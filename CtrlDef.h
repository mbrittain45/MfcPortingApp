
#pragma once

#include <string>
#include <vector>
#include <atltypes.h>

using namespace std;


// the MFC Dlg Control Types
enum eCtrlType
{
    eUNK_CTRL = -1,
    eLISTBOX,
    eGROUPBOX,
    eICON, 
    eDEFPUSHBUTTON,  
    ePUSHBUTTON,
    eCOMBOBOX,
    eLTEXT,
    eRTEXT, 
    eCTEXT,  
    eEDITTEXT,
    eSCROLLBAR,
    eRichEdit20A,
    eSysListView32,
    eMsctlsTrackbar32,
    eGeneralButton,
    eSysTabControl32,
    eStatic,
    eMsctlsUpdown32,
    eComboBoxEx32,
    eMsctlsProgress32,
    eMsctlsHotkey32,
    eSysTreeView32,
    eSysAnimate32,
    eRichEdit20W,
    eSysDateTimePick32,
    eSysMonthCal32,
    eSysIPAddress32,
    eSysLink,
    eMsctlsNetaddress,
    eMfcButton,
    eMfcColorButton,
    eMfcEditBrowse,
    eMfcVSListBox,
    eMfcFontComboBox,
    eMfcMaskedEdit,
    eMfcMenuButton1,
    eMfcPropertyGrid,
    eMfcShellList,
    eMfcShellTree,
    eMfcLink,
    // buttons are marked as general then the parsing function decides on the proper type
    eRadioButton,
    eCheckBoxButton,
    eCUSTOM,        // a custom control ??? unknown to us
    eMAXCTRLTYPE
};



//
// A MFC Dialog Control Definition object
//
class CtrlDef
{
public:

    CtrlDef() 
    {
        m_type = eUNK_CTRL; 
    }
    
    CtrlDef(CtrlDef& rhs)
    {
        *this = rhs;
    }
    
    ~CtrlDef() { }

    CtrlDef& operator = ( const CtrlDef& rhs )
    {
        m_type  = rhs.m_type; 
        m_rect  = rhs.m_rect; 
        m_idc   = rhs.m_idc;  
        m_idr   = rhs.m_idr;  
        m_capt  = rhs.m_capt; 
        m_opts  = rhs.m_opts; 
        m_name  = rhs.m_name; 
        m_opts2 = rhs.m_opts2;
        return *this;
    }

    int getWidth()
    {
        return m_rect.right - m_rect.left;
    }

    void setWidth( int newWidth )
    {
        int width = getWidth();
        if ( width < newWidth )
            m_rect.right += (newWidth - width);
        else
            m_rect.right = (m_rect.left + newWidth);
    }

    // Note: not all values are set for any given control
    
    eCtrlType   m_type;     // control type
    CRect       m_rect;     // the controls CRect orientation   
    string      m_idc;      // IDC_ value as a string
    string      m_idr;      // IDR_ value as a string
    string      m_capt;     // the controls Caption string
    string      m_opts;     // the controls Options (ie WS_BORDER | WS_HSCROLL )
    string      m_name;     // complex control name
    string      m_opts2;    // the controls Options 2
};



//
// A MFC Dialog Control Parser object
//
class CtrlDefParser
{
public:

    static CtrlDef* parse( string line );

protected:

    // simple controls parsing functions
    static void parseLISTBOX( CtrlDef*, string line );
    static void parseGROUPBOX( CtrlDef*, string line );
    static void parseICON( CtrlDef*, string line );
    static void parsePUSHBUTTON( CtrlDef*, string line );
    static void parseCOMBOBOX( CtrlDef*, string line );
    static void parseTEXT( CtrlDef*, string line );
    static void parseEDITTEXT( CtrlDef*, string line );
    static void parseSCROLLBAR( CtrlDef*, string line );

    // complex controls parsing functions
    static void parseRichEdit20A( CtrlDef*, string line );
    static void parseSysListView32( CtrlDef*, string line );
    static void parseGeneralButton( CtrlDef*, string line );
    static void parseSysLink( CtrlDef*, string line );
    static void parseMsctlsNetaddress( CtrlDef*, string line );
    static void parseMfcControl( CtrlDef* pCtrl, string line );

    // func ptr def
    typedef void (*ParseFunc)( CtrlDef*, string );
    
    // our Ctrl Parser Def structure
    // the control name, the control type and the
    // function pointer to parse the CtrlDef
    struct CtrlParserDef
    {
        string    m_name;
        eCtrlType m_type;
        ParseFunc m_func;
    };
        
#define NumSimpleDefs 11
    static CtrlParserDef m_simpleCtrls[ NumSimpleDefs ];

#define NumComplexDefs 31
    static CtrlParserDef m_complexCtrls[ NumComplexDefs ]; 
};




