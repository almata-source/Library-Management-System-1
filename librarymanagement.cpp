#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Book {
public:
    string bookID;
    string title;
    string author;
    bool isBorrowed;

    Book(const string& id = "", const string& t = "", const string& a = "", bool b = false)
        : bookID(id), title(t), author(a), isBorrowed(b) {}
};

class LibraryUser {
public:
    string userID;
    string name;
    vector<string> borrowedBooks;

    LibraryUser(const string& id = "", const string& n = "") : userID(id), name(n) {}
};

//---MAIN---
int main() {



    while (true) {
        cout<< "--- Library Management ---";
        cout<< "1. Register User\n";
        cout<< "2.Remove User\n";
        cout<< "3. Display Users\n";
        cout << "4. Add Book\n";
        cout << "5. Remove Book\n";
    }
}
