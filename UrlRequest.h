
// UrlRequest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUrlRequestApp: 
// �йش����ʵ�֣������ UrlRequest.cpp
//

class CUrlRequestApp : public CWinApp
{
public:
	CUrlRequestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUrlRequestApp theApp;