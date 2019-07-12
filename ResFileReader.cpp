
#include "stdafx.h"

#include "ResFileReader.h"
#include "StrUtil.h"
#include "CtrlDef.h"


/*
IDD_MFCGUIPORTAPP_DIALOG DIALOGEX 0, 0, 320, 200
STYLE DS_SETFONT | DS_FIXEDSYS | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME
EXSTYLE WS_EX_APPWINDOW
CAPTION "Hello"
FONT 8, "MS Shell Dlg", 0, 0, 0x1
BEGIN
    DEFPUSHBUTTON   "OK",IDOK,209,179,50,14
    PUSHBUTTON      "Cancel",IDCANCEL,263,179,50,14
    CTEXT           "TODO: Place dialog controls here.",IDC_STATIC,10,96,300,8
END
*/

bool DlgDef::parse( string line, FileReader* pfr )
{
    m_idd  = StrUtil::getSubStr( line, ' ' );           // IDD_
    StrUtil::getSubStr( line, ' ' );                    // DIALOGEX
    StrUtil::parseRect( line, m_rect );
    
    line = pfr->readLine();
    StrUtil::getSubStr( line, ' ' );                    // STYLE
    StrUtil::parseStyles( line, m_styles );             // style1 | style2 ...
    
    string* pstr[] = { &m_exstyle, &m_capt, &m_font };
    for ( int i =0; i < 3; ++i )
    {
        line = pfr->readLine();
        StrUtil::getSubStr( line, ' ' );         
        *pstr[i] = line;
    }
    
    line = pfr->readLine();                             // BEGIN - beginning of controls contained in the Dialog
      
    // read and parse the controls
    while( ! pfr->isEof() )
    {
        line = pfr->readLine();      
        if ( line.find( "END" ) == string::npos )       // END - end of Dialog definition
            m_ctrls.push_back( CtrlDefParser::parse( line ) );
        else
            return true;
    }

    return false;
}

void DlgDef::resizeControls()
{
    vector<CtrlDef> changedCtlrs;
    
    for( auto it = m_ctrls.begin(); it != m_ctrls.end(); ++it )
    {
        CtrlDef* pCtrl = *it;
        
        if ( ! pCtrl->m_capt.empty() )
        {
            int len = pCtrl->m_capt.length();
            len += (len * .5);

            if ( len >= pCtrl->getWidth() )
            {
                pCtrl->setWidth( len + 10 );
                changedCtrls.push_back( pCtrl );
            }
        }

    }

    // now check all changed controls to make sure the dialog is still wide enough



}


//
// Resource File Reader
//
void ResFileReader::parseFile( FileReader* reader )
{
    while( ! reader->isEof() )
    {
        m_sLine = reader->readLine();
        
        if ( m_sLine.find( "DIALOGEX" ) != string::npos )
        {
            DlgDef* pDlg = new DlgDef(); 
            pDlg->parse( m_sLine, &m_reader );
            m_dlgDefs.push_back( pDlg );
        }
    }
}

