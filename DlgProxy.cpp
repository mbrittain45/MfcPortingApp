
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "MfcGuiPortApp.h"
#include "DlgProxy.h"
#include "MfcGuiPortAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcGuiPortAppDlgAutoProxy

IMPLEMENT_DYNCREATE(CMfcGuiPortAppDlgAutoProxy, CCmdTarget)

CMfcGuiPortAppDlgAutoProxy::CMfcGuiPortAppDlgAutoProxy()
{
	EnableAutomation();

	// To keep the application running as long as an automation
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMfcGuiPortAppDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMfcGuiPortAppDlg)))
		{
			m_pDialog = reinterpret_cast<CMfcGuiPortAppDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMfcGuiPortAppDlgAutoProxy::~CMfcGuiPortAppDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CMfcGuiPortAppDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMfcGuiPortAppDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMfcGuiPortAppDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IMfcGuiPortApp to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {07f3d1a8-ead7-40da-a704-91c944f43ceb}
static const IID IID_IMfcGuiPortApp =
{0x07f3d1a8,0xead7,0x40da,{0xa7,0x04,0x91,0xc9,0x44,0xf4,0x3c,0xeb}};

BEGIN_INTERFACE_MAP(CMfcGuiPortAppDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMfcGuiPortAppDlgAutoProxy, IID_IMfcGuiPortApp, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {0491098b-81e3-4eef-8af0-0633d2f73476}
IMPLEMENT_OLECREATE2(CMfcGuiPortAppDlgAutoProxy, "MfcGuiPortApp.Application", 0x0491098b,0x81e3,0x4eef,0x8a,0xf0,0x06,0x33,0xd2,0xf7,0x34,0x76)


// CMfcGuiPortAppDlgAutoProxy message handlers
