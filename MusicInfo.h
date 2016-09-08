#pragma once
#include "include\libzplay.h"
using namespace libZPlay;
/*
	��ͷ�ļ�����MP3��ʽ���ļ���Ϣ��������Բο���http://blog.csdn.net/wwv386646959/article/details/40868035
	MP3�ļ��ṹ����
	Layer-3��Ƶ�ļ���MPEG(MovingPicture Experts Group)�ں�������Ϊ�ͼ��ר���飬��ָ�Ӱ��ѹ����׼��MPEG��Ƶ�ļ���MPEG1��׼�е��������֣�Ҳ��MPEG��Ƶ�㣬
	������ѹ�������ͱ��븴�ӳ̶Ȼ���Ϊ���㣬��Layer-1��Layer2��Layer3���ҷֱ��ӦMP1��MP2��MP3�����������ļ��������ݲ�ͬ����;��ʹ�ò�ͬ��εı��롣
	MPEG��Ƶ����Ĳ��Խ�ߣ�������Խ���ӣ�ѹ����ҲԽ�ߣ�MP1��MP2��ѹ���ʷֱ�Ϊ4��1��6��1-8��1����MP3��ѹ������ߴ�10��1-12��1��
	MP3�ļ������Ϊ�����֣�TAG_V2(ID3V2)����Ƶ���ݣ�TAG_V1(ID3V1)������ID3V2��ID3V1�Ĳ��䣬���������е�MP3����ID3V2���䣬���������е�MP3�ļ�����ID3V2��
*/

/*
	ID3V2 �ṹ
    ���MP3�ļ�����ID3V2����һ�����ļ���ͷ����ID3V2�ṹ��Ϊͷ����header�������ɱ�ǩ֡������ͷ������Ϊ10�ֽڣ�10���ֽڵĽṹ���1��
	| 0    1  	2	|	3	 |   4		|		5		|		6			7			8			9	|
	| ����Ϊ��ID3�� | �汾�� | ���汾�� |��ű�־���ֽ�	|	ID3V2�ܴ�С��֡ͷ��֮������ɱ�ǩ֡�ܺͣ�	|
	
	1.�������ṹ�ɿ����ж�MP3�ļ��Ƿ����ID3V2��ֻ��Ҫ�ж��ļ�ǰ�����ֽ��Ƿ��ǡ�ID3��
	2.ID3V2���ݴ�С���㹫ʽ��
	total_size = (Size[0]&0x7F)*0x200000+ (Size[1]&0x7F)*0x400 + (Size[2]&0x7F)*0x80 +(Size[3]&0x7F)
	���У�size[0~3]���ֱ��Ǳ�1�е�6~9�ֽڡ���Ҫע����ǣ������ʽ����ĳ��Ȳ�������ID3V2��10���ֽڵ�ͷ����
	
	ID3V2ͷ��֮������ɱ�ǩ֡ÿһ֡�ṹ��Ϊ��ǩID��4�ֽڣ���֡���ݴ�С��4�ֽڣ���������ǩ֡֡ͷ������ű�־λ��2�ֽڣ������ݡ����б�ǩID�ĺ������£�
	TEXT�� �������    
	TENC�� ����        
	WXXX�� URL����(URL)       
	TCOP�� ��Ȩ(Copyright)   
	TOPE�� ԭ������
	TCOM�� ������      
	TDAT�� ����        
	TPE3�� ָ����             
	TPE2�� �ֶ�             
	TPE1�� �������൱��ID3v1��Artist
	TPE4�� ���루��¼Ա���޸�Ա��  
	TYER�� ��ID3v1��Year   
	USLT�� ���       
	TSIZ�� ��С
	TALB�� ר���൱��ID3v1��Album   
	TIT1�� ����������
	TIT2�� �����൱��ID3v1��Title	
	TIT3�� ������
	TCON�� ���ɣ�����൱��ID3v1��Genre 
	AENC�� ��Ƶ���ܼ���
	TBPM�� ÿ���ӽ�����
	COMM�� ע���൱��ID3v1��Comment
	TDLY�� �����б�¼               
	TRCK�� ���죨���ţ��൱��ID3v1��Track
	TFLT�� �ļ�����            
	TIME�� ʱ�䡡
	TKEY�� ����ؼ���         
	TLAN�� ����
	TLEN�� ����                    
	TMED�� ý������
	TOAL�� ԭ��Ƭ��            
	TOFN�� ԭ�ļ���
	TOLY�� ԭ�������           
	TORY�� ����������
	TOWM�� �ļ������ߣ����֤�ߣ�  
	TPOS�� ��Ʒ������
	TPUB�� ������                  
	TRDA�� ¼������
	TRSN�� Intenet��̨����            
	TRSO�� Intenet��̨������   UFID�� Ψһ���ļ���ʶ�� ��
	TSRC�� ISRC�����ʵı�׼��¼���룩  
	TSSE�� ����ʹ�õ������Ӳ�����ã�
*/

