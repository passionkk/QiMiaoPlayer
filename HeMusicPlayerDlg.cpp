
// HeMusicPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HeMusicPlayer.h"
#include "HeMusicPlayerDlg.h"
#include "afxdialogex.h"
#include "Util\FileUtil.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CHeMusicPlayerDlg �Ի���

CHeMusicPlayerDlg::CHeMusicPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHeMusicPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nListCount = 0;
	m_playState = PlayState::STOP;
	m_loopMode = LoopMode::SEQUENCE;
	m_vecPlayList.clear();
}

void CHeMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SONGLIST, m_listPlayList);
	DDX_Control(pDX, IDC_SLIDER_VOICE, m_sliderVolumn);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_btnPlay);
}

BEGIN_MESSAGE_MAP(CHeMusicPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CHeMusicPlayerDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON1, &CHeMusicPlayerDlg::OnBnClickedButton1)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CHeMusicPlayerDlg::OnHdnItemdblclickListSonglist)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SONGLIST, &CHeMusicPlayerDlg::OnNMDblclkListSonglist)
	ON_BN_CLICKED(IDC_BUTTON_FR, &CHeMusicPlayerDlg::OnBnClickedButtonFr)
	ON_BN_CLICKED(IDC_BUTTON_FF, &CHeMusicPlayerDlg::OnBnClickedButtonFf)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_PREVONE, &CHeMusicPlayerDlg::OnBnClickedButtonPrevone)
	ON_BN_CLICKED(IDC_BUTTON_NEXTONE, &CHeMusicPlayerDlg::OnBnClickedButtonNextone)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_VOICE, &CHeMusicPlayerDlg::OnTRBNThumbPosChangingSliderVoice)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CHeMusicPlayerDlg ��Ϣ�������

BOOL CHeMusicPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	InitCtrl();
	InitPlayer();
	InitPlayList();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHeMusicPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHeMusicPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHeMusicPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHeMusicPlayerDlg::InitCtrl()
{
	//Button 
	//m_btnPlay.Init(IDI_ICON_PLAY, IDI_ICON_PLAY, L"����");
	//��ʼ�������б�
	CRect rect;
	m_listPlayList.GetClientRect(&rect);
	m_listPlayList.InsertColumn(0, L"������", LVCFMT_CENTER, rect.Width()/3);
	m_listPlayList.InsertColumn(1, L"·��", LVCFMT_CENTER, rect.Width() * 2/3);
	m_listPlayList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//����
	m_sliderVolumn.SetRange(0, 100);
	m_sliderVolumn.SetPos(30);
}

void CHeMusicPlayerDlg::InitPlayer()
{
	m_player.InitPlayer(player_proc);
}

void CHeMusicPlayerDlg::InitPlayList()
{
	CString strCurPath;
	GetModuleFileName(NULL, strCurPath.GetBuffer(MAX_PATH), MAX_PATH);
	strCurPath.ReleaseBuffer();
	int pos = strCurPath.ReverseFind(_T('\\'));
	strCurPath = strCurPath.Left(pos);
	CString strPlayList = strCurPath + L"\\" + L"playlist.txt";

	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");
	CStdioFile stdFile;
	if (stdFile.Open(strPlayList, CFile::modeRead|CFile::typeText))
	{
		CString strPath = L"";
		CString strFileName = L"";
		while (stdFile.ReadString(strPath))
		{
			strFileName = FileUtil::GetFileNameFromAbsPath(strPath);
			strFileName = FileUtil::GetFileNameWithoutExtend(strFileName);
			m_listPlayList.InsertItem(m_nListCount, strFileName);
			m_listPlayList.SetItemText(m_nListCount, 1, strPath);
			m_nListCount++;
			CMusicInfo mInfo;
			mInfo.SetMusicPath(strPath);
			m_vecPlayList.push_back(mInfo);
		}
		stdFile.Close();
		setlocale(LC_CTYPE, old_locale); //��ԭ������������� 
		free(old_locale);//��ԭ�����趨
	}
}

