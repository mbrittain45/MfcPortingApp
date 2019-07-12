
#include "stdafx.h"

#include "IniFileParser.h"
#include "StrUtil.h"

#include <fstream>


using namespace std;


//
// helper function to get the comment position if there is one
//
size_t findCommentPosition( string line )
{
    size_t commentPos = string::npos;

    // .ini and .cfg and .properties comment characters
    char commentChars[3] = { ';', '#', '!' }; 
    
    // check the line for each of the chars stop at first match
    for( int i = 0; i < 3; ++i )
    {
        commentPos = line.find( commentChars[i] );
        if ( commentPos != string::npos )
            return commentPos;
    }

    return commentPos;
}


//
// parse a key value pair file line with possible ending comment
//
void KeyValueFileLine::setLine( std::string line )
{
    // find the key value delimiter
    size_t pos = line.find( "=" );
    if ( pos == string::npos )
    {   
        // should  never happen..of course
        assert( false ); return;
    }

    // parse out the key 
    m_key = line.substr( 0, pos );
    StrUtil::trim( m_key );
    line.erase( 0, (pos + 1) );

    // see if there is a comment in the line
    size_t commentPos = findCommentPosition( line );
    if ( commentPos != string::npos )
    {
        // parse the value 
        m_val = line.substr( 0, commentPos );
        StrUtil::trim( m_val );

        // remove the value to leave the comment only
        line.erase( 0, commentPos );
        m_comment = ("    " + line);
    }
    else
    {
        // no comment so the line is just the value
        m_val = line;
        StrUtil::trim( m_val );
    }
}


//
// Ini File Section object
//
bool IniFileSection::hasKey( std::string key )
{
    auto mit = m_keyValMap.find( key );
    return (mit != m_keyValMap.end());
}

std::string IniFileSection::getValue( std::string key )
{
    auto mit = m_keyValMap.find( key );
    if ( mit != m_keyValMap.end() )
    {
        shared_ptr<KeyValueFileLine> kvfl = mit->second;
        return kvfl->getVal();
    }
    return "";
}

void IniFileSection::setValue( std::string key, std::string val )
{
    auto mit = m_keyValMap.find( key );
    if ( mit != m_keyValMap.end() )
    {
        shared_ptr<KeyValueFileLine> kvfl = mit->second;
        kvfl->setVal( val );
    }
    else
    {   // add the unknown key and value
        shared_ptr<KeyValueFileLine> kvfl( new KeyValueFileLine() );
        kvfl->setKey( key );
        kvfl->setVal( val );
        m_keyValMap[key] = kvfl;
    }
}

// write out all the lines in a section to an output file
void IniFileSection::writeLines( ofstream* pOutStrm )
{
    // write the formatted INI section [name] out
    string tmp = getLine();
    pOutStrm->write( tmp.c_str(), tmp.length() );
  
    // write out each line in the section
    auto lit = m_lines.begin();
    for ( ; lit != m_lines.end(); ++lit )
    {
        tmp = lit->get()->getLine();
        pOutStrm->write( tmp.c_str(), tmp.length() );
    }
}

// create a key value file line in a section
void IniFileSection::createKeyValue( string line )
{
    shared_ptr<KeyValueFileLine> kvfl( new KeyValueFileLine() );
    kvfl->setLine( line );
    addLine( kvfl );
}
            


//
// Ini File Parser object
//
// which is used to read and write a given ini file
// See the particular Ini file for notes about the file specifics
//
 
// get a value by section name and key
std::string IniFileParser::getValue( std::string section, std::string key )
{
    auto sit = m_sectionsMap.find( section );
    if ( sit != m_sectionsMap.end() )
        return sit->second->getValue( key );

    assert( false ); return "";
}

// set a value by section name and key
bool IniFileParser::setValue( std::string section, std::string key, std::string val )
{
    auto sit = m_sectionsMap.find( section );
    if ( sit != m_sectionsMap.end() )
    {
        sit->second->setValue( key, val );
        return true;
    }

    assert( false ); return false;
}

// create a new ini file section
shared_ptr<IniFileSection> IniFileParser::createSection( string name )
{   
    // see if we already have an section w/ that name
    auto fit = m_sectionsMap.find( name );
    if ( fit != m_sectionsMap.end() )
        return fit->second;
    
    // create a new section and put in order and on the map
    shared_ptr<IniFileSection> pSection( new IniFileSection( name ) );
    m_sections.push_back( pSection );
    m_sectionsMap[ name ] = pSection;
    
    return pSection;
}


// parse an ini file section name from '[ name ]'
string IniFileParser::parseSection( size_t startPos, string line )
{       
    size_t endPos = line.find( "]" );
    if ( endPos == string::npos )
        return "";
        
    string section = line.substr( (startPos + 1), (endPos - 1) );
    StrUtil::trim( section );
    return section;
}


// read and parse the ini file
bool IniFileParser::readFile()
{
    string buffer;

    // open the file
    ifstream inStrm( m_fileName );
    if ( ! inStrm.is_open() )
        return false;

    // start off with a blank section name
    shared_ptr<IniFileSection> pCurSection = createSection( "" );
    
    // read the entire file
    while ( std::getline( inStrm, buffer ) )
	{
        // if empty line put a place holder in the section
        if ( buffer.empty() )
        {
            pCurSection->addLine( shared_ptr<BaseFileLine>( new BaseFileLine() ) );
            continue;
        }

        // if its a section create the section by name
        size_t sectionPos = buffer.find( "[" );
        if ( sectionPos != string::npos )
        {
            pCurSection = createSection( parseSection( sectionPos, buffer ) );
            continue;
        }

        // get the comment position and key value delimiter position
        size_t cmmntPos = findCommentPosition( buffer );
        size_t delimPos = buffer.find( "=" );

        // see if its a comment or a key value pair. Key value pairs are still allowed
        // to have comments at the end of the line and its still a key value object.
        if ( cmmntPos != string::npos ) 
        {
            if ( delimPos == string::npos )
                pCurSection->addLine( shared_ptr<BaseFileLine>( new CommentFileLine( buffer ) ) );
            else if ( delimPos < cmmntPos )
                pCurSection->createKeyValue( buffer );
            else
            {   // the comment is before the key = value so it becomes a comment
                pCurSection->addLine( shared_ptr<BaseFileLine>( new CommentFileLine( buffer ) ) );
            }
        }
        else
        {
            pCurSection->createKeyValue( buffer );
        }
    }

    // close the file
    inStrm.close();
    return true;
}


//
// write the ini file back out in the proper order
//
bool IniFileParser::writeFile()
{
    // open the fresh output file
    ofstream outStrm( m_fileName, (ios_base::trunc | ios_base::out) );
   if ( ! outStrm.is_open() )
        return false;

    // write out all of our entries to the file in the same order
    for( auto fsmIt = m_sections.begin(); fsmIt != m_sections.end(); ++fsmIt )
    {
        fsmIt->get()->writeLines( &outStrm );
    }

    // close the file
    outStrm.close();
    return true;
}