//����ͷ���ͱ�ǩ֡
typedef struct _ID3v2Header_
{
	char	szIdentify[3];	/* ID3v2�̶���־��ID3 ����Ϊ"ID3"������Ϊ��ǩ������*/
	char	szVersion;		/*���汾�ţ�ID3v2����3*/
	char	szRevision;		/*���汾�ţ�һ�㶼Ϊ0*/
	char	szFlag;			/*��ű�־���ֽڣ���־λ��һ��Ϊ0������Ϊabc00000*/
	char	szSize[4];		/*��ǩ��С��������ǩͷ��10 ���ֽں����еı�ǩ֡�Ĵ�С һ���ĸ��ֽڣ���ÿ���ֽ�ֻʹ��7λ�����λ��ʹ�ú�Ϊ0�����Ը�ʽ�� 0xxxxxxx 0xxxxxxx 0xxxxxxx 0xxxxxxx*/
}ID3v2Header;

//��ǩ֡��10���ֽ�
typedef struct _ID3v2Frame_
{
	char szFrameID[4];          // ��־���շ�����TEXT��TOPE��TDAT....
	char szSize[4];             // ֡��Ĵ�С������������8λ�洢�ģ�FSize = Size[0]*0x100000000 + Size[1]*0x10000 + Size[2]*0x100 + Size[3];
	char szFlag[2];             // ��ű�־
}ID3v2Frame;

typedef struct _tagID3V1_
{
	char	szHeader[3];        /*��ǩͷ������"TAG"������Ϊû�б�ǩ*/
	char	szTitle[30];        /*����*/
	char	szArtist[30];		/*����*/
	char	szAlbum[30];		/*ר��*/
	char	szYear[4];          /*��Ʒ���*/
	char	szComment[28];		/*��ע*/
	char	szreserve;          /*����*/
	char	sztrack;            /*����*/
	char	szGenre;            /*����*/
}tagID3V1, *pID3V1;

enum PlayState{
	PLAY = 0,
	PAUSE,
	STOP
};

enum LoopMode{
	SEQUENCE = 0,
	RANDOM,
	SINGLEONE,
	LISTLOOP
};

enum PLAY_MSG
{
	MSG_OPEN = 0,    //��
	MSG_PLAY,        //����
	MSG_PLAYING,     //���ڲ���
	MSG_PAUSE,       //��ͣ
	MSG_RESUME,      //����
	MSG_STOP,        //ֹͣ
	MSG_SEEK,        //����λ��
	MSG_PREV,        //��һ��
	MSG_NEXT,        //��һ��
	MSG_VOLUME,      //����
	MSG_SET_LOOP     //����ѭ��״̬
};

typedef struct tagMEDIA
{
	CString		name;				//����
	CString		pathFileName;		//�ļ�·����
	CString		logoPath;			//logoͼƬ��·��
	CString		exName;				//��չ��
	UINT		playNum;			//���Ŵ���
	CString		size;				//��С  (M)
	TStreamTime totalTime;			//��ʱ��	
}MEDIA;


class CMusicPlayer;
class CHeMusicPlayerDlg;
//�ص�����ָ��
typedef void(*PLAY_PROC)(CMusicPlayer*, PLAY_MSG, WPARAM, LPARAM, void*);

class CMusicInfo
{
public:
	CMusicInfo();
	virtual ~CMusicInfo();

public:
	void GetID3V2Info();
	void GetID3V1Info();
	void GetStr(char* oldstr, char* str);
	void SetMusicPath(const CString strMusicPath);
	void GetMusicPath(CString& strMusicPath);
private:
	CString m_strMusicPath;
};

class CMusicPlayer
{
public:
	CMusicPlayer();
	virtual ~CMusicPlayer();

public:
	void SetWndHwnd(const HWND& hwnd);
	// callback function prototype, need this to use callback message to push more data into managed stream
	void InitPlayer(PLAY_PROC proc);
	void Open(CString strMusicPath, bool bAutoPlay = true);
	void Play();		//����
	void Pause();		//��ͣ
	void Stop();		//ֹͣ����
	void Seek(int nSec);	//seek ��λ��
	void PlayPreSong();	//��һ��
	void PlayNextSong();	//��һ��
	void SetLoopMode(LoopMode loopMode);	//����ѭ��ģʽ
	void SetVolumn(int nVolumn);	//��������
	int GetVolumn();
	void GetStreamInfo(TStreamInfo& Info);	//��ȡ��Ƶ����Ϣ
	int	 GetID3Info(TID3InfoEx& Info);		//��ȡID3�ṹ, return 0 fail, 1 success.
	
	ZPlay* GetZPlayer();	//��ȡZPlayerָ�룬��CallbackFunc�ص�����ʹ��
	PLAY_PROC GetPlayProc();	//��ȡ���ڻص���������CallbackFunc�ص�����ʹ��

	CHeMusicPlayerDlg* GetMainDlg();	//��ȡ���Ի���ָ��
private:
	ZPlay*		m_pMusicPlayer;
	PLAY_PROC	m_PlayProc;				//���Żص�����ָ��
	CString		m_strMusicPath;
	int			m_nVolumn;
	LoopMode	m_loopMode;
	CHeMusicPlayerDlg*	m_pMainDlg;			//��������
	tagMEDIA	m_stMedia;
};