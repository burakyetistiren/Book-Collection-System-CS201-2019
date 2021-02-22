#include <iostream>
#include "Author.h"

using namespace std;

Author::Author()
{
    name = "";
    id = -1;
}

Author::Author(const int id, const string name)
{
    this->id = id;
    this->name = name;
}

int Author::getID() const
{
    return id;
}

void Author::setID(const int id)
{
    this->id = id;
}

string Author::getName() const
{
    return name;
}

void Author::setName(const string id)
{
    name = id;
}
