#pragma once
#include "include\libzplay.h"
using namespace libZPlay;
/*
	此头文件定义MP3格式的文件信息，具体可以参考：http://blog.csdn.net/wwv386646959/article/details/40868035
	MP3文件结构概述
	Layer-3音频文件，MPEG(MovingPicture Experts Group)在汉语中译为活动图像专家组，特指活动影音压缩标准，MPEG音频文件是MPEG1标准中的声音部分，也叫MPEG音频层，
	它根据压缩质量和编码复杂程度划分为三层，即Layer-1、Layer2、Layer3，且分别对应MP1、MP2、MP3这三种声音文件，并根据不同的用途，使用不同层次的编码。
	MPEG音频编码的层次越高，编码器越复杂，压缩率也越高，MP1和MP2的压缩率分别为4：1和6：1-8：1，而MP3的压缩率则高达10：1-12：1。
	MP3文件大体分为三部分：TAG_V2(ID3V2)，音频数据，TAG_V1(ID3V1)，其中ID3V2是ID3V1的补充，并不是所有的MP3都有ID3V2补充，即不是所有的MP3文件都有ID3V2。
*/

/*
	ID3V2 结构
    如果MP3文件存在ID3V2，则一定在文件的头部，ID3V2结构分为头部（header）和若干标签帧，其中头部长度为10字节，10个字节的结构如表1：
	| 0    1  	2	|	3	 |   4		|		5		|		6			7			8			9	|
	| 内容为”ID3” | 版本号 | 副版本号 |存放标志的字节	|	ID3V2总大小（帧头和之后的若干标签帧总和）	|
	
	1.从上述结构可看出判断MP3文件是否存在ID3V2，只需要判断文件前三个字节是否是”ID3”
	2.ID3V2数据大小计算公式：
	total_size = (Size[0]&0x7F)*0x200000+ (Size[1]&0x7F)*0x400 + (Size[2]&0x7F)*0x80 +(Size[3]&0x7F)
	其中，size[0~3]，分别是表1中的6~9字节。需要注意的是，这个公式计算的长度并不包括ID3V2的10个字节的头部。
	
	ID3V2头部之后的若干标签帧每一帧结构分为标签ID（4字节）、帧内容大小（4字节，不包括标签帧帧头）、存放标志位（2字节）、内容。其中标签ID的含义如下：
	TEXT： 歌词作者    
	TENC： 编码        
	WXXX： URL链接(URL)       
	TCOP： 版权(Copyright)   
	TOPE： 原艺术家
	TCOM： 作曲家      
	TDAT： 日期        
	TPE3： 指挥者             
	TPE2： 乐队             
	TPE1： 艺术家相当于ID3v1的Artist
	TPE4： 翻译（记录员、修改员）  
	TYER： 即ID3v1的Year   
	USLT： 歌词       
	TSIZ： 大小
	TALB： 专辑相当于ID3v1的Album   
	TIT1： 内容组描述
	TIT2： 标题相当于ID3v1的Title	
	TIT3： 副标题
	TCON： 流派（风格）相当于ID3v1的Genre 
	AENC： 音频加密技术
	TBPM： 每分钟节拍数
	COMM： 注释相当于ID3v1的Comment
	TDLY： 播放列表返录               
	TRCK： 音轨（曲号）相当于ID3v1的Track
	TFLT： 文件类型            
	TIME： 时间　
	TKEY： 最初关键字         
	TLAN： 语言
	TLEN： 长度                    
	TMED： 媒体类型
	TOAL： 原唱片集            
	TOFN： 原文件名
	TOLY： 原歌词作者           
	TORY： 最初发行年份
	TOWM： 文件所有者（许可证者）  
	TPOS： 作品集部分
	TPUB： 发行人                  
	TRDA： 录制日期
	TRSN： Intenet电台名称            
	TRSO： Intenet电台所有者   UFID： 唯一的文件标识符 　
	TSRC： ISRC（国际的标准记录代码）  
	TSSE： 编码使用的软件（硬件设置）
*/

