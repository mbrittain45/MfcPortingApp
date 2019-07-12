
#include "stdafx.h"
#include "CtrlDef.h"

#include "StrUtil.h"




//
// parse a control in a dialog
//
CtrlDef* CtrlDefParser::parse( string line )
{
    CtrlDef* pCtrl = new CtrlDef();

    string type = StrUtil::getSubStr( line, ' ' );
    if ( type == "CONTROL" )
    {
        for( int i = 0; i < NumComplexDefs; ++i )
        {
            if ( line.find( m_complexCtrls[i].m_name ) != string::npos )
            {
                pCtrl->m_type = m_complexCtrls[i].m_type;
                m_complexCtrls[i].m_func( pCtrl, line );
                return pCtrl;
            }
        }
    }
    else
    {
        for( int i = 0; i < NumSimpleDefs; ++i )
        {
            if ( type == m_simpleCtrls[i].m_name )
            {
                pCtrl->m_type = m_simpleCtrls[i].m_type;
                m_simpleCtrls[i].m_func( pCtrl, line );
                return pCtrl;
            }
        }
    }

    // if we are still here then we don't know the type of
    // control so pack it all into the options for later
    pCtrl->m_type = eCUSTOM;
    pCtrl->m_opts = line;
    
    return pCtrl;
}


//
// MFC Control definition names in the .rc file Control Parser parsing types
//

CtrlDefParser::CtrlParserDef CtrlDefParser::m_simpleCtrls[ NumSimpleDefs ] = 
{
    { "LISTBOX", eLISTBOX, &CtrlDefParser::parseLISTBOX },
    { "GROUPBOX", eGROUPBOX, &CtrlDefParser::parseGROUPBOX },
    { "ICON", eICON, &CtrlDefParser::parseICON },
    { "DEFPUSHBUTTON", eDEFPUSHBUTTON, &CtrlDefParser::parsePUSHBUTTON },
    { "PUSHBUTTON", ePUSHBUTTON, &CtrlDefParser::parsePUSHBUTTON },
    { "COMBOBOX", eCOMBOBOX, &CtrlDefParser::parseCOMBOBOX },
    { "LTEXT", eLTEXT, &CtrlDefParser::parseTEXT },
    { "RTEXT", eRTEXT, &CtrlDefParser::parseTEXT },
    { "CTEXT", eCTEXT, &CtrlDefParser::parseTEXT },
    { "EDITTEXT", eEDITTEXT, &CtrlDefParser::parseEDITTEXT },
    { "SCROLLBAR", eSCROLLBAR, &CtrlDefParser::parseSCROLLBAR }
};


// MFC Control definition names in the .rc file Comlpex Control Parser parsing types
CtrlDefParser::CtrlParserDef CtrlDefParser::m_complexCtrls[ NumComplexDefs ] = 
{
    { "RichEdit20A",        eRichEdit20A,       &CtrlDefParser::parseRichEdit20A },
    { "SysListView32",      eSysListView32,     &CtrlDefParser::parseSysListView32 },
    { "msctls_trackbar32",  eMsctlsTrackbar32,  &CtrlDefParser::parseMfcControl },
    { "Button",             eGeneralButton,     &CtrlDefParser::parseGeneralButton },  // various button types
    { "SysTabControl32",    eSysTabControl32,   &CtrlDefParser::parseMfcControl },
    { "Static",             eStatic,            &CtrlDefParser::parseMfcControl },
    { "msctls_updown32",    eMsctlsUpdown32,    &CtrlDefParser::parseMfcControl },
    { "ComboBoxEx32",       eComboBoxEx32,      &CtrlDefParser::parseMfcControl },
    { "msctls_progress32",  eMsctlsProgress32,  &CtrlDefParser::parseMfcControl },
    { "msctls_hotkey32",    eMsctlsHotkey32,    &CtrlDefParser::parseMfcControl },
    { "SysListView32",      eSysListView32,     &CtrlDefParser::parseSysListView32 },
    { "SysTreeView32",      eSysTreeView32,     &CtrlDefParser::parseMfcControl },
    { "SysTabControl32",    eSysTabControl32,   &CtrlDefParser::parseMfcControl },
    { "SysAnimate32",       eSysAnimate32,      &CtrlDefParser::parseMfcControl },
    { "RichEdit20W",        eRichEdit20W,       &CtrlDefParser::parseMfcControl },
    { "SysDateTimePick32",  eSysDateTimePick32, &CtrlDefParser::parseMfcControl }, 
    { "SysMonthCal32",      eSysMonthCal32,     &CtrlDefParser::parseMfcControl },
    { "SysIPAddress32",     eSysIPAddress32,    &CtrlDefParser::parseMfcControl },
    { "SysLink",            eSysLink,           &CtrlDefParser::parseSysLink },
    { "msctls_netaddress",  eMsctlsNetaddress,  &CtrlDefParser::parseMsctlsNetaddress },
    { "MfcButton",          eMfcButton,         &CtrlDefParser::parseMfcControl },
    { "MfcColorButton",     eMfcColorButton,    &CtrlDefParser::parseMfcControl },
    { "MfcEditBrowse",      eMfcEditBrowse,     &CtrlDefParser::parseMfcControl },
    { "MfcVSListBox",       eMfcVSListBox,      &CtrlDefParser::parseMfcControl },
    { "MfcFontComboBox",    eMfcFontComboBox,   &CtrlDefParser::parseMfcControl },
    { "MfcMaskedEdit",      eMfcMaskedEdit,     &CtrlDefParser::parseMfcControl },
    { "MfcMenuButton1",     eMfcMenuButton1,    &CtrlDefParser::parseMfcControl },
    { "MfcPropertyGrid",    eMfcPropertyGrid,   &CtrlDefParser::parseMfcControl },
    { "MfcShellList",       eMfcShellList,      &CtrlDefParser::parseMfcControl },
    { "MfcShellTree",       eMfcShellTree,      &CtrlDefParser::parseMfcControl },
    { "MfcLink",            eMfcLink,           &CtrlDefParser::parseMfcControl }
};


