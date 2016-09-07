
// HeMusicPlayerDlg.h : ͷ�ļ�
//

#pragma once

#include "MusicInfo.h"
#include "afxcmn.h"
#include <vector>
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
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonPrevone();
	afx_msg void OnBnClickedButtonNextone();
	CSliderCtrl m_sliderVolumn;
	afx_msg void OnTRBNThumbPosChangingSliderVoice(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
