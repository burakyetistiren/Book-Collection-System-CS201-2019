#include <iostream>

using namespace std;

#include "SimpleGenre.h"

Genre::Genre( const string gname)
{
    genreName = gname;
}

Genre::Genre( const Genre &genreToCopy)
{
    genreName = genreToCopy.getGenreName();
}

Genre::~Genre()
{
//    if( genreName)
//        delete genreName;
}

void Genre::operator=( const Genre &right){}

string Genre::getGenreName() const
{
    return genreName;
}

void Genre::setGenreName(const string gName)
{
    genreName = gName;
}



