#include "stdafx.h"
#include "MusicInfo.h"
#include "MsgDefine.h"

CMusicInfo::CMusicInfo()
{
	m_strMusicPath.Empty();
}

CMusicInfo::~CMusicInfo()
{
}

void CMusicInfo::GetID3V2Info()
{
	if (!m_strMusicPath.IsEmpty())
	{
		CFile file;
		ID3v2Header mp3Header;
		ID3v2Frame	mp3Frame;
		if (!file.Open(m_strMusicPath, CFile::modeRead))
		{
			AfxMessageBox(L"打开文件失败");
			return;
		}

		int FSize = 0;
		char str[4096] = { 0 };
		char str2[5] = { 0 };
		int head_size = 0;
		//ID3
		file.Read(&mp3Header, sizeof(mp3Header));
		if (strncmp(mp3Header.szIdentify, "ID3", 3))
		{
			printf("此歌曲不支持ID3v2标准！\n");
			return;
		}
		if (mp3Header.szIdentify[0] != 'I' || mp3Header.szIdentify[1] != 'D' || mp3Header.szIdentify[2] != '3')
		{
			printf("此歌曲不支持ID3v2标准！\n");
			return;
		}
		//ID3Size
		int ID3size = (mp3Header.szSize[0] & 0x7F) * 0x200000 + (mp3Header.szSize[1] & 0x7F) * 0x400
			+ (mp3Header.szSize[2] & 0x7F) * 0x80 + (mp3Header.szSize[3] & 0x7F);

		for (int i = 0; i<ID3size; i = i + 11 + FSize)
		{
			memset(&mp3Frame, 0, sizeof(mp3Frame));
			memset(&str, 0, sizeof(str));
			file.Seek(10 + i, CFile::begin);	//移动到标签帧头
			file.Read(&mp3Frame, sizeof(mp3Frame));
			//原则上是不用-1的，但是实际发现，总有一个字节的差距，为了计算方便-1，所以出现-1时标明此区块无内容
			FSize = (int)(mp3Frame.szSize[0] * 0x100000000 + mp3Frame.szSize[1] * 0x10000 + mp3Frame.szSize[2] * 0x100 + mp3Frame.szSize[3] - 1);
			if (FSize>0)
			{
				file.Seek(10 + 11 + i, CFile::begin);	//移动到内容区
				file.Read(str, FSize);
				GetStr(mp3Frame.szFrameID, str2);
				head_size += 11;
			}
			else
			{
				return;// ID3size + 10;
			}
		}
		file.Close();
	}
}

void CMusicInfo::GetID3V1Info()
{
	if (!m_strMusicPath.IsEmpty())
	{
		CFile file;
		if (!file.Open(m_strMusicPath, CFile::modeRead))
		{
			AfxMessageBox(L"打开文件失败");
			return;
		}
		tagID3V1 ID3V1Info;
		file.Seek(-128, CFile::end);
		file.Read(&ID3V1Info, sizeof(ID3V1Info));
		file.Close();
	}
}

void CMusicInfo::SetMusicPath(const CString strMusicPath)
{
	m_strMusicPath = strMusicPath;
	//GetID3V1Info();
	//GetID3V2Info();
}

void CMusicInfo::GetMusicPath(CString& strMusicPath)
{
	strMusicPath = m_strMusicPath;
}

/**/
void CMusicInfo::GetStr(char* oldstr, char* str)
{
	if (0 == memcmp((LPCTSTR)"TIT2", oldstr, 4))
	{
		memcpy(str, "标题", 4);
	}
	else if(0 == memcmp((LPCTSTR)"TPE1", oldstr, 4))
	{
		memcpy(str, "作者", 4);
	}else if(0 == memcmp((LPCTSTR)"TALB", oldstr, 4)){

		memcpy(str, "专辑", 4);
	}
	else if(0 == memcmp((LPCTSTR)"TRCK", oldstr, 4))
	{
		memcpy(str, "音轨", 4);
	}
	else if(0 == memcmp((LPCTSTR)"TYER", oldstr, 4))
	{
		memcpy(str, "年代", 4);
	}
	else if(0 == memcmp((LPCTSTR)"COMM", oldstr, 4))
	{
		memcpy(str, "备注", 4);
	}else if(0 == memcmp((LPCTSTR)"TCON", oldstr, 4))
	{
		memcpy(str, "类型", 4);
	}
	else
	{
		memcpy(str, "未知", 4);  //其他的不是很重要，所以省略了
	}
}

