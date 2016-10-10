
// HeMusicPlayerDlg.h : ͷ�ļ�
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

// CHeMusicPlayerDlg �Ի���
class CHeMusicPlayerDlg : public CDialogEx
{
// ����
public:
	CHeMusicPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HEMUSICPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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


	//�������Żص�����
	static void player_proc(CMusicPlayer* pPlayer, PLAY_MSG msg, WPARAM wParam, LPARAM lParam, void* pVoid);

	//ʱ��ת������
	static CString SecToTime(int nSec);
protected:
	void InitCtrl();		//�Ի����ʼ���ؼ�
	void InitPlayer();		//��ʼ��������
	void InitPlayList();	//��ʼ�������б�
	void SavePlayList();	//���沥���б�
private:
	CMusicInfo		musicInfo;
	CListCtrl		m_listPlayList;
	int				m_nListCount;
	CMusicPlayer	m_player;

	PlayState		m_playState;
	LoopMode		m_loopMode;
	CString			m_strCurMusicPath;	//��ǰ���ŵĸ���
	std::vector<CMusicInfo>	m_vecPlayList;	//�����б�
	CSliderCtrl		m_sliderVolumn;
public:
	CSkinButton		m_btnPlay;
	CSliderCtrl		m_sliderProgress;
	//CBitmapSlider	m_sliderProgress;
	// ��������ʱ��
	CStatic			m_staticPlayTime;	//������ʱʹ��Ĭ�ϵ� static�ؼ���δ�ҵ����ʵĿؼ�
	int				m_nCurPlaySec;		//��ǰ����ʱ��
	bool			m_bPressProgressSlider;	//������½��Ȼ���
	CStatic			m_picSong;

	//���Խ���
	CDlgPlayControl	m_DlgPlayControl;
	CPlayListUI		m_DlgPlayList;
};
