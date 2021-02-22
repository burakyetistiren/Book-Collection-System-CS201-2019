#include <iostream>
#include <string>

using namespace std;

#include "BookCollection.h"

BookCollection::BookCollection()
{
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

BookCollection::BookCollection(const BookCollection& bcToCopy):genreCount(bcToCopy.genreCount)
{
    if(bcToCopy.head)
    {
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
    else
        head = NULL;
}

void BookCollection::operator=(const BookCollection& right)
{
    if(right.head)
    {
        head = new GenreNode;

        head->g = Genre(right.head->g);

        GenreNode *newNode = head;
        for( GenreNode *cur = right.head->next; cur; cur = cur->next)
        {
            newNode->next = new GenreNode;
            newNode = newNode->next;
            newNode->g = Genre(cur->g);
        }
        newNode->next = NULL;

    }
    else
        head = NULL;
}

void BookCollection::addBook(string genreName, string bookName)
{
    string toBeAdded = toLower(bookName);
    string gnr = toLower(genreName);

    if( head)
    {
        GenreNode *curr = findGenre(gnr);

        if( curr)
            curr->g.addBook(toBeAdded);
        else
            cout << "Genre not found." << endl;
    }
    else
    {
        cout << "The genre list is empty." << endl;
    }
}

void BookCollection::removeBook(string genreName, string bookName)
{
    string gnr = toLower(genreName);
    string toBeRemoved = toLower(bookName);

    if( head)
    {
        GenreNode *curr = findGenre(gnr);
        if( curr)

            curr->g.removeBook(toBeRemoved);
        else
            cout << "Genre not found." << endl;
    }
    else
        cout << "There are no genres." << endl;
}

void BookCollection::displayAllGenres() const
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

void BookCollection::addGenre( string genreName)
{
	string toBeAdded = toLower(genreName);

    if( head)
    {
		GenreNode *newNode = new GenreNode;
        newNode->g.setGenreName( toBeAdded);

        if( !findGenre( toBeAdded))
        {
            GenreNode *curr = head;

            while( curr)
            {
                string temp = toLower(curr->g.getGenreName());

                if( !curr->next)
                {
                    curr->next = newNode;
                    newNode->next = NULL;
                    ++genreCount;
                    break;
                }
                curr->g.setGenreName(temp);
                curr = curr->next;
            }
        }

        else
        {
            cout << "Genre already exists in the collection." << endl;
        }
    }
    else
    {
        GenreNode *newNode = new GenreNode;
        (newNode->g).setGenreName( toBeAdded);

        head = newNode;
        head->next = NULL;
        ++genreCount;
    }
}

void BookCollection::removeGenre( string genreName)
{
    if( head)
    {
        GenreNode *curr = head;

        string toBeRemoved = toLower(genreName);
        curr = findGenre( toBeRemoved);

        if( !curr)
        {
            cout << "Genre does not exist in the collection." << endl;
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
        }
    }
    else
    {
        cout << "List is empty, cannot remove the requested genre." << endl;
    }
}

void BookCollection::addAuthor(string genreName, string bookName, int authorID, string authorName)
{
    string gnr = toLower(genreName);
    bookName = toLower(bookName);

    if( head)
    {
        GenreNode *curr = findGenre(gnr);

        if(curr)
        {
            if( curr->g.doesExist(bookName))
            {
                curr->g.retrieve( bookName)->addAuthor( authorID, authorName);
            }
            else
                cout << "Book not found." << endl;
        }
        else
            cout << "Genre not found." << endl;
    }
    else
        cout << "There are no genres." << endl;

}

void BookCollection::removeAuthor(string genreName, string bookName, int authorID)
{
    genreName = toLower(genreName);
    bookName = toLower(bookName);

    if( head)
    {
        GenreNode *curr = findGenre(genreName);

        if(curr)
        {
            if( curr->g.doesExist(bookName))
                curr->g.retrieve(bookName)->removeAuthor(authorID);
            else
                cout << "Book not found." << endl;
        }
        else
            cout << "Genre not found." << endl;
    }
    else
        cout << "There are no genres." << endl;
}

void BookCollection::displayGenre(string genreName)
{
    genreName = toLower(genreName);

    if( head)
    {
        GenreNode *curr = findGenre(genreName);
        if(curr)
        {
            cout << curr->g.getGenreName() << endl;
            curr->g.displayBooks();
        }
    }
    else
        cout << "   --EMPTY--" << endl;
}

void BookCollection::displayAuthor(int authorID)
{
    if( head)
    {
        cout << "Author: " << authorID;
        GenreNode *cur = head;
        //if(head->g.getAuthor(authorID))
            cout << head->g.getAuthor(authorID) << endl;
        while(cur)
        {
            cout << cur->g.getGenreName() << endl;
            cur->g.booksWithAuthor(authorID);
            cur = cur->next;
        }
    }
    else
        cout << "There are no genres." << endl;
}

string BookCollection::toLower( string s)
{
    string result = s;

    for ( unsigned int i = 0; i < result.length(); i++)
    {
        if ('a' <= result[i] && result[i] <= 'z')
            result[i] = char(((int)result[i]) - 32);
        if ('A' <= result[i] && result[i] <= 'Z')
            result[i] = char(((int)result[i]) + 32);
    }

    return result;
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName)
{
    genreName = toLower(genreName);

    if ( head)
    {
        GenreNode *curr = head;
        while(curr)
        {
            if( curr->g.getGenreName() == genreName)
                return curr;
            curr = curr->next;
        }
        delete curr;
    }
    return NULL;
}


