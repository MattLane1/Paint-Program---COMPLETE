
// Paint-Program.h : main header file for the Paint-Program application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPaintProgramApp:
// See Paint-Program.cpp for the implementation of this class
//

class CPaintProgramApp : public CWinApp
{
public:
	CPaintProgramApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPaintProgramApp theApp;