//-------------------------------------------------------------------------
//
// Comments Above the functions show which controls the function parsers
//
//-------------------------------------------------------------------------

// SCROLLBAR IDC_SCROLLBAR2,431,14,10,40,SBS_VERT
void CtrlDefParser::parseSCROLLBAR( CtrlDef* pCtrl, string line ) 
{
    pCtrl->m_idc = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
    pCtrl->m_opts = line;
}

// LISTBOX IDC_LIST1,29,121,115,40,LBS_SORT | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_TABSTOP
void CtrlDefParser::parseLISTBOX( CtrlDef* pCtrl, string line ) 
{
    pCtrl->m_idc = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
    pCtrl->m_opts = line;
}

// GROUPBOX  "Static",IDC_STATIC,192,28,96,58
void CtrlDefParser::parseGROUPBOX( CtrlDef* pCtrl, string line )
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}

// ICON IDR_MAINFRAME,IDC_STATIC,14,14,21,20
void CtrlDefParser::parseICON( CtrlDef* pCtrl, string line ) 
{
    pCtrl->m_idr = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}

// DEFPUSHBUTTON   "Save",IDOK,115,85,50,14
// PUSHBUTTON      "Save",IDOK,115,85,50,14
void CtrlDefParser::parsePUSHBUTTON( CtrlDef* pCtrl, string line )
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}

// COMBOBOX  IDC_CTED_CMB,54,48,107,84,CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_GROUP | WS_TABSTOP
void CtrlDefParser::parseCOMBOBOX( CtrlDef* pCtrl, string line ) 
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
    pCtrl->m_opts = line;
}

// LTEXT  "Name:",IDC_STATIC,13,50,35,8
// RTEXT  "Name:",IDC_STATIC,13,50,35,8
// CTEXT  "Name:",IDC_STATIC,13,50,35,8
void CtrlDefParser::parseTEXT( CtrlDef* pCtrl, string line ) 
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}

// EDITTEXT IDC_EDIT_COPY_DIRNAME,63,12,98,14,ES_AUTOHSCROLL
void CtrlDefParser::parseEDITTEXT( CtrlDef* pCtrl, string line ) 
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
    pCtrl->m_opts = line;
}

//    CONTROL         "Use Active Primary Study Set",IDC_PRIMARY_RADIO,"Button",BS_AUTORADIOBUTTON | WS_GROUP,12,133,109,10
//    CONTROL         "Delete Existing Contours",IDC_DELETE_EXISTING_CHECK,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,12,167,95,10
//    CONTROL         "Single Slice",IDC_SINGLE_SLICE_RADIO,"Button",BS_AUTORADIOBUTTON | WS_GROUP,12,20,65,10
//    CONTROL         "Check1",IDC_CHECK1,"Button",BS_AUTOCHECKBOX | WS_TABSTOP,38,19,39,10
//    CONTROL         "Radio1",IDC_RADIO1,"Button",BS_AUTORADIOBUTTON,248,23,38,10
void CtrlDefParser::parseGeneralButton( CtrlDef* pCtrl, string line )
{
    // set the proper button type
    if ( line.find( "BS_AUTOCHECKBOX" ) != string::npos )
        pCtrl->m_type = eCheckBoxButton;
    else
        pCtrl->m_type = eRadioButton;

    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    pCtrl->m_name = StrUtil::getSubStr( line, ',' );
    pCtrl->m_opts = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}

//    CONTROL         "",IDC_ADDITIONAL_PLAN_LIST,"SysListView32",LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | LVS_NOCOLUMNHEADER | WS_BORDER | WS_TABSTOP,25,70,177,78
void CtrlDefParser::parseSysListView32( CtrlDef* pCtrl, string line )
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    pCtrl->m_name = StrUtil::getSubStr( line, ',' );
    pCtrl->m_opts = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}

//    CONTROL         "",IDC_MC_RELATIVE_DOSE_THRESHOLD,"RichEdit20A",ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_TABSTOP,136,220,42,14,WS_EX_RIGHT
void CtrlDefParser::parseRichEdit20A( CtrlDef* pCtrl, string line )
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    pCtrl->m_name = StrUtil::getSubStr( line, ',' );
    pCtrl->m_opts = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
    pCtrl->m_opts2 = StrUtil::getSubStr( line, ',' );
}

