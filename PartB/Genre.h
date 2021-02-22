#ifndef __GENRE_H
#define __GENRE_H

#include "Book.h"
#include <string>

using namespace std;

class Genre {
public:
    Genre( const string gname = "");
    ~Genre();
    Genre( const Genre &genreToCopy);
    void operator=(const Genre &right);
    void booksWithAuthor(int id);
    string getGenreName() const;
    string getAuthor(int id);
    void setGenreName(const string gName);
    void displayBooks() const;
    bool addBook(const string bookName);
    bool removeBook(const string bookName);
    bool doesExist(const string bookName) const;
    Book* retrieve( string bookName);
private:
    struct BookNode
    {
        Book b;
        BookNode* next;
    };
    string genreName;
    BookNode* head;
    BookNode* findBook(string bookName);
};
#endif
