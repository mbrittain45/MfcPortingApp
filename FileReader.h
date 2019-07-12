
#pragma once

#include <string>
#include <fstream>

using namespace std;

class FileReader
{
public:

    FileReader()
    {
        m_bEof = false; 
        m_fin = nullptr; 
    }

    ~FileReader()
    {
        if ( m_fin )
        {
            m_fin->close();
            delete m_fin;
        }
        m_fin = nullptr;
    }

    bool openFile( string fname )
    {
        m_fname = fname;
        if ( m_fname.empty() )
            return false;
    
        m_fin = new ifstream( fname );   
        if ( ! m_fin->is_open() )
        {
            delete m_fin;
            m_fin = nullptr;
            return false;
        }

        return true;
    }

    string readLine()
    {
        m_bEof = m_fin->eof();
        if ( ! m_bEof )
        {
            memset( m_buf, ' ', _MAX_PATH );
            m_fin->getline( m_buf, _MAX_PATH, '\n' );
            return m_buf;
        }
        return "";
    }
        
    bool isEof() { return m_bEof; }

protected:

    bool m_bEof;
    string m_fname;
    char m_buf[ _MAX_PATH ];
    ifstream* m_fin;
};