//    CONTROL         "<a>SysLink1</a>",IDC_SYSLINK1,"SysLink",WS_TABSTOP,451,130,60,14
void CtrlDefParser::parseSysLink( CtrlDef* pCtrl, string line )
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    pCtrl->m_name = StrUtil::getSubStr( line, ',' );
    pCtrl->m_opts = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}

//    CONTROL         "",IDC_NETADDRESS1,"msctls_netaddress",ES_AUTOHSCROLL | WS_TABSTOP,29,170,70,14,WS_EX_CLIENTEDGE
void CtrlDefParser::parseMsctlsNetaddress( CtrlDef* pCtrl, string line )
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    pCtrl->m_name = StrUtil::getSubStr( line, ',' );
    pCtrl->m_opts = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
    pCtrl->m_opts2 = StrUtil::getSubStr( line, ',' );
}

//    CONTROL         "",IDC_SLIDER1,"msctls_trackbar32",TBS_BOTH | TBS_NOTICKS | WS_TABSTOP,21,47,100,15
//    CONTROL         "",IDC_STATIC,"Static",SS_BLACKFRAME,340,17,20,20
//    CONTROL         "",IDC_SPIN1,"msctls_updown32",UDS_ARROWKEYS,135,47,11,14
//    CONTROL         "",IDC_PROGRESS1,"msctls_progress32",WS_BORDER,162,49,80,14
//    CONTROL         "",IDC_HOTKEY1,"msctls_hotkey32",WS_BORDER | WS_TABSTOP,253,50,80,14
//    CONTROL         "",IDC_LIST1,"SysListView32",LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP,348,50,60,50
//    CONTROL         "",IDC_TREE1,"SysTreeView32",WS_BORDER | WS_HSCROLL | WS_TABSTOP,431,58,60,50
//    CONTROL         "",IDC_TAB1,"SysTabControl32",0x0,512,57,50,30
//    CONTROL         "",IDC_ANIMATE1,"SysAnimate32",WS_BORDER | WS_TABSTOP,27,89,20,20
//    CONTROL         "",IDC_RICHEDIT21,"RichEdit20W",ES_AUTOHSCROLL | WS_BORDER | WS_TABSTOP,72,91,40,14
//    CONTROL         "",IDC_DATETIMEPICKER1,"SysDateTimePick32",DTS_RIGHTALIGN | WS_TABSTOP,131,90,100,15
//    CONTROL         "",IDC_MONTHCALENDAR1,"SysMonthCal32",MCS_NOTODAY | MCS_NOTODAYCIRCLE | WS_TABSTOP,19,121,140,45
//    CONTROL         "",IDC_IPADDRESS1,"SysIPAddress32",WS_TABSTOP,181,125,100,15
//    CONTROL         "",IDC_COMBOBOXEX1,"ComboBoxEx32",CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | WS_TABSTOP,303,135,48,30
//    CONTROL         "MfcButton1",IDC_MFCBUTTON1,"MfcButton",WS_TABSTOP,245,180,50,14
//    CONTROL         "",IDC_MFCCOLORBUTTON1,"MfcColorButton",WS_TABSTOP,317,180,50,14
//    CONTROL         "",IDC_MFCEDITBROWSE1,"MfcEditBrowse",WS_BORDER | WS_TABSTOP | 0x80,386,182,80,14
//    CONTROL         "",IDC_MFCVSLISTBOX1,"MfcVSListBox",WS_TABSTOP,475,159,125,52
//    CONTROL         "",IDC_MFCFONTCOMBO1,"MfcFontComboBox",WS_VSCROLL | WS_TABSTOP | 0x312,27,233,48,30
//    CONTROL         "Sample-mask-0001",IDC_MFCMASKEDEDIT1,"MfcMaskedEdit",WS_BORDER | WS_TABSTOP | 0x80,94,234,80,14
//    CONTROL         "MfcMenuButton1",IDC_MFCMENUBUTTON1,"MfcMenuButton",WS_TABSTOP,190,228,80,14
//    CONTROL         "",IDC_MFCPROPERTYGRID1,"MfcPropertyGrid",0x100,271,230,140,56
//    CONTROL         "",IDC_MFCSHELLLIST1,"MfcShellList",WS_BORDER | WS_TABSTOP | 0x841,425,226,60,50
//    CONTROL         "",IDC_MFCSHELLTREE1,"MfcShellTree",WS_BORDER | WS_HSCROLL | WS_TABSTOP,502,224,60,50
//    CONTROL         "MfcLink1",IDC_MFCLINK1,"MfcLink",WS_TABSTOP,29,273,60,14
void CtrlDefParser::parseMfcControl( CtrlDef* pCtrl, string line )
{
    pCtrl->m_capt = StrUtil::getSubStr( line, ',' );
    pCtrl->m_idc  = StrUtil::getSubStr( line, ',' );
    pCtrl->m_name = StrUtil::getSubStr( line, ',' );
    pCtrl->m_opts = StrUtil::getSubStr( line, ',' );
    StrUtil::parseRect( line, pCtrl->m_rect );
}



