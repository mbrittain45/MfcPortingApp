
// DlgProxy.h: header file
//

#pragma once

class CMfcGuiPortAppDlg;


// CMfcGuiPortAppDlgAutoProxy command target

class CMfcGuiPortAppDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMfcGuiPortAppDlgAutoProxy)

	CMfcGuiPortAppDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CMfcGuiPortAppDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CMfcGuiPortAppDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMfcGuiPortAppDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

