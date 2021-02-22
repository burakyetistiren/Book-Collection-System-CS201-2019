#include <iostream>
#include "Book.h"

#include <string>
using namespace std;

Book::Book()
{
    name = "";
    head = NULL;
}

Book::Book(const string name)
{
    this->name = name;
    head = NULL;
}

Book::Book(const Book& bookToCopy):name(bookToCopy.name)
{
    if( !bookToCopy.head)
    {
        head = NULL;
    }
    else
    {
        head = new AuthorNode;
        head->a = bookToCopy.head->a;
        head->a.setID(bookToCopy.head->a.getID());
        head->a.setName(bookToCopy.head->a.getName());

        AuthorNode *newNode = head;
        for( AuthorNode *cur = bookToCopy.head->next; cur; cur = cur->next)
        {
            newNode->next = new AuthorNode;
            newNode = newNode->next;
            newNode->a = cur->a;
            newNode->a.setID(cur->a.getID());
            newNode->a.setName(cur->a.getName());
        }
        newNode->next = NULL;
    }
}

void Book::operator=(const Book& right)
{
    if( !right.head)
    {
        head = NULL;
        name = right.name;
    }
    else
    {
        name = right.name;

        head = new AuthorNode;
        head->a = right.head->a;
        head->a.setID(right.head->a.getID());
        head->a.setName(right.head->a.getName());

        AuthorNode *newNode = head;
        for( AuthorNode *cur = right.head->next; cur; cur = cur->next)
        {
            newNode->next = new AuthorNode;
            newNode = newNode->next;
            newNode->a = cur->a;
            newNode->a.setID(cur->a.getID());
            newNode->a.setName(cur->a.getName());
        }
        newNode->next = NULL;
    }
}

Book::~Book()
{
    if( head)
    for( AuthorNode *curr = head; head != NULL; head = head->next)
    {
        head->next = curr->next;
        curr->next = NULL;
        delete curr;
        curr = head;
    }
}

string Book::getName() const
{
    return name;
}

void Book::bookWithAuthor( int id)
{
    AuthorNode *curr = findAuthor(id);
    if(curr)
    {
        cout << "   " << getName() << endl;
    }
}

string Book::getAuthor(int id)
{
    AuthorNode *curr = findAuthor(id);
    if(curr)
    {
        return curr->a.getName();
    }
    return "-i-EMPTY--";
}

void Book::setName(const string bookName)
{
    name = bookName;
}

bool Book::addAuthor(const int id, const string name)
{
    if ( head)
    {
        if( !findAuthor(id))
        {
            AuthorNode *newNode = new AuthorNode;
            newNode->a.setName( name);
            newNode->a.setID(id);

            newNode->next = head;
            head = newNode;

            return true;
        }
        else
        {
            cout << "Author already exists in the collection." << endl;
            return false;
        }
    }
    else
    {
        head = new AuthorNode;
        head->a.setID(id);
        head->a.setName(name);

        head->next = NULL;

        return true;
    }
    return false;
}

void Book::displayAuthors() const
{
    if( head)
    {
        AuthorNode *curr = head;
        while( curr)
        {
            cout << "   Author ID: " << curr->a.getID() << ", "
            << "Author name: " << curr->a.getName() << endl;
            curr = curr->next;
        }
        delete curr;
        cout << endl;
    }
        else
            cout << "--EMPTY--" << endl << endl;
}

Book::AuthorNode* Book::findAuthor(int id)
{
    if( head)
    {
        AuthorNode* curr = head;
        while( curr)
        {
            if( curr->a.getID() == id)
                return curr;
            curr = curr->next;
        }
        delete curr;
    }
    else
        return NULL;
    return NULL;
}

bool Book::removeAuthor(const int id)
{
    if( head)
    {
        AuthorNode *toBeRemoved = findAuthor(id);
        if( toBeRemoved)
        {
            if( toBeRemoved == head)
            {
                toBeRemoved = head;
                head = head->next;
            }
            else
            {
                AuthorNode *prev = head;
                while( prev->next != toBeRemoved)
                    prev = prev->next;
                toBeRemoved = prev->next;
                prev->next = toBeRemoved->next;
            }
                toBeRemoved->next = NULL;
                delete toBeRemoved;
                toBeRemoved = NULL;

                return true;
        }

        else
        {
            cout << "Author not found." << endl;
            return false;
        }
    }
    else
    {
        cout << "List is empty, cannot remove the requested author." << endl;
        return false;
    }
    return false;
}

