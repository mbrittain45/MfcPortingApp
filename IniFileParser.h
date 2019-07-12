
#pragma once


#include <string>
#include <map>
#include <vector>
#include <memory>
#include <fstream>


//
// This file parser works with .ini , .cfg and .properties files
//
// format: name=value
//
// Keys may (but need not) be grouped into arbitrarily named sections.
// [section name]
//
// Comments begin with ';' or '#' or '!' and can be an entire line or at the end of a key value pair line
//
// The following simple types for values are supported:
//
//      boolean:    value can be either true or false
//
//      decimal:    value can be integer.positiveInteger
//
//      directory:  value can be a string representing a file system path a platform-specific trailing directory separator
//                  will be added to the string if it doesn't already end with one - THE END USER MUST CHECK THIS.
//
//      file:       value can be a string representing a file system filename with optional path information; currently handled the same as string
//
//      fraction:   value can be the sequence integer/positiveInteger
//      number:     value can be decimal or fraction or integer
//      integer:    value can be a sequence of digits (0 through 9) with an optional leading minus (-)
//      positiveInteger: value can be a sequence of digits (0 through 9)
//
//      multilineString: a string that may contain end-of-line indicators (\); currently handled the same as string  - NOT SUPPORTED CURRENTLY
//
//      point:      value can be number@number
//
//      string:     value can be any sequence of adjacent characters except for the comment delimiter (;), array delimiter (,) and leading/trailing white space; to handle these exceptions, you can surround the sequence with single quote characters (and double any embedded single quote characters)
//
// The following complex types for value are supported:
//
//      array: value can be an array of simple values separated by the array delimiter (,) character. 
//  
//      range: value can be a number falling within the specified range of numbers; the specification supports including or excluding the end-points of the range.
//
//  NOTE: All values are treated as 'std::strings' at this level it is up to the end user
//        of the parser to do conversion to any of the other specific data types.
//


//
// objccts used to represent the ini file
//
class BaseFileLine
{
public:   
    BaseFileLine() { }
    virtual ~BaseFileLine(){ }
    virtual void setLine( std::string line = "" ) { }
    virtual std::string getLine() { return "\n"; }
};


//
// describes a comment file line
//
class CommentFileLine : public BaseFileLine
{
public:

    CommentFileLine( std::string comment ) : BaseFileLine() { m_comment = comment; }
    virtual ~CommentFileLine() { }
    virtual void setLine( std::string line = "" ) 
    {
        if ( ! line.empty() ) 
            m_comment = line;
    }
    virtual std::string getLine() { return (m_comment + BaseFileLine::getLine()); }

protected:
   
    std::string m_comment;
};


//
// describes a key value file line w/ possible ending comment
//
class KeyValueFileLine : public CommentFileLine
{
public:

    // ctor
    KeyValueFileLine() : CommentFileLine( "" ){ }

    // dtor
    virtual ~KeyValueFileLine() { }

    // set our line
    virtual void setLine( std::string line = "" );
    // get our line
    virtual std::string getLine()   { return (m_key + "=" + m_val + "    " + CommentFileLine::getLine()); }

    // get our key value
    std::string getKey()            { return m_key; }
    // get our value
    std::string getVal()            { return m_val; }
    // set our key
    void setKey(std::string key)    { m_key = key; }
    // set our value
    void setVal(std::string val)    { m_val = val; }

protected:
 
    std::string m_key;
    std::string m_val;
};


//
// define an Ini File Section object
//
class IniFileSection
{
public:

    // ctor
    IniFileSection( std::string name ) { m_name = name; }

    // dtor
    ~IniFileSection(){ }

    // get our section file line
    std::string getLine()
    {
        return std::string( "[" + m_name + "]\n" );
    }

    // add a line to our lines array
    void addLine( std::shared_ptr<BaseFileLine> bfl )
    {
        m_lines.push_back( bfl );
    }

    void addLine( std::shared_ptr<CommentFileLine> cfl )
    {
        m_lines.push_back( cfl );
    }

    void addLine( std::shared_ptr<KeyValueFileLine> kvfl )
    {
        m_lines.push_back( kvfl );
        m_keyValMap[ kvfl->getKey() ] = kvfl;
    }
    
    // see if we have a key
    bool hasKey( std::string key );
    // get a value by key
    std::string getValue( std::string key );
    // set a value by key
    void setValue( std::string key, std::string val );
    // write out our lines to a file
    void writeLines( std::ofstream* pOutStrm );
    // create a key value file line in a section
    void createKeyValue( std::string line );

protected:

    std::string m_name;
    std::vector<std::shared_ptr<BaseFileLine>> m_lines;

    // Note: any changes to the KeyValueFileLine object in this map will show up in the m_lines vector
    std::map<std::string, std::shared_ptr<KeyValueFileLine>> m_keyValMap;
};



//
// Ini File Parser
//
// which we can use to Read and Write an Ini file. Of course the
// is expected to be a normal ASCII text file
//
class IniFileParser
{
public:

    // ctor
    IniFileParser( std::string fileName ){ m_fileName = fileName; }
    // dtor
    virtual ~IniFileParser(){ }

    // read and parse the ini file
    bool readFile();
    // write the ini file back out
    bool writeFile();
    
    // get a value by section name and key name
    std::string getValue( std::string section, std::string key );
    // set a value by section name and key name
    bool setValue( std::string section, std::string key, std::string val );
    
protected:

    // create a new ini file section
    std::shared_ptr<IniFileSection> createSection( std::string name );
    // parse an ini file section name from '[ name ]'
    std::string parseSection( size_t startPos, std::string line );
  
    std::string m_fileName;
    std::vector<std::shared_ptr<IniFileSection>> m_sections;                // the file sections in order for recreating the file on ::writeFile()
    std::map<std::string, std::shared_ptr<IniFileSection>> m_sectionsMap;   // the file section map where the key is the section name
};
