
#pragma once

#include <string>
#include <atltypes.h>

using namespace std;

class StrUtil
{
public:

    static void trim( string& str )
    {
        int cnt = 0;
        while( str.at( cnt ) == ' ' ) ++cnt;
        if ( cnt ) str.erase( 0, cnt );
               
        int len = (int) (str.length() - 1);
        cnt     = len;
        while( str.at( cnt ) == ' ' ) --cnt;
        if ( cnt < len ) str.erase( 0, cnt );
    }

    static string getSubStr( string& line, char delim )
    {
        int pos = line.find( delim );
        if ( pos == string::npos )
            return "";

        string tmp = line.substr( 0, pos );
        line.erase( 0, pos + 1 );
        return tmp;
    }

    static string getSubStr( string& line, string delim )
    {
        int pos = line.find( delim );
        if ( pos == string::npos )
            return "";

        string tmp = line.substr( 0, pos );
        line.erase( 0, pos + delim.length() );
        return tmp;
    }

    // IDD_MFCGUIPORTAPP_DIALOG DIALOGEX 0, 0, 320, 200
    static void parseRect( string& line, CRect& rect )
    {
        string tmp  = getSubStr( line, ',' );
        rect.top    = atoi( tmp.c_str() );

        tmp         = getSubStr( line, ',' );
        rect.left   = atoi( tmp.c_str() );

        tmp         = getSubStr( line, ',' );
        rect.bottom = atoi( tmp.c_str() );
        
        if ( line.find( ',' ) != string::npos )
        {
            tmp         = getSubStr( line, ',' );
            rect.right  = atoi( tmp.c_str() );
        }
        else rect.right = atoi( line.c_str() );
    }

    // STYLE DS_SETFONT | DS_FIXEDSYS | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME
    static void parseStyles( string& line, vector<string>& styles )
    {
        while( line.length() )
        {
            if ( line.find( '|' ) != string::npos )
                styles.push_back( getSubStr( line, '|' ) );
            else
            {
                styles.push_back( line );
                line.clear();
            }
        }
    }
};

