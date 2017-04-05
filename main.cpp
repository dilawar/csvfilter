/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Utility to parse csv file.
 *
 *        Version:  1.0
 *        Created:  04/05/2017 01:56:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>
#include <map>

using namespace std;
namespace po = boost::program_options;

char findDelimiters( string header )
{
    string allDelims = " ,\t;";
    char delim = ' ';
    for( size_t i = 0; i < allDelims.size( ); i++ )
    {
        delim = allDelims[ i ];
        if( header.find( delim ) != string::npos )
            return delim;
    }
    return delim;
}

template<typename Out>
void split(const std::string &s, char delim, Out result) 
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) 
    {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<boost::regex> split1(const std::string &s, char delim) 
{
    std::vector<boost::regex> elems;
    vector< string > tokens = split( s, delim );
    for( const string v : tokens )
    {
        boost::regex x( v );
        elems.push_back( x );
    }
    return elems;
}

bool isSelectedHeader( const vector<boost::regex> & regexs, const string& header )
{
    boost::cmatch m;

    bool match = false;
    for( size_t i = 0; i < regexs.size( ); i ++ )
    {
        match = boost::regex_match( header.c_str(), m, regexs[i] );
        if( match )
            break;
    }

    return match;
}

int main(int argc, const char *argv[])
{

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("infile,i", po::value<string>()->required(), "Input csv file")
        ("patterns,p", po::value<string>()->required(), "Regex pattern for columns")
        ("delimiter,d", po::value<char>()->default_value(' '), "Deleimiter")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    

    if( vm.count("help") )
    {
        cout << desc << "\n";
        return 1;
    }

    string filename = vm["infile"].as<string>();
    string patterns = vm["patterns"].as<string>();
    const char delim = vm[ "delimiter" ].as<char>();

    vector<boost::regex> headerRegex = split1( patterns, delim );

    // Now print the columns.
    ifstream dataF( filename.c_str() );
    string line;

    // First line is headers.
    getline( dataF, line);
    vector<string> headerVec = split( line, delim );

    // Print filtered header.
    string outline = "";
    for( size_t i = 0; i < headerVec.size(); i ++ )
        if( isSelectedHeader( headerRegex, headerVec[i] ) )
            outline += headerVec[ i ] + delim;
    outline.erase( outline.size() - 1);
    cout << outline << endl;

    // Now rest of the file.
    while( getline( dataF, line ) )
    {
        if( '#' == line[0] )
            continue;

        outline = "";
        vector<string> lineV = split( line, delim );

        for( size_t i = 0; i < headerVec.size(); i ++ )
            if( isSelectedHeader( headerRegex, headerVec[i] ) )
                outline += lineV[ i ] + delim;

        outline.erase( outline.size() - 1);
        cout << outline << endl;
    }

    return 0;
}

