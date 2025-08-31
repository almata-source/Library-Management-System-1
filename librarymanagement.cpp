#include <iostream>

using namespace std;


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
