
// SpartyCrossing.h : main header file for the SpartyCrossing application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


/**
 *  SpartyCrossing App
 */
class CSpartyCrossingApp : public CWinApp
{
public:
	CSpartyCrossingApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken = 0;
};

extern CSpartyCrossingApp theApp;
