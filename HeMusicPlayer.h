
// HeMusicPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHeMusicPlayerApp: 
// �йش����ʵ�֣������ HeMusicPlayer.cpp
//

class CHeMusicPlayerApp : public CWinApp
{
public:
	CHeMusicPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHeMusicPlayerApp theApp;