//定义头部和标签帧
typedef struct _ID3v2Header_
{
	char	szIdentify[3];	/* ID3v2固定标志：ID3 必须为"ID3"否则认为标签不存在*/
	char	szVersion;		/*主版本号，ID3v2就是3*/
	char	szRevision;		/*副版本号，一般都为0*/
	char	szFlag;			/*存放标志的字节，标志位，一般为0，字义为abc00000*/
	char	szSize[4];		/*标签大小，包括标签头的10 个字节和所有的标签帧的大小 一共四个字节，但每个字节只使用7位，最高位不使用恒为0，所以格式： 0xxxxxxx 0xxxxxxx 0xxxxxxx 0xxxxxxx*/
}ID3v2Header;

//标签帧，10个字节
typedef struct _ID3v2Frame_
{
	char szFrameID[4];          // 标志对照符，如TEXT，TOPE，TDAT....
	char szSize[4];             // 帧体的大小，按照正常的8位存储的，FSize = Size[0]*0x100000000 + Size[1]*0x10000 + Size[2]*0x100 + Size[3];
	char szFlag[2];             // 存放标志
}ID3v2Frame;

typedef struct _tagID3V1_
{
	char	szHeader[3];        /*标签头必须是"TAG"否则认为没有标签*/
	char	szTitle[30];        /*标题*/
	char	szArtist[30];		/*作者*/
	char	szAlbum[30];		/*专集*/
	char	szYear[4];          /*出品年代*/
	char	szComment[28];		/*备注*/
	char	szreserve;          /*保留*/
	char	sztrack;            /*音轨*/
	char	szGenre;            /*类型*/
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
	MSG_OPEN = 0,    //打开
	MSG_PLAY,        //播放
	MSG_PLAYING,     //正在播放
	MSG_PAUSE,       //暂停
	MSG_RESUME,      //继续
	MSG_STOP,        //停止
	MSG_SEEK,        //播放位置
	MSG_PREV,        //上一首
	MSG_NEXT,        //下一首
	MSG_VOLUME,      //音量
	MSG_SET_LOOP     //设置循环状态
};

typedef struct tagMEDIA
{
	CString		name;				//名称
	CString		pathFileName;		//文件路径名
	CString		logoPath;			//logo图片的路径
	CString		exName;				//扩展名
	UINT		playNum;			//播放次数
	CString		size;				//大小  (M)
	TStreamTime totalTime;			//总时间	
}MEDIA;


class CMusicPlayer;
class CHeMusicPlayerDlg;
//回调函数指针
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
	void Play();		//播放
	void Pause();		//暂停
	void Stop();		//停止播放
	void Seek(int nSec);	//seek 单位秒
	void PlayPreSong();	//上一曲
	void PlayNextSong();	//下一曲
	void SetLoopMode(LoopMode loopMode);	//设置循环模式
	void SetVolumn(int nVolumn);	//设置音量
	int GetVolumn();
	void GetStreamInfo(TStreamInfo& Info);	//获取音频流信息
	int	 GetID3Info(TID3InfoEx& Info);		//获取ID3结构, return 0 fail, 1 success.
	
	ZPlay* GetZPlayer();	//获取ZPlayer指针，供CallbackFunc回调函数使用
	PLAY_PROC GetPlayProc();	//获取窗口回调函数，供CallbackFunc回调函数使用

	CHeMusicPlayerDlg* GetMainDlg();	//获取主对话框指针
private:
	ZPlay*		m_pMusicPlayer;
	PLAY_PROC	m_PlayProc;				//播放回调函数指针
	CString		m_strMusicPath;
	int			m_nVolumn;
	LoopMode	m_loopMode;
	CHeMusicPlayerDlg*	m_pMainDlg;			//主窗体句柄
	tagMEDIA	m_stMedia;
};