CMusicPlayer::CMusicPlayer()
{
	m_strMusicPath.Empty();
	m_nVolumn = 0;
	m_loopMode = LoopMode::SEQUENCE;
	m_pMusicPlayer = NULL;
	m_pMainDlg = NULL;
	m_PlayProc = NULL;
}

CMusicPlayer::~CMusicPlayer()
{
	if (m_pMusicPlayer != NULL)
	{
		m_pMusicPlayer->Release();
	}
}

int __stdcall CallbackFunc(void* instance, void *user_data, TCallbackMessage message, unsigned int param1, unsigned int param2)
{
	ZPlay* myInstance = (ZPlay*)instance;
	CMusicPlayer* player = (CMusicPlayer*)user_data;
	if (message & MsgWaveBuffer)
	{
		UINT num = 0;
		TStreamTime ttm;
		player->GetZPlayer()->GetPosition(&ttm);
		num = ttm.sec;
		player->GetPlayProc()(player, MSG_PLAYING, 0, num, NULL);
	}
	return 0;
}


void CMusicPlayer::InitPlayer(PLAY_PROC proc)
{
	if (m_pMusicPlayer == NULL)
	{
		m_pMusicPlayer = CreateZPlay();
		if (m_pMusicPlayer != NULL)
		{
			m_pMusicPlayer->SetCallbackFunc(CallbackFunc, (TCallbackMessage)(MsgStop | MsgNextSong | MsgEnterVolumeSlideAsync | MsgExitVolumeSlideAsync | MsgEnterVolumeSlide | MsgExitVolumeSlide), 0);
		}
	}
	m_PlayProc = proc;
}
void CMusicPlayer::Open(CString strMusicPath, bool bAutoPlay)
{
	m_strMusicPath = strMusicPath;
	if (m_pMusicPlayer->OpenFileW(m_strMusicPath, sfAutodetect) == 0)
	{
		OutputDebugString(L"open file error");
		return ;
	}

	if (bAutoPlay)
		Play();
}

void CMusicPlayer::Play()
{
	m_pMusicPlayer->Play();
}

void CMusicPlayer::Pause()
{
	m_pMusicPlayer->Pause();
}

void CMusicPlayer::Stop()
{
	m_pMusicPlayer->Stop();
}

void CMusicPlayer::Seek(int nSec)
{
	if (m_pMusicPlayer != NULL)
	{
		TStreamTime stTST;
		stTST.sec = abs(nSec);
		
		m_pMusicPlayer->Seek(tfSecond, &stTST, nSec > 0 ? smFromCurrentBackward : smFromCurrentForward);
	}
}

void CMusicPlayer::PlayPreSong()
{
	if (m_pMusicPlayer != NULL)
	{
		
	}
}

void CMusicPlayer::PlayNextSong()
{
	if (m_pMusicPlayer != NULL)
	{
		
	}
}

void CMusicPlayer::SetLoopMode(LoopMode loopMode)
{
	m_loopMode = loopMode;
}

void CMusicPlayer::SetVolumn(int nVolumn)
{
	m_pMusicPlayer->SetMasterVolume(nVolumn, nVolumn);
}

int CMusicPlayer::GetVolumn()
{
	return m_nVolumn;
}

void CMusicPlayer::GetStreamInfo(TStreamInfo& Info)
{
	if (m_pMusicPlayer != NULL)
	{
		m_pMusicPlayer->GetStreamInfo(&Info);
	}
}

int	 CMusicPlayer::GetID3Info(TID3InfoEx& Info)
{
	if (m_pMusicPlayer != NULL)
	{
		return m_pMusicPlayer->LoadID3Ex(&Info, 0);
	}
	return 0;
}

ZPlay* CMusicPlayer::GetZPlayer()
{
	return m_pMusicPlayer;
}

PLAY_PROC CMusicPlayer::GetPlayProc()
{
	return m_PlayProc;
}