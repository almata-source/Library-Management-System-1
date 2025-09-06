#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// para masure na hindi empty ang input
string getNonEmptyLine(const string& prompt) {
    string s;
    do {
        cout << prompt;
        if (!getline(cin, s)) return string();
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == string::npos) s = "";
        else {
            size_t b = s.find_last_not_of(" \t\r\n");
            s = s.substr(a, b - a + 1);
        }
        if (s.empty()) cout << "Input cannot be empty. Try again.\n";
    } while (s.empty());
    return s;
}

int parseMenuChoice(const string& line) {
    stringstream ss(line);
    int choice;
    if (!(ss >> choice)) return -1;
    char c;
    if (ss >> c) return -1;
    return choice;
}

// class Book
class Book {
public:
    string bookID;
    string title;
    string author;
    bool isBorrowed;

    Book(const string& id = "", const string& t = "", const string& a = "", bool b = false)
        : bookID(id), title(t), author(a), isBorrowed(b) {}
};

// class LibraryUser 
class LibraryUser {
public:
    string userID;
    string name;
    vector<string> borrowedBooks;

    LibraryUser(const string& id = "", const string& n = "") : userID(id), name(n) {}
};

// class Library
class Library {
private:
    vector<Book> books;
    vector<LibraryUser> users;

    int findUserIndexById(const string& id) const {
        for (int i = 0; i < (int)users.size(); ++i)
            if (users[i].userID == id) return i;
        return -1;
    }

    int findBookIndexById(const string& id) const {
        for (int i = 0; i < (int)books.size(); ++i)
            if (books[i].bookID == id) return i;
        return -1;
    }

public:
    // Load files into memory
    void loadFromFiles() {
        books.clear();
        users.clear();
        ifstream bf("books.txt");
        string line;
        if (bf.is_open()) {
            while (getline(bf, line)) {
                if (line.empty()) continue;
                size_t p1 = line.find('|');
                size_t p2 = (p1==string::npos) ? string::npos : line.find('|', p1+1);
                size_t p3 = (p2==string::npos) ? string::npos : line.find('|', p2+1);
                string id = (p1==string::npos) ? "" : line.substr(0, p1);
                string title = (p1==string::npos || p2==string::npos) ? "" : line.substr(p1+1, p2-p1-1);
                string author = (p2==string::npos || p3==string::npos) ? "" : line.substr(p2+1, p3-p2-1);
                string borrowedStr = (p3==string::npos) ? "0" : line.substr(p3+1);
                bool borrowed = (borrowedStr == "1");
                books.push_back(Book(id, title, author, borrowed));
            }
            bf.close();
        }

        ifstream uf("users.txt");
        if (uf.is_open()) {
            while (getline(uf, line)) {
                if (line.empty()) continue;
                size_t p1 = line.find('|');
                size_t p2 = (p1==string::npos) ? string::npos : line.find('|', p1+1);
                string id = (p1==string::npos) ? "" : line.substr(0, p1);
                string name, borrowedList;
                if (p2 == string::npos) {
                    if (p1 == string::npos) name = "";
                    else name = line.substr(p1+1);
                } else {
                    name = line.substr(p1+1, p2-p1-1);
                    borrowedList = line.substr(p2+1);
                }
                LibraryUser u(id, name);
                if (!borrowedList.empty()) {
                    size_t start = 0;
                    while (start < borrowedList.size()) {
                        size_t pos = borrowedList.find(',', start);
                        if (pos == string::npos) pos = borrowedList.size();
                        string bid = borrowedList.substr(start, pos - start);
                        if (!bid.empty()) u.borrowedBooks.push_back(bid);
                        start = pos + 1;
                    }
                }
                users.push_back(u);
            }
            uf.close();
        }
    }

    // save current data to files
    void saveToFiles() {
        ofstream bf("books.txt", ios::trunc);
        for (int i = 0; i < (int)books.size(); ++i)
            bf << books[i].bookID << "|" << books[i].title << "|" << books[i].author << "|" << (books[i].isBorrowed ? "1" : "0") << "\n";
        bf.close();

        ofstream uf("users.txt", ios::trunc);
        for (int i = 0; i < (int)users.size(); ++i) {
            uf << users[i].userID << "|" << users[i].name << "|";
            for (int j = 0; j < (int)users[i].borrowedBooks.size(); ++j) {
                if (j) uf << ",";
                uf << users[i].borrowedBooks[j];
            }
            uf << "\n";
        }
        uf.close();
    }

    // display all user ID
    void showUserIDs() const {
        if (users.empty()) { cout << "No users registered.\n"; return; }
        cout << "Available User IDs: ";
        for (int i = 0; i < (int)users.size(); ++i) {
            if (i) cout << ", ";
            cout << users[i].userID;
        }
        cout << "\n";
    }

    // display all book ID
    void showBookIDs() const {
        if (books.empty()) { cout << "No books available.\n"; return; }
        cout << "Available Book IDs: ";
        for (int i = 0; i < (int)books.size(); ++i) {
            if (i) cout << ", ";
            cout << books[i].bookID;
        }
        cout << "\n";
    }

    // register user
    void registerUser() {
        string id = getNonEmpty("Enter User ID: ");
        if (findUserIndexById(id) != -1) {
            cout << "User ID already exists. Registration cancelled.\n";
            return;
        }
        string name = getNonEmpty("Enter Name: ");
        users.push_back(LibraryUser(id, name));
        saveToFiles();
        cout << "User registered: " << name << " (ID: " << id << ")\n";
    }

    // remove user
    void removeUser() {
        showUserIDs();
        string id = getNonEmpty("Enter User ID to remove: ");
        int idx = findUserIndexById(id);
        if (idx == -1) { cout << "User not found.\n"; return; }
        if (!users[idx].borrowedBooks.empty()) {
            cout << "Cannot remove user: they still have borrowed books.\n";
            return;
        }
        cout << "Removing user: " << users[idx].name << " (ID: " << id << ")\n";
        users.erase(users.begin() + idx);
        saveToFiles();
    }
    
    // Display registered users
    void displayUsers() const {
        if (users.empty()) { cout << "No users registered.\n"; return; }
        cout << "\n=== Registered Users ===\n";
        for (int i = 0; i < (int)users.size(); ++i) {
            cout << "User ID: " << users[i].userID << ", Name: " << users[i].name << "\n  Borrowed: ";
            if (users[i].borrowedBooks.empty()) cout << "None";
            else {
                for (int j = 0; j < (int)users[i].borrowedBooks.size(); ++j) {
                    if (j) cout << ", ";
                    cout << users[i].borrowedBooks[j];
                }
            }
            cout << "\n";
        }
    }

    // adding book
    void addBook() {
        string id = getNonEmpty("Enter Book ID: ");
        if (findBookIndexById(id) != -1) {
            cout << "Book ID already exists. Add cancelled.\n";
            return;
        }
        string title = getNonEmpty("Enter Title: ");
        string author = getNonEmpty("Enter Author: ");
        books.push_back(Book(id, title, author, false));
        saveToFiles();
        cout << "Book added: " << title << " (ID: " << id << ")\n";
    }
    
    // removing/deleting book
    void removeBook() {
        showBookIDs();
        string id = getNonEmpty("Enter Book ID to remove: ");
        int idx = findBookIndexById(id);
        if (idx == -1) { cout << "Book not found.\n"; return; }
        if (books[idx].isBorrowed) {
            cout << "Cannot remove book: it's currently borrowed.\n";
            return;
        }
        cout << "Removing book: " << books[idx].title << " (ID: " << id << ")\n";
        books.erase(books.begin() + idx);
        saveToFiles();
    }
    
    // display list of books
    void displayBooks() const {
        if (books.empty()) { cout << "No books available.\n"; return; }
        cout << "\n=== Books in Library ===\n";
        for (int i = 0; i < (int)books.size(); ++i) {
            cout << "Book ID: " << books[i].bookID
                 << ", Title: " << books[i].title
                 << ", Author: " << books[i].author
                 << " [" << (books[i].isBorrowed ? "Borrowed" : "Available") << "]\n";
        }
    }

    // borrow book
    void borrowBook() {
        showUserIDs();
        string userID = getNonEmpty("Enter User ID: ");
        int uidx = findUserIndexById(userID);
        if (uidx == -1) { cout << "User not found.\n"; return; }

        showBookIDs();
        string bookID = getNonEmpty("Enter Book ID: ");
        int bidx = findBookIndexById(bookID);
        if (bidx == -1) { cout << "Book not found.\n"; return; }

        if (books[bidx].isBorrowed) { cout << "Book already borrowed.\n"; return; }

        for (int i = 0; i < (int)users[uidx].borrowedBooks.size(); ++i)
            if (users[uidx].borrowedBooks[i] == bookID) { cout << "User already borrowed this book.\n"; return; }

        books[bidx].isBorrowed = true;
        users[uidx].borrowedBooks.push_back(bookID);
        saveToFiles();
        cout << "Book borrowed: " << books[bidx].title << " by " << users[uidx].name << "\n";
    }
    
    // return book
    void returnBook() {
        showUserIDs();
        string userID = getNonEmpty("Enter User ID: ");
        int uidx = findUserIndexById(userID);
        if (uidx == -1) { cout << "User not found.\n"; return; }

        showBookIDs();
        string bookID = getNonEmpty("Enter Book ID: ");
        int pos = -1;
        for (int i = 0; i < (int)users[uidx].borrowedBooks.size(); ++i)
            if (users[uidx].borrowedBooks[i] == bookID) { pos = i; break; }

        if (pos == -1) { cout << "This user did not borrow that book.\n"; return; }

        users[uidx].borrowedBooks.erase(users[uidx].borrowedBooks.begin() + pos);

        int bidx = findBookIndexById(bookID);
        if (bidx != -1) books[bidx].isBorrowed = false;

        saveToFiles();
        cout << "Book returned: " << bookID << " by " << users[uidx].name << "\n";
    }
    
private:
    string getNonEmpty(const string& prompt) { return getNonEmptyLine(prompt); }
};

//---MAIN---
int main() {
    Library lib;
    lib.loadFromFiles();
    
    //menu
    while (true) {
        cout << "--- Library Management ---\n";
        cout << "1. Register User\n";
        cout << "2. Remove User\n";
        cout << "3. Display Users\n";
        cout << "4. Add Book\n";
        cout << "5. Remove Book\n";
        cout << "6. Display Books\n";
        cout << "7. Borrow Book\n";
        cout << "8. Return Book\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        string line;
        if (!getline(cin, line)) { lib.saveToFiles(); break; }

        int choice = parseMenuChoice(line);
        if (choice < 1 || choice > 9) { cout << "Invalid choice!\n"; continue; }

        switch (choice) {
            case 1: lib.registerUser(); break;
            case 2: lib.removeUser(); break;
            case 3: lib.displayUsers(); break;
            case 4: lib.addBook(); break;
            case 5: lib.removeBook(); break;
            case 6: lib.displayBooks(); break;
            case 7: lib.borrowBook(); break;
            case 8: lib.returnBook(); break;
            case 9: cout << "Exiting...\n"; lib.saveToFiles(); return 0;
        }
    }
}
