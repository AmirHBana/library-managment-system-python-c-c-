#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Person {
public:
    Person(string name, string phone) : name(name), phone(phone) {}
    string getName() { return name; }
    string getPhone() { return phone; }
private:
    string name;
    string phone;
};

class Member : public Person {
public:
    Member(int ID, int idm, string name, string phone) : Person(name, phone), ID(ID), idm(idm) {}
    int getID() { return ID; }
    int getIdm() { return idm; }
private:
    int ID;
    int idm;
};

class Book : public Person {
public:
    Book(int ISBN, string title, string author, string publisher, string language, int page, string Genres) : Person(title, author), ISBN(ISBN), title(title), author(author), publisher(publisher), language(language), page(page), Genres(Genres) {}
    int getISBN() { return ISBN; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getPublisher() { return publisher; }
    string getLanguage() { return language; }
    int getPage() { return page; }
    string getGenres() { return Genres; }
private:
    int ISBN;
    string title;
    string author;
    string publisher;
    string language;
    int page;
    string Genres;
};

class CodeBook {
public:
    CodeBook(string Genrestype, int codeofGenrestype) : Genrestype(Genrestype), codeofGenrestype(codeofGenrestype) {}
    string getGenrestype() { return Genrestype; }
    int getCodeofGenrestype() { return codeofGenrestype; }
private:
    string Genrestype;
    int codeofGenrestype;
};

class LendingBook : public Book {
public:
    LendingBook(int ISBN, int code, int idm, time_t time_get_book, time_t time_return_book) : Book(ISBN, "", "", "", "", 0, ""), code(code), idm(idm), time_get_book(time_get_book), time_return_book(time_return_book) {}
    int getCode() { return code; }
    int getIdm() { return idm; }
    time_t getTime_get_book() { return time_get_book; }
    time_t getTime_return_book() { return time_return_book; }
private:
    int code;
    int idm;
    time_t time_get_book;
    time_t time_return_book;
};

class Librarian : public Person {
public:
    Librarian(int ID, int idm, string name, string phone) : Person(name, phone), ID(ID), idm(idm) {}
    int getID() { return ID; }
    int getIdm() { return idm; }
    bool login() {
        string password;
        cout << "Enter password: ";
        cin >> password;
        if (password == "123456") {
            return true;
        }
        return false;
    }
    int menulibrarian() {
        int choice;
        cout << "\n LIBRARIAN MENU \n";
        cout << "1. Register Member \n";
        cout << "2. Add Book \n";
        cout << "3. Lend Book \n";
        cout << "4. Return Book \n";
        cout << "5. List of Members \n";
        cout << "6. List of Librarians \n";
        cout << "7. List of Books \n";
        cout << "8. Search Book \n";
        cout << "9. Update Member Information \n";
        cout << "10. Update Book Information \n";
        cout << "11. Exit \n";
        cout << "Enter your choice ...: ";
        cin >> choice;
        return choice;
    }
    void registermember() {
        int ID, idm;
        string name, phone;
        cout << "Enter ID: ";
        cin >> ID;
        cout << "Enter idm: ";
        cin >> idm;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter phone: ";
        cin >> phone;
        Member member(ID, idm, name, phone);
        cout << "Member Registered Successfully \n";
    }
    void addbook() {
        int ISBN;
        string title, author, publisher, language, Genres;
        int page;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        cout << "Enter title: ";
        cin >> title;
        cout << "Enter author: ";
        cin >> author;
        cout << "Enter publisher: ";
        cin >> publisher;
        cout << "Enter language: ";
        cin >> language;
        cout << "Enter page: ";
        cin >> page;
        cout << "Enter Genres: ";
        cin >> Genres;
        Book book(ISBN, title, author, publisher, language, page, Genres);
        cout << "Book Added Successfully \n";
    }
    void lendingbook() {
        int ISBN, code, idm;
        time_t time_get_book, time_return_book;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        cout << "Enter code: ";
        cin >> code;
        cout << "Enter idm: ";
        cin >> idm;
        time_get_book = time(0);
        time_return_book = time(0) + 14 * 24 * 60 * 60; // 14 days
        LendingBook lendingbook(ISBN, code, idm, time_get_book, time_return_book);
        cout << "Book Lended Successfully \n";
    }
    void returnbook() {
        int ISBN;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        cout << "Book Returned Successfully \n";
    }
    void listofmember() {
        cout << "List of Members \n";
        cout << "ID \t idm \t Name \t Phone \n";
    }
    void listoflibrarian() {
        cout << "List of Librarians \n";
        cout << "ID \t idm \t Name \t Phone \n";
    }
    void listofbook() {
        cout << "List of Books \n";
        cout << "ISBN \t Title \t Author \t Publisher \t Language \t Page \t Genres \n";
    }
    void searchbook() {
        int choice;
        string field;
        cout << "1. Title \n";
        cout << "2. Author \n";
        cout << "3. Publisher \n";
        cout << "Enter your choice ...: ";
        cin >> choice;
        if (choice == 1) {
            field = "title";
        }
        if (choice == 2) {
            field = "author";
        }
        if (choice == 3) {
            field = "publisher";
        }
        string title;
        cout << "Enter " << field << " Value: ";
        cin >> title;
        cout << "Search Result for: " << field << " : " << title << "\n";
    }
    void updatesmember() {
        int ID;
        string name, phone;
        cout << "Enter ID: ";
        cin >> ID;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter phone: ";
        cin >> phone;
        cout << "Member Information Updated Successfully \n";
    }
    void updatesbook() {
        int ISBN;
        string title, author, publisher, language, Genres;
        int page;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        cout << "Enter title: ";
        cin >> title;
        cout << "Enter author: ";
        cin >> author;
        cout << "Enter publisher: ";
        cin >> publisher;
        cout << "Enter language: ";
        cin >> language;
        cout << "Enter page: ";
        cin >> page;
        cout << "Enter Genres: ";
        cin >> Genres;
        cout << "Book Information Updated Successfully \n";
    }
private:
    int ID;
    int idm;
};

int main() {
    Librarian lib(982341347, 55478988, "Ali", "Amir hossien bana");
    bool log = lib.login();
    if (log == true) {
        while (true) {
            int choice = lib.menulibrarian();
            if (choice == 1) {
                lib.registermember();
            }
            if (choice == 2) {
                lib.addbook();
            }
            if (choice == 3) {
                lib.lendingbook();
            }
            if (choice == 4) {
                lib.returnbook();
            }
            if (choice == 5) {
                lib.listofmember();
            }
            if (choice == 6) {
                lib.listoflibrarian();
            }
            if (choice == 7) {
                lib.listofbook();
            }
            if (choice == 8) {
                lib.searchbook();
            }
            if (choice == 9) {
                lib.updatesmember();
            }
            if (choice == 10) {
                lib.updatesbook();
            }
            if (choice == 11) {
                break;
            }
        }
    }
    return 0;
}