void CHeMusicPlayerDlg::SavePlayList()
{
	CString strCurPath;
	GetModuleFileName(NULL, strCurPath.GetBuffer(MAX_PATH), MAX_PATH);
	strCurPath.ReleaseBuffer();
	int pos = strCurPath.ReverseFind(_T('\\'));
	strCurPath = strCurPath.Left(pos);
	CString strPlayList = strCurPath + L"\\" + L"playlist.txt";

	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");
	CStdioFile stdFile;
	if (stdFile.Open(strPlayList, CFile::modeWrite | CFile::modeCreate))
	{
		int nlistSize = m_vecPlayList.size();
		CString strPath;
		for (int i = 0; i < nlistSize; i++)
		{
			m_vecPlayList.at(i).GetMusicPath(strPath);
			strPath += L"\n";
			stdFile.WriteString(strPath);
		}
		stdFile.Close();
	}
	setlocale(LC_CTYPE, old_locale); //��ԭ������������� 
	free(old_locale);//��ԭ�����趨
}

void CHeMusicPlayerDlg::OnBnClickedButtonPlay()
{
	if (m_playState == PlayState::PLAY)
	{
		m_player.Pause();
		m_playState = PlayState::PAUSE;
	}
	else if (m_playState == PlayState::PAUSE)
	{
		m_player.Play();
		m_playState = PlayState::PLAY;
	}
	else
	{	
		//ֹͣ״̬
		int nCurSel = m_listPlayList.GetSelectionMark();
		if (nCurSel != -1)
		{
			CString strMusicPath = m_listPlayList.GetItemText(nCurSel, 1);
			m_player.Open(strMusicPath);
			m_strCurMusicPath = strMusicPath;
			m_playState = PlayState::PLAY;
		}
	}
}


void CHeMusicPlayerDlg::OnBnClickedButton1()
{
	TCHAR szFilter[] = _T("Mp3 Files (*.mp3)|*.mp3|")
		_T("Wav (*.wav)|*.wav|Audio Files (*.mp3;*.wav)|")
		_T("*.mp3; *.wav|All Files (*.*)|*.*||");


	CFileDialog fileDlg(TRUE, _T("mp3"), _T("*.mp3"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilter);

	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();
		//Change the window's title to the opened file's title.
		CString fileName = fileDlg.GetFileTitle();
		fileName = FileUtil::GetFileNameWithoutExtend(fileName);
		m_listPlayList.InsertItem(m_nListCount, fileName);
		m_listPlayList.SetItemText(m_nListCount, 1, pathName);
		m_nListCount++;

		CMusicInfo mInfo;
		mInfo.SetMusicPath(pathName);
		m_vecPlayList.push_back(mInfo);
	}

}

void CHeMusicPlayerDlg::OnHdnItemdblclickListSonglist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (phdr != NULL)
	{
		int nDbClkItem = phdr->iItem;
		CString strMusicPath = m_listPlayList.GetItemText(nDbClkItem, 1);
		m_player.Open(strMusicPath);
	}
	*pResult = 0;
}


void CHeMusicPlayerDlg::OnNMDblclkListSonglist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView != NULL)
	{
		int nDbClkItem = pNMListView->iItem;
		CString strMusicPath = m_listPlayList.GetItemText(nDbClkItem, 1);
		m_player.Open(strMusicPath);
		m_strCurMusicPath = strMusicPath;
		m_playState = PlayState::PLAY;
	}
	*pResult = 0;
}


void CHeMusicPlayerDlg::OnBnClickedButtonFr()
{
	//���� ��ʱĬ��5s
	m_player.Seek(-5);
	if (m_playState == PlayState::PAUSE)
		m_player.Pause();
}


void CHeMusicPlayerDlg::OnBnClickedButtonFf()
{
	//��� ��ʱĬ��5s
	m_player.Seek(5);
	if (m_playState == PlayState::PAUSE)
		m_player.Pause();
}


