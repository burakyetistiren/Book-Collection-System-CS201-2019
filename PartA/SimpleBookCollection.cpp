#include <iostream>

using namespace std;

#include "SimpleBookCollection.h"

BookCollection::BookCollection()
{
    name = "";
    genreCount = 0;
    head = NULL;
}

BookCollection::~BookCollection()
{
    if( head)
        for( GenreNode *curr = head; head != NULL; head = head->next)
        {
            head->next = curr->next;
            curr->next = NULL;
            delete curr;
            curr = head;
            --genreCount;
        }
}

BookCollection::BookCollection(const BookCollection& bcToCopy):name(bcToCopy.name)
{
    if( !bcToCopy.head)
    {
        head = NULL;
        genreCount = 0;
    }
    else
    {
        genreCount = bcToCopy.genreCount;

        head = new GenreNode;
        head->g = bcToCopy.head->g;
        head->g.setGenreName(bcToCopy.head->g.getGenreName());

        GenreNode *newNode = head;
        for( GenreNode *cur = bcToCopy.head->next; cur; cur = cur->next)
        {
            newNode->next = new GenreNode;
            newNode = newNode->next;
            newNode->g = cur->g;
            newNode->g.setGenreName(cur->g.getGenreName());
        }
        newNode->next = NULL;
    }
}

BookCollection::GenreNode* BookCollection::findGenre( string genreName)
{
    if( head)
    {
        GenreNode* curr = head;
        while( curr)
        {
            if( curr->g.getGenreName() == genreName)
                return curr;
            curr = curr->next;
        }
        delete curr;
    }
    else
        return NULL;
    return NULL;
}

void BookCollection::operator=(const BookCollection& right)
{
    if( !right.head)
    {
        head = NULL;
        genreCount = 0;
        name = right.name;
    }
    else
    {
        genreCount = right.genreCount;
        name = right.name;

        head = new GenreNode;
        head->g = right.head->g;
        head->g.setGenreName(right.head->g.getGenreName());

        GenreNode *newNode = head;
        for( GenreNode *cur = right.head->next; cur; cur = cur->next)
        {
            newNode->next = new GenreNode;
            newNode = newNode->next;
            newNode->g = cur->g;
            newNode->g.setGenreName(cur->g.getGenreName());
        }
        newNode->next = NULL;
    }
}

void BookCollection::displayGenres() const
{
        if( head)
        {
            GenreNode *curr = head;
            while( curr)
            {
               cout << "genre: " << curr->g.getGenreName() << endl;
               curr = curr->next;
            }
            delete curr;
            cout << endl;
        }
        else
            cout << "--EMPTY--" << endl << endl;
}

bool BookCollection::addGenre( const string genreName)
{
    if( head)
    {
        string toBeAdded = genreName;

        for ( unsigned int i = 0; i < toBeAdded.length(); i++)
        {
            if ('a' <= toBeAdded[i] && toBeAdded[i] <= 'z')
               toBeAdded[i] = char(((int)toBeAdded[i]) - 32);
            if ('A' <= toBeAdded[i] && toBeAdded[i] <= 'Z')
               toBeAdded[i] = char(((int)toBeAdded[i]) + 32);
        }

        GenreNode *newNode = new GenreNode;
        newNode->g.setGenreName( toBeAdded);

        if( !findGenre( toBeAdded))
        {
            GenreNode *curr = head;

            while( curr)
            {
                string temp;
                temp = curr->g.getGenreName();

                if( !curr->next)
                {
                    curr->next = newNode;
                    newNode->next = NULL;
                    ++genreCount;
                    break;
                }


                for ( unsigned int i = 0; i < temp.length(); i++)
                {
                    if ('a' <= temp[i] && temp[i] <= 'z')
                       temp[i] = char(((int)temp[i]) - 32);
                    if ('A' <= temp[i] && temp[i] <= 'Z')
                       temp[i] = char(((int)temp[i]) + 32);
                }
                curr->g.setGenreName(temp);
                curr = curr->next;
            }
            //delete curr;
            //delete newNode;
        }

        else
        {
            cout << "Genre already exists in the collection." << endl;
            return false;
        }
    }
    else
    {
        string toBeAdded = genreName;

        for ( unsigned int i = 0; i < toBeAdded.length(); i++)
        {
            if ('a' <= toBeAdded[i] && toBeAdded[i] <= 'z')
               toBeAdded[i] = char(((int)toBeAdded[i]) - 32);
            if ('A' <= toBeAdded[i] && toBeAdded[i] <= 'Z')
               toBeAdded[i] = char(((int)toBeAdded[i]) + 32);
        }

        GenreNode *newNode = new GenreNode;
        (newNode->g).setGenreName( toBeAdded);

        head = newNode;
        head->next = NULL;
        ++genreCount;
        //delete newNode;

        return true;
    }
    return false;
}

bool BookCollection::removeGenre(const string genreName)
{
    if( head)
    {
        GenreNode *curr = head;

        string toBeRemoved = genreName;

        for ( unsigned int i = 0; i < toBeRemoved.length(); i++)
        {
            if ('a' <= toBeRemoved[i] && toBeRemoved[i] <= 'z')
               toBeRemoved[i] = char(((int)toBeRemoved[i]) - 32);
            if ('A' <= toBeRemoved[i] && toBeRemoved[i] <= 'Z')
               toBeRemoved[i] = char(((int)toBeRemoved[i]) + 32);
        }

        curr = findGenre( toBeRemoved);

        if( !curr)
        {
            cout << "Genre does not exist in the collection." << endl;
            return false;
        }
        else
        {
            if( curr == head)
            {
                curr = head;
                head = head->next;
                --genreCount;
            }
            else
            {
                GenreNode *prev = head;
                while( prev->next != curr)
                    prev = prev->next;
                curr = prev->next;
                prev->next = curr->next;
                --genreCount;

            }
            curr->next = NULL;
            delete curr;
            curr = NULL;

            return true;
        }
    }
    else
    {
        cout << "List is empty, cannot remove the requested genre." << endl;
        return false;
    }
    return false;
}

string BookCollection::getName() const
{
    return name;
}

void BookCollection::setName(const string bcName)
{
    name = bcName;
}




