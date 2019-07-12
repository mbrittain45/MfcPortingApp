

#pragma once


#include <string>
#include <fstream>
#include <vector>

#include "FileReader.h"
#include "CtrlDef.h"


using namespace std;


class DlgDef
{
public:

    DlgDef() { }

    ~DlgDef()
    {
        for( auto it = m_ctrls.begin(); it != m_ctrls.end(); ++it )
            delete *it;
        m_ctrls.clear();
    }

    bool parse( string line, FileReader* pfr );

    int  getWidth() { return (m_rect.right - m_rect.left); }
    void incrWidth(){ ++m_rect.right; }

    void resizeControls();

    string m_idd;
    string m_exstyle;
    string m_capt;
    string m_font;
    CRect  m_rect;
    vector<string> m_styles;
    vector<CtrlDef*> m_ctrls;
};


class ResFileReader
{
public:

    ResFileReader(){ }
   
    ~ResFileReader()
    {
        for( auto it = m_dlgDefs.begin(); it != m_dlgDefs.end(); ++it )
            delete *it;
        m_dlgDefs.clear();
    }

    void             parseFile( FileReader* );
    vector<DlgDef*>* getDlgDefs() { return &m_dlgDefs; }

protected:
    
    string m_sLine;
    FileReader m_reader;
    vector<DlgDef*> m_dlgDefs;
};

