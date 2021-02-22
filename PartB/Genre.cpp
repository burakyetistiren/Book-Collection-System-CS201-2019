#include <iostream>
#include "Genre.h"

using namespace std;

Genre::Genre(const string gname)
{
    genreName = gname;
    head = NULL;
}

Genre::~Genre()
{
    if( head)
        for( BookNode *curr = head; head != NULL; head = head->next)
        {
            head->next = curr->next;
            curr->next = NULL;
            delete curr;
            curr = head;
        }
}

Genre::Genre( const Genre& genreToCopy):genreName(genreToCopy.genreName)
{
    if( !genreToCopy.head)
    {
        head = NULL;
    }
    else
    {
        head = new BookNode;
        //head->b = genreToCopy.head->b;
        head->b = Book(genreToCopy.head->b);

        BookNode *newNode = head;
        for( BookNode *cur = genreToCopy.head->next; cur; cur = cur->next)
        {
            newNode->next = new BookNode;
            newNode = newNode->next;
            //newNode->b = cur->b;
            newNode->b = Book(cur->b);
        }
        newNode->next = NULL;
    }
}

void Genre::operator=(const Genre &right)
{
    if( !right.head)
    {
        head = NULL;
    }
    else
    {
        head = new BookNode;
        //head->b = right.head->b;
        head->b = Book(right.head->b);



        BookNode *newNode = head;
        for( BookNode *cur = right.head->next; cur; cur = cur->next)
        {
            newNode->next = new BookNode;
            newNode = newNode->next;
            //newNode->b = cur->b;
            newNode->b = Book(cur->b);
        }
        newNode->next = NULL;
    }
}

string Genre::getGenreName() const
{
    return genreName;
}

void Genre::setGenreName(const string bookName)
{
    genreName = bookName;
}

string Genre::getAuthor(int id)
{
    if( head)
    {
        BookNode *curr = head;
        while( curr)
        {
            if(curr->b.getAuthor(id) != " ")
                return curr->b.getAuthor(id);
            curr = curr->next;
        }
        return NULL;
    }
    return NULL;
}

void Genre::booksWithAuthor(int id)
{
    if( head)
    {
        BookNode *curr = head;
        while( curr)
        {
            curr->b.bookWithAuthor(id);
            curr = curr->next;
        }
    }
    else
        cout << "   -d-EMPTY--" << endl;
}

void Genre::displayBooks() const
{
        if( head)
        {
            BookNode *curr = head;
            while( curr)
            {
                cout << "book: " << curr->b.getName()<< endl;
                curr->b.displayAuthors();
                cout << endl;
                curr = curr->next;
            }
            delete curr;
            cout << endl;
        }
        else
            cout << "   --EMPTY--" << endl << endl;
}

bool Genre::addBook(const string bookName)
{
    if( head)
    {
        string toBeAdded = bookName;

        for ( unsigned int i = 0; i < toBeAdded.length(); i++)
        {
            if ('a' <= toBeAdded[i] && toBeAdded[i] <= 'z')
               toBeAdded[i] = char(((int)toBeAdded[i]) - 32);
            if ('A' <= toBeAdded[i] && toBeAdded[i] <= 'Z')
               toBeAdded[i] = char(((int)toBeAdded[i]) + 32);
        }

        BookNode *newNode = new BookNode;
        newNode->b.setName( toBeAdded);

        if( !findBook( toBeAdded))
        {
            BookNode *curr = head;

            while( curr)
            {
                string temp;
                temp = curr->b.getName();

                if( !curr->next)
                {
                    curr->next = newNode;
                    newNode->next = NULL;
                    break;
                }


                for ( unsigned int i = 0; i < temp.length(); i++)
                {
                    if ('a' <= temp[i] && temp[i] <= 'z')
                       temp[i] = char(((int)temp[i]) - 32);
                    if ('A' <= temp[i] && temp[i] <= 'Z')
                       temp[i] = char(((int)temp[i]) + 32);
                }
                curr->b.setName(temp);
                curr = curr->next;
            }
            //delete curr;
            //delete newNode;
        }

        else
        {
            cout << "Book already exists in the collection." << endl;
            return false;
        }
    }
    else
    {
        string toBeAdded = bookName;

        for ( unsigned int i = 0; i < toBeAdded.length(); i++)
        {
            if ('a' <= toBeAdded[i] && toBeAdded[i] <= 'z')
               toBeAdded[i] = char(((int)toBeAdded[i]) - 32);
            if ('A' <= toBeAdded[i] && toBeAdded[i] <= 'Z')
               toBeAdded[i] = char(((int)toBeAdded[i]) + 32);
        }

        BookNode *newNode = new BookNode;
        (newNode->b).setName( toBeAdded);

        head = newNode;
        head->next = NULL;
        //delete newNode;

        return true;
    }
    return false;
}

bool Genre::removeBook(const string bookName)
{
    if( head)
    {
        BookNode *curr = head;

        string toBeRemoved = bookName;

        for ( unsigned int i = 0; i < toBeRemoved.length(); i++)
        {
            if ('a' <= toBeRemoved[i] && toBeRemoved[i] <= 'z')
               toBeRemoved[i] = char(((int)toBeRemoved[i]) - 32);
            if ('A' <= toBeRemoved[i] && toBeRemoved[i] <= 'Z')
               toBeRemoved[i] = char(((int)toBeRemoved[i]) + 32);
        }

        curr = findBook( toBeRemoved);

        if( !curr)
        {
            cout << "Book does not exist in the collection." << endl;
            return false;
        }
        else
        {
            if( curr == head)
            {
                curr = head;
                head = head->next;
            }
            else
            {
                BookNode *prev = head;
                while( prev->next != curr)
                    prev = prev->next;
                curr = prev->next;
                prev->next = curr->next;

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

Genre::BookNode* Genre::findBook(string bookname)
{
    if( head)
    {
        BookNode* curr = head;
        while( curr)
        {
            if( curr->b.getName() == bookname)
                return curr;
            curr = curr->next;
        }
        delete curr;
    }
    else
        return NULL;
    return NULL;
}

Book* Genre::retrieve( string bookName)
{
    if(doesExist(bookName))
    {
        BookNode *cur = findBook(bookName);
        return &(cur->b);
    }
    return NULL;
}

bool Genre::doesExist( const string bookName) const
{
    if( head)
    {
        BookNode* curr = head;
        while( curr)
        {
            if( curr->b.getName() == bookName)
                return true;
            curr = curr->next;
        }
        delete curr;
    }
    else
        return false;
    return false;
}
