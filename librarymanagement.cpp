#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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
};

	int parseMenuChoice(const string& line) {
	    stringstream ss(line);
	    int choice;
	    if (!(ss >> choice)) return -1;
	    char c;
	    if (ss >> c) return -1;
	    return choice;
	}
public:

    //register user
    void registerUser() {
    string id, name;
    cout << "Enter User ID: ";
    getline(cin, id);

    if (findUserIndexById(id) != -1) {
        cout << "User already exists!\n";
        return;
    }

    cout << "Enter User Name: ";
    getline(cin, name);

    users.emplace_back(id, name);
    cout << "User registered successfully!\n";

    //display user
    void displayUsers() const {
    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }
    cout << "--- Registered Users ---\n";
    for (const auto& u : users) {
        cout << "ID: " << u.userID << ", Name: " << u.name << "\n";
    }
    void addBook() {
    string id, title, author;
    cout << "Enter Book ID: ";
    getline(cin, id);

    if (findBookIndexById(id) != -1) {
        cout << "Book already exists!\n";
        return;
    }

    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);

    books.emplace_back(id, title, author, false);
    cout << "Book added successfully!\n";
}

    //borrow books
    void borrowBook() {
    string userId, bookId;
    cout << "Enter User ID: ";
    getline(cin, userId);
    int uIdx = findUserIndexById(userId);
    if (uIdx == -1) {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter Book ID: ";
    getline(cin, bookId);
    int bIdx = findBookIndexById(bookId);
    if (bIdx == -1) {
        cout << "Book not found!\n";
        return;
    }

    if (books[bIdx].isBorrowed) {
        cout << "Book is already borrowed!\n";
        return;
    }

    books[bIdx].isBorrowed = true;
    users[uIdx].borrowedBooks.push_back(bookId);
    cout << "Book borrowed successfully!\n";
    }
    void returnBook() {
    string userId, bookId;
    cout << "Enter User ID: ";
    getline(cin, userId);
    int uIdx = findUserIndexById(userId);
    if (uIdx == -1) {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter Book ID: ";
    getline(cin, bookId);
    int bIdx = findBookIndexById(bookId);
    if (bIdx == -1) {
        cout << "Book not found!\n";
        return;
    }

    auto& borrowed = users[uIdx].borrowedBooks;
    auto it = find(borrowed.begin(), borrowed.end(), bookId);
    if (it == borrowed.end()) {
        cout << "This user did not borrow that book.\n";
        return;
    }

    borrowed.erase(it);
    books[bIdx].isBorrowed = false;
    cout << "Book returned successfully!\n";
    }
    
    void returnBook() {
    string userId, bookId;
    cout << "Enter User ID: ";
    getline(cin, userId);
    int uIdx = findUserIndexById(userId);
    if (uIdx == -1) {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter Book ID: ";
    getline(cin, bookId);
    int bIdx = findBookIndexById(bookId);
    if (bIdx == -1) {
        cout << "Book not found!\n";
        return;
    }

    auto& borrowed = users[uIdx].borrowedBooks;
    auto it = find(borrowed.begin(), borrowed.end(), bookId);
    if (it == borrowed.end()) {
        cout << "This user did not borrow that book.\n";
        return;
    }

    borrowed.erase(it);
    books[bIdx].isBorrowed = false;
    cout << "Book returned successfully!\n";
}

    //return book
    void returnBook() {
    string userId, bookId;
    cout << "Enter User ID: ";
    getline(cin, userId);
    int uIdx = findUserIndexById(userId);
    if (uIdx == -1) {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter Book ID: ";
    getline(cin, bookId);
    int bIdx = findBookIndexById(bookId);
    if (bIdx == -1) {
        cout << "Book not found!\n";
        return;
    }

    auto& borrowed = users[uIdx].borrowedBooks;
    auto it = find(borrowed.begin(), borrowed.end(), bookId);
    if (it == borrowed.end()) {
        cout << "This user did not borrow that book.\n";
        return;
    }

    borrowed.erase(it);
    books[bIdx].isBorrowed = false;
    cout << "Book returned successfully!\n";
    }
}
}


//---MAIN---
int main() {
	Library lib;
	
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
        if (!getline(cin, line)) break;
        int choice = parseMenuChoice(line);
        if (choice < 1 || choice > 9) {
            cout << "Invalid choice!\n";
            continue;
        }
        if (choice == 9) { cout << "Exiting...\n"; break; }

        cout << "You chose option " << choice << endl;
        
        case 1: lib.registerUser(); break;
    }
}