void CHeMusicPlayerDlg::OnClose()
{
	SavePlayList();

	CDialogEx::OnClose();
}


void CHeMusicPlayerDlg::OnBnClickedButtonPrevone()
{
	// ��һ��
	m_player.PlayPreSong();
}


void CHeMusicPlayerDlg::OnBnClickedButtonNextone()
{
	// ��һ��
	m_player.PlayNextSong();
}


void CHeMusicPlayerDlg::OnTRBNThumbPosChangingSliderVoice(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// 

	*pResult = 0;
}


void CHeMusicPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nCtrlID = pScrollBar->GetDlgCtrlID();
	int nVolumn = 0;
	switch (nCtrlID)
	{
	case IDC_SLIDER_VOICE:
		nVolumn = m_sliderVolumn.GetPos();
		m_player.SetVolumn(nVolumn);
		break;
	default:
		break;

	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CHeMusicPlayerDlg::player_proc(CMusicPlayer* pPlayer, PLAY_MSG msg, WPARAM wParam, LPARAM lParam, void* pVoid)
{
	CHeMusicPlayerDlg* pDlg = pPlayer->GetMainDlg();

	CFrameWnd* pFrame = pPlayer->GetMainFrame();
	MEDIA* media = (MEDIA*)wParam;
	if (pFrame == NULL || media == NULL)
		return;

	switch (msg)
	{

	case MSG_OPEN:
	{
					 pFrame->m_pLblTotalTime->SetText(CMusicPlayer::TimeToString(media->totalTime.sec));
					 pFrame->m_pSliderPlayProcess->SetMinValue(0);
					 pFrame->m_pSliderPlayProcess->SetMaxValue(media->totalTime.sec);
					 pFrame->m_pSliderPlayProcess->SetValue(0);
	}
		break;
	case MSG_PLAYING:
	{

						CDuiString playTime = CMusicPlayer::TimeToString(lParam);
						pFrame->m_pLblPlayTime->SetText(playTime.GetData());
						pFrame->m_pSliderPlayProcess->SetValue((int)lParam);

						CLabelUI* music_curpos = static_cast<CLabelUI*>(pFrame->GetMainWndPaintManager()->FindSubControlByName(pFrame->GetCurMedia()->pControl, kMusicCurPosControlName));
						CDuiString strSumTime = CMusicPlayer::TimeToString(media->totalTime.sec);
						if (music_curpos != NULL)
						{
							TCHAR szBuf[MAX_PATH] = { 0 };
							_stprintf_s(szBuf, MAX_PATH - 1, _T("%s/%s"), playTime.GetData(), strSumTime.GetData());
							music_curpos->SetText(szBuf);
						}
	}
		break;
	case MSG_PLAY:
	{
					 media->playNum += 1;
					 if (pFrame->m_pLblMainWndTitile != NULL)
						 pFrame->m_pLblMainWndTitile->SetText(media->name.GetData());
	}
		break;
	case MSG_PAUSE:
	{

	}
		break;
	case MSG_RESUME:
	{
	}
		break;
	case MSG_STOP:
	{
					 if (pPlayer->GetPlayState() == P_STOP)
					 {
						 pFrame->SetPlayBtnState(false);
						 pFrame->m_pSliderPlayProcess->SetValue(0);

						 pFrame->m_pLblPlayTime->SetText(_T("00:00"));

						 CLabelUI* music_curpos = static_cast<CLabelUI*>(pFrame->GetMainWndPaintManager()->FindSubControlByName(/*pCurMedia*/media->pControl, kMusicCurPosControlName));
						 if (music_curpos != NULL)
						 {
							 music_curpos->SetText(_T("00:00"));
						 }

						 if (pFrame->m_pLblMainWndTitile != NULL)
							 pFrame->m_pLblMainWndTitile->SetText(MainWndTitle);

					 }
	}
		break;
	case MSG_VOLUME:
	{
	}
		break;
	}
}
