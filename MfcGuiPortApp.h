
// MfcGuiPortApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include <string>

using namespace std;

#include "IniFileParser.h"
#include "ResFileReader.h"


// CMfcGuiPortApp:
// See MfcGuiPortApp.cpp for the implementation of this class
//

class CMfcGuiPortApp : public CWinApp
{
public:
	CMfcGuiPortApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

    IniFileParser m_parser;
    ResFileReader m_resReader;

    map<string,vector<string>> m_rsrcs;

    string m_sDlgCaptionAddition;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMfcGuiPortApp theApp;
