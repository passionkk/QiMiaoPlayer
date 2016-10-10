
// HeMusicPlayerDlg.h : 头文件
//

#pragma once

#include "afxcmn.h"
#include <vector>
#include "afxwin.h"
#include "resource.h"
#include "MusicInfo.h"
#include "UI\SkinButton.h"
#include "UI\Label.h"
#include "UI\StaticTime.h"
#include "UI\BitmapSlider.h"
#include "UI\Dialog\DlgPlayControl.h"
#include "UI\Dialog\PlayListUI.h"

// CHeMusicPlayerDlg 对话框
class CHeMusicPlayerDlg : public CDialogEx
{
// 构造
public:
	CHeMusicPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HEMUSICPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnHdnItemdblclickListSonglist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSonglist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonFr();
	afx_msg void OnBnClickedButtonFf();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonPrevone();
	afx_msg void OnBnClickedButtonNextone();
	afx_msg void OnTRBNThumbPosChangingSliderVoice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);


	//歌曲播放回调函数
	static void player_proc(CMusicPlayer* pPlayer, PLAY_MSG msg, WPARAM wParam, LPARAM lParam, void* pVoid);

	//时间转换函数
	static CString SecToTime(int nSec);
protected:
	void InitCtrl();		//对话框初始化控件
	void InitPlayer();		//初始化播放器
	void InitPlayList();	//初始化播放列表
	void SavePlayList();	//保存播放列表
private:
	CMusicInfo		musicInfo;
	CListCtrl		m_listPlayList;
	int				m_nListCount;
	CMusicPlayer	m_player;

	PlayState		m_playState;
	LoopMode		m_loopMode;
	CString			m_strCurMusicPath;	//当前播放的歌曲
	std::vector<CMusicInfo>	m_vecPlayList;	//播放列表
	CSliderCtrl		m_sliderVolumn;
public:
	CSkinButton		m_btnPlay;
	CSliderCtrl		m_sliderProgress;
	//CBitmapSlider	m_sliderProgress;
	// 歌曲播放时长
	CStatic			m_staticPlayTime;	//这里暂时使用默认的 static控件，未找到合适的控件
	int				m_nCurPlaySec;		//当前播放时长
	bool			m_bPressProgressSlider;	//左键按下进度滑块
	CStatic			m_picSong;

	//测试界面
	CDlgPlayControl	m_DlgPlayControl;
	CPlayListUI		m_DlgPlayList;
};
