
// MfcGuiPortApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MfcGuiPortApp.h"
#include "MfcGuiPortAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcGuiPortApp

BEGIN_MESSAGE_MAP(CMfcGuiPortApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMfcGuiPortApp construction

CMfcGuiPortApp::CMfcGuiPortApp() : m_parser( "GuiPortDefs.ini" )
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMfcGuiPortApp object

CMfcGuiPortApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{0x604e458a,0xe3d1,0x4468,{0xb4,0x23,0x0e,0xcd,0xfa,0x29,0xa8,0x92}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CMfcGuiPortApp initialization

BOOL CMfcGuiPortApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	// Parse command line for automation or reg/unreg switches.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register class factories via CoRegisterClassObject().
		COleTemplateServer::RegisterAll();
	}
	// App was launched with /Unregserver or /Unregister switch.  Remove
	// entries from the registry.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

    if ( ! m_parser.readFile() )
    {
        assert( false );
        return false;
    }

    FileReader reader;
    if ( ! reader.openFile( "Dialogs.rc" ) )
    {
        assert( false );
        return false;
    }

    m_resReader.parseFile( &reader );
    
    vector<DlgDef*>* dlgDefs = m_resReader.getDlgDefs();

    for ( auto it = dlgDefs->begin(); it != dlgDefs->end(); ++it )
    {
        DlgDef* pDlg = *it;

        int addLen  = (pDlg->m_capt.length() / 2);
        while ( addLen > 6 ) pDlg->m_capt += ' ';
        pDlg->m_capt += ".....@";
        
        int halfWidth = (pDlg->getWidth() / 2);
        while ( pDlg->m_capt.length() >= halfWidth )
            pDlg->incrWidth();
    }
         
    for ( auto it = dlgDefs->begin(); it != dlgDefs->end(); ++it )
    {
        DlgDef* pDlg = *it;
        pDlg->resizeControls();
    }


    /*
	CMfcGuiPortAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	}


#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
    */

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CMfcGuiPortApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
