
// MfcGuiPortAppDlg.h : header file
//

#pragma once

class CMfcGuiPortAppDlgAutoProxy;


// CMfcGuiPortAppDlg dialog
class CMfcGuiPortAppDlg : public CDialog
{
	DECLARE_DYNAMIC(CMfcGuiPortAppDlg);
	friend class CMfcGuiPortAppDlgAutoProxy;

// Construction
public:
	CMfcGuiPortAppDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CMfcGuiPortAppDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGUIPORTAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CMfcGuiPortAppDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
};
