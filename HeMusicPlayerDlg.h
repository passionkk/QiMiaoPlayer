
// HeMusicPlayerDlg.h : 头文件
//

#pragma once

#include "MusicInfo.h"
#include "afxcmn.h"
#include <vector>
#include "afxwin.h"
#include "UI\SkinButton.h"
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
};
