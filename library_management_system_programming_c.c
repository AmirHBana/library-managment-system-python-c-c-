#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <mysql/mysql.h>
#include <time.h>
#include "prettytable.h"

typedef struct {
    char name[50];
    char phone[20];
} person;

typedef struct {
    int ID;
    int code;
    char username[50];
    char password[50];
    person librarian;
} librarian;

person* create_person(const char* name, const char* phone) {
    person* p = (person*) malloc(sizeof(person));
    strcpy(p->name, name);
    strcpy(p->phone, phone);
    return p;
}

librarian* create_librarian(int ID, int code, const char* username, const char* password, const char* name, const char* phone) {
    librarian* l = (librarian*) malloc(sizeof(librarian));
    l->ID = ID;
    l->code = code;
    strcpy(l->username, username);
    strcpy(l->password, password);
    l->librarian = *create_person(name, phone);
    return l;
}

int login(const char* host, const char* user, const char* passwd, const char* database) {
    mysql.connect(
        host,
        user,
        passwd,
        database
    );
    mysql.cursor();
    // Perform login validation here
    // Return 1 if successful, 0 if not
}

void menu(librarian* lib) {
    // Implement menu here
}



// Define the person and librarian structs here
// Define the create_person and create_librarian functions here

void registermember(const char* host, const char* user, const char* passwd, const char* database) {
    MYSQL* db = mysql_init(NULL);
    mysql_real_connect(db, host, user, passwd, database, 0, NULL, 0, NULL);

    char name[50];
    char idm[20];
    char phone[20];

    printf("Enter Member Name :");
    scanf("%s", name);
    printf("Enter Member ID :");
    scanf("%s", idm);
    printf("Enter Member Phone  :");
    scanf("%s", phone);

    char sql[200];
    sprintf(sql, "insert into member(name,idm,phone) values ('%s','%s','%s')", name, idm, phone);
    mysql_query(db, sql);

    mysql_close(db);
}

void addbook(const char* host, const char* user, const char* passwd, const char* database) {
    MYSQL* db = mysql_init(NULL);
    mysql_real_connect(db, host, user, passwd, database, 0, NULL, 0, NULL);

    char ISBN[20];
    char title[50];
    char author[50];
    char publisher[50];
    char language[20];
    int page;
    char Genres[50];

    printf("Enter ISBN :");
    scanf("%s", ISBN);
    printf("Enter Title of the book :");
    scanf("%s", title);
    printf("Enter author name of the book :");
    scanf("%s", author);
    printf("Enter Publisher of the book :");
    scanf("%s", publisher);
    printf("Enter language of the book :");
    scanf("%s", language);
    printf("Enter number pages of the book :");
    scanf("%d", &page);
    printf("Enter Genres type of the book :");
    scanf("%s", Genres);

    char sql[300];
    sprintf(sql, "insert into book(ISBN,title,author,publisher,language,page,Genres,status) values ('%s','%s','%s','%s','%s',%d,'%s','available')", ISBN, title, author, publisher, language, page, Genres);
    mysql_query(db, sql);

    mysql_close(db);
}


// Function to connect to the database
MYSQL *db_connect() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "127.0.0.1", "root", "", "library system", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

// Function to update member details
void update_member(MYSQL *conn, int idm, char *field, char *value) {
    char sql[256];
    sprintf(sql, "UPDATE member SET %s = '%s' WHERE idm = %d;", field, value, idm);
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("Member details Updated.....\n");
}

// Function to check member issue status
MYSQL_RES *check_issue_status(MYSQL *conn, int idm) {
    char sql[256];
    sprintf(sql, "SELECT * FROM lending WHERE idm = %d AND time_return_book IS NULL;", idm);
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return mysql_use_result(conn);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int idm, sh;
    char field[50], value[50];

    conn = db_connect();

    system("cls");
    printf("%s%s UPdates Memeber %s\n", "\033[1;37m", "\033[44m", "\033[0m");
    printf("%s\n", "--------------------------------------------------------");
    printf("%s\n", "1. name");
    printf("%s\n", "2. phone");
    scanf("%d", &sh);

    if (sh == 1) {
        strcpy(field, "name");
    } else if (sh == 2) {
        strcpy(field, "phone");
    }

    printf("%s", "Enter member ID :");
    scanf("%d", &idm);
    printf("%s", "Enter new value :");
    scanf("%s", value);

    update_member(conn, idm, field, value);

    result = check_issue_status(conn, idm);

    printf("%s\n", "Issue Status:");
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%s\n", row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return 0;
}


MYSQL *conn;
MYSQL_RES *result;
MYSQL_ROW row;

MYSQL_RES *check_issue_status(MYSQL *conn, int idm, char *ISBN) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char sql[200];

    sprintf(sql, "SELECT * FROM lending WHERE ISBN = '%s' AND idm = %d AND time_return_book IS NULL;", ISBN, idm);
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    result = mysql_store_result(conn);
    return result;
}

void update_member(MYSQL *conn, int idm, char *field, char *value) {
    char sql[200];

    sprintf(sql, "UPDATE member SET %s = '%s' WHERE idm = %d;", field, value, idm);
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

MYSQL *db_connect() {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }

    if (mysql_real_connect(conn, "127.0.0.1", "root", "", "library system", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

int main() {
    int sh, idm;
    char ISBN[50], field[50], value[50];

    conn = db_connect();

    system("cls");
    printf("%s%s UPdates Memeber %s\n", "\033[1;37m", "\033[44m", "\033[0m");
    printf("%s\n", "--------------------------------------------------------");
    printf("%s\n", "1. name");
    printf("%s\n", "2. phone");
    scanf("%d", &sh);

    if (sh == 1) {
        strcpy(field, "name");
    } else if (sh == 2) {
        strcpy(field, "phone");
    }

    printf("%s", "Enter member ID :");
    scanf("%d", &idm);
    printf("%s", "Enter new value :");
    scanf("%s", value);

    update_member(conn, idm, field, value);

    result = check_issue_status(conn, idm, ISBN);

    printf("%s\n", "Issue Status:");
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%s\n", row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return 0;
}


// Function to establish a connection with the MySQL server
MYSQL *connect_to_db() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
    if (mysql_real_connect(conn, "127.0.0.1", "root", "", "library system", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

// Function to execute a SQL query
int execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed\n");
        return 1;
    }
    return 0;
}

// Function to fetch the book status from the database
int book_status(MYSQL *conn, const char *ISBN) {
    char query[100];
    sprintf(query, "SELECT status FROM book WHERE ISBN = %s", ISBN);
    if (execute_query(conn, query)) {
        return -1;
    }
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        return -1;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        return -1;
    }
    int status = strcmp(row[0], "available") == 0 ? 0 : 1;
    mysql_free_result(result);
    return status;
}

// Function to fetch the member's issue status from the database
int mem_issue_status(MYSQL *conn, const char *idm) {
    char query[100];
    sprintf(query, "SELECT COUNT(*) FROM lending WHERE idm = %s", idm);
    if (execute_query(conn, query)) {
        return -1;
    }
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        return -1;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        return -1;
    }
    int status = atoi(row[0]);
    mysql_free_result(result);
    return status;
}

// Function to lend a book to a member
void lendingbook(MYSQL *conn) {
    char ISBN[20], idm[20];
    printf("\n BOOK Lending to Member \n");
    printf("-------------------------------------------------------------\n");
    printf("Enter Book  ISBN : ");
    scanf("%s", ISBN);
    printf("Enter Member ID : ");
    scanf("%s", idm);

    int result = book_status(conn, ISBN);
    int result_1 = mem_issue_status(conn, idm);

    time_t now = time(NULL);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d", localtime(&now));

    if (result_1 == 1) {
        if (result == 0) {
            char query[200];
            sprintf(query, "INSERT INTO lending(ISBN, idm, time_get_book) VALUES('%s', '%s', '%s')", ISBN, idm, date);
            if (execute_query(conn, query)) {
                printf("\n Book issued successfully\n");
            } else {
                printf("\nBook is not available for ISSUE... Current status : %s\n", result_1 == 0 ? "available" : "issue");
            }
        }
    } else {
        if (result_1 < 5) {
            char query[200];
            sprintf(query, "INSERT INTO lending(ISBN, idm, time_get_book) VALUES('%s', '%s', '%s')", ISBN, idm, date);
            if (execute_query(conn, query)) {
                printf("\n\n\n Book issued successfully\n");
            }
        } else {
            printf("\nMember already have book from the Library\n");
        }
    }
}

int main() {
    MYSQL *conn = connect_to_db();
    if (conn == NULL) {
        return 1;
    }
    lendingbook(conn);
    mysql_close(conn);
    return 0;
}


// Function to establish a connection with the MySQL server
MYSQL *connect_to_db() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
    if (mysql_real_connect(conn, "127.0.0.1", "root", "", "library system", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

// Function to fetch the book status
void book_status(MYSQL *conn, char *ISBN) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[100];
    sprintf(query, "SELECT status FROM book WHERE ISBN = '%s';", ISBN);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed\n");
        return;
    }
    result = mysql_store_result(conn);
    if (result) {
        while ((row = mysql_fetch_row(result))) {
            printf("Book status: %s\n", row[0]);
        }
        mysql_free_result(result);
    }
}

// Function to fetch the member's issue status
void member_issue_status(MYSQL *conn, char *idm) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[100];
    sprintf(query, "SELECT status FROM member WHERE id = '%s';", idm);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed\n");
        return;
    }
    result = mysql_store_result(conn);
    if (result) {
        while ((row = mysql_fetch_row(result))) {
            printf("Member issue status: %s\n", row[0]);
        }
        mysql_free_result(result);
    }
}

// Function to lend a book to a member
void lendingbook(MYSQL *conn) {
    char ISBN[20], idm[20];
    printf("Enter Book ISBN: ");
    scanf("%s", ISBN);
    printf("Enter Member ID: ");
    scanf("%s", idm);
    book_status(conn, ISBN);
    member_issue_status(conn, idm);
    if (strcmp("available", "select * from book where status = available") == 0) {
        printf("Book was not issued...Check book ISBN and Member ID again..\n");
    } else {
        char query1[100], query_book[100];
        time_t now = time(0);
        char *dt = ctime(&now);
        dt[strcspn(dt, "\n")] = '\0';
        sprintf(query1, "INSERT INTO lending(time_return_book) VALUES('%s');", dt);
        sprintf(query_book, "UPDATE book SET status = 'available' WHERE ISBN = '%s';", ISBN);
        if (mysql_query(conn, query1)) {
            fprintf(stderr, "mysql_query() failed\n");
            return;
        }
        if (mysql_query(conn, query_book)) {
            fprintf(stderr, "mysql_query() failed\n");
            return;
        }
        printf("\nBook returned successfully\n");
    }
}

int main() {
    MYSQL *conn = connect_to_db();
    if (conn == NULL) {
        return 1;
    }
    lendingbook(conn);
    mysql_close(conn);
    return 0;
}



MYSQL *connect_to_db() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
    if (mysql_real_connect(conn, "127.0.0.1", "root", "", "library system", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

void listofmember(MYSQL *conn) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    if (mysql_query(conn, "SELECT * FROM member")) {
        fprintf(stderr, "mysql_query() failed\n");
        return;
    }
    result = mysql_store_result(conn);
    if (result) {
        prettytable table;
        prettytable_init(&table);
        int num_fields = mysql_num_fields(result);
        MYSQL_FIELD *fields = mysql_fetch_fields(result);
        for (int i = 0; i < num_fields; i++) {
            prettytable_add_column(&table, fields[i].name);
        }
        while ((row = mysql_fetch_row(result))) {
            prettytable_add_row(&table, row);
        }
        prettytable_print(&table);
        prettytable_destroy(&table);
        mysql_free_result(result);
    }
}

int main() {
    MYSQL *conn = connect_to_db();
    if (conn == NULL) {
        return 1;
    }
    listofmember(conn);
    mysql_close(conn);
    return 0;
}


MYSQL *connect_to_db() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
    if (mysql_real_connect(conn, "127.0.0.1", "root", "", "library system", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

void listoflibrarian(MYSQL *conn) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    if (mysql_query(conn, "SELECT * FROM librarian")) {
        fprintf(stderr, "mysql_query() failed\n");
        return;
    }
    result = mysql_store_result(conn);
    if (result) {
        prettytable table;
        prettytable_init(&table);
        int num_fields = mysql_num_fields(result);
        MYSQL_FIELD *fields = mysql_fetch_fields(result);
        for (int i = 0; i < num_fields; i++) {
            prettytable_add_column(&table, fields[i].name);
        }
        while ((row = mysql_fetch_row(result))) {
            prettytable_add_row(&table, row);
        }
        prettytable_print(&table);
        prettytable_destroy(&table);
        mysql_free_result(result);
    }
}

int main() {
    MYSQL *conn = connect_to_db();
    if (conn == NULL) {
        return 1;
    }
    listoflibrarian(conn);
    mysql_close(conn);
    return 0;
}


MYSQL *connect_to_db() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }
    if (mysql_real_connect(conn, "127.0.0.1", "root", "", "library system", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

void listofbook(MYSQL *conn) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    if (mysql_query(conn, "SELECT * FROM book")) {
        fprintf(stderr, "mysql_query() failed\n");
        return;
    }
    result = mysql_store_result(conn);
    if (result) {
        prettytable table;
        prettytable_init(&table);
        int num_fields = mysql_num_fields(result);
        MYSQL_FIELD *fields = mysql_fetch_fields(result);
        for (int i = 0; i < num_fields; i++) {
            prettytable_add_column(&table, fields[i].name);
        }
        while ((row = mysql_fetch_row(result))) {
            prettytable_add_row(&table, row);
        }
        prettytable_print(&table);
        prettytable_destroy(&table);
        mysql_free_result(result);
    }
}

int main() {
    MYSQL *conn = connect_to_db();
    if (conn == NULL) {
        return 1;
    }
    listofbook(conn);
    mysql_close(conn);
    return 0;
}


void searchbook() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "127.0.0.1";
    char *user = "root";
    char *password = "";
    char *database = "library system";
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    int choice;
    printf("\n%s%s S E A R C H   M E N U %s\n", "\033[1;37m", "\033[44m", "\033[0m");
    printf("\n%s1.  Book Title%s\n", "\033[31m", "\033[0m");
    printf("\n%s2.  Book Author%s\n", "\033[35m", "\033[0m");
    printf("\n%s3.  Publisher%s\n", "\033[33m", "\033[0m");
    printf("\n");
    scanf("%d", &choice);
    char field[50];
    if (choice == 1) {
        strcpy(field, "title");
    } else if (choice == 2) {
        strcpy(field, "author");
    } else if (choice == 3) {
        strcpy(field, "publisher");
    }
    char title[100];
    printf("\nEnter %s Value : ", field);
    scanf("%s", title);
    char query[200];
    sprintf(query, "select * from book where %s like '%%%s%%'", field, title);
    mysql_query(conn, query);
    res = mysql_use_result(conn);
    system("cls");
    printf("\n BOOK SEARCH SCREEN\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("\nSearch Result for : %s : %s\n", field, title);
    printf("--------------------------------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s %s %s %s\n", row[0], row[1], row[2], row[3]);
    }
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    searchbook();
    return 0;
}


// Structures
typedef struct {
    char name[50];
    char phone[15];
} person;

typedef struct {
    int ID;
    int idm;
    person p;
} affiliatesofmember;

typedef struct {
    char ISBN[20];
    char title[50];
    char author[50];
    char publisher[50];
    char language[20];
    int page;
    char Genres[50];
} bookitem;

typedef struct {
    bookitem b;
} book;

typedef struct {
    char Genrestype[50];
    char codeofGenrestype[20];
} codebook;

typedef struct {
    char ISBN[20];
    char code[20];
    int idm;
    char time_get_book[50];
    char time_return_book[50];
} lendingbook;

// Functions
void print_book(book b) {
    printf("\033[1;32m%s\033[0m\n", b.b.title);
    printf("\033[1;33m%s\033[0m\n", b.b.author);
    printf("\033[1;34m%s\033[0m\n", b.b.publisher);
    printf("\033[1;35m%s\033[0m\n", b.b.language);
    printf("\033[1;36m%d\033[0m\n", b.b.page);
    printf("\033[1;37m%s\033[0m\n", b.b.Genres);
}

void searchbook(MYSQL *conn, char *ISBN) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[200];

    sprintf(query, "SELECT * FROM books WHERE ISBN = '%s'", ISBN);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    result = mysql_use_result(conn);
    if (result) {
        while ((row = mysql_fetch_row(result))) {
            book b;
            strcpy(b.b.ISBN, row[0]);
            strcpy(b.b.title, row[1]);
            strcpy(b.b.author, row[2]);
            strcpy(b.b.publisher, row[3]);
            strcpy(b.b.language, row[4]);
            b.b.page = atoi(row[5]);
            strcpy(b.b.Genres, row[6]);
            print_book(b);
        }
        mysql_free_result(result);
    }
}

int main() {
    MYSQL *conn;
    char *server = "localhost";
    char *user = "root";
    char *password = "password"; // use your own password
    char *database = "library";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char ISBN[20];
    printf("Enter ISBN: ");
    scanf("%s", ISBN);
    searchbook(conn, ISBN);

    mysql_close(conn);
    return 0;
}


typedef struct {
    int id;
    int phone;
    char name[50];
    char address[100];
} Member;

typedef struct {
    int id;
    char title[50];
    char author[50];
    int quantity;
    int issued;
} Book;

typedef struct {
    int member_id;
    int book_id;
    char lend_date[20];
    char return_date[20];
} Lending;

typedef struct {
    int id;
    char username[50];
    char password[50];
} Librarian;

void registermember(MYSQL *conn);
void addbook(MYSQL *conn);
void lendingbook(MYSQL *conn);
void returnbook(MYSQL *conn);
void listofmember(MYSQL *conn);
void listoflibrarian(MYSQL *conn);
void listofbook(MYSQL *conn);
void searchbook(MYSQL *conn, char *ISBN);
void updatesmember(MYSQL *conn);
void updatesbook(MYSQL *conn);

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int choice;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "password", "library", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    while (1) {
        printf("\n1. Register Member\n");
        printf("2. Add Book\n");
        printf("3. Lend Book\n");
        printf("4. Return Book\n");
        printf("5. List of Members\n");
        printf("6. List of Librarians\n");
        printf("7. List of Books\n");
        printf("8. Search Book\n");
        printf("9. Update Member\n");
        printf("10. Update Book\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registermember(conn);
                break;
            case 2:
                addbook(conn);
                break;
            case 3:
                lendingbook(conn);
                break;
            case 4:
                returnbook(conn);
                break;
            case 5:
                listofmember(conn);
                break;
            case 6:
                listoflibrarian(conn);
                break;
            case 7:
                listofbook(conn);
                break;
            case 8: {
                char ISBN[20];
                printf("Enter ISBN: ");
                scanf("%s", ISBN);
                searchbook(conn, ISBN);
                break;
            }
            case 9:
                updatesmember(conn);
                break;
            case 10:
                updatesbook(conn);
                break;
            case 11:
                goto exit;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

exit:
    mysql_close(conn);
    return 0;
}

void registermember(MYSQL *conn) {
    Member member;
    char query[200];

    printf("Enter member details:\n");
    printf("ID: ");
    scanf("%d", &member.id);
    printf("Phone: ");
    scanf("%d", &member.phone);
    printf("Name: ");
    scanf("%s", member.name);
    printf("Address: ");
    scanf("%s", member.address);

    sprintf(query, "INSERT INTO members(id, phone, name, address) VALUES(%d, %d, '%s', '%s')", member.id, member.phone, member.name, member.address);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Member registered successfully.\n");
}

void addbook(MYSQL *conn) {
    Book book;
    char query[200];

    printf("Enter book details:\n");
    printf("ID: ");
    scanf("%d", &book.id);
    printf("Title: ");
    scanf("%s", book.title);
    printf("Author: ");
    scanf("%s", book.author);
    printf("Quantity: ");
    scanf("%d", &book.quantity);
    printf("Issued: ");
    scanf("%d", &book.issued);

    sprintf(query, "INSERT INTO books(id, title, author, quantity, issued) VALUES(%d, '%s', '%s', %d, %d)", book.id, book.title, book.author, book.quantity, book.issued);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Book added successfully.\n");
}

void lendingbook(MYSQL *conn) {
    int member_id, book_id;
    char lend_date[20];
    char query[200];

    printf("Enter member ID: ");
    scanf("%d", &member_id);
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    printf("Enter lend date (DD-MM-YYYY): ");
    scanf("%s", lend_date);

    sprintf(query, "INSERT INTO lendings(member_id, book_id, lend_date) VALUES(%d, %d, '%s')", member_id, book_id, lend_date);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    sprintf(query, "UPDATE books SET issued = issued + 1 WHERE id = %d", book_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Book lent successfully.\n");
}

void returnbook(MYSQL *conn) {
    int member_id, book_id;
    char return_date[20];
    char query[200];

    printf("Enter member ID: ");
    scanf("%d", &member_id);
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    printf("Enter return date (DD-MM-YYYY): ");
    scanf("%s", return_date);

    sprintf(query, "INSERT INTO returns(member_id, book_id, return_date) VALUES(%d, %d, '%s')", member_id, book_id, return_date);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    sprintf(query, "UPDATE books SET issued = issued - 1 WHERE id = %d", book_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Book returned successfully.\n");
}

void listofmember(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];

    sprintf(query, "SELECT * FROM members");
    mysql_query(conn, query);
    res = mysql_use_result(conn);

    printf("ID\tPhone\tName\tAddress\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
    }

    mysql_free_result(res);
}

void listoflibrarian(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];

    sprintf(query, "SELECT * FROM librarians");
    mysql_query(conn, query);
    res = mysql_use_result(conn);

    printf("ID\tUsername\tPassword\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }

    mysql_free_result(res);
}

void listofbook(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];

    sprintf(query, "SELECT * FROM books");
    mysql_query(conn, query);
    res = mysql_use_result(conn);

    printf("ID\tTitle\tAuthor\tQuantity\tIssued\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
    }

    mysql_free_result(res);
}

void searchbook(MYSQL *conn, char *ISBN) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];

    sprintf(query, "SELECT * FROM books WHERE ISBN = '%s'", ISBN);
    mysql_query(conn, query);
    res = mysql_use_result(conn);

    if (mysql_num_rows(res) == 0) {
        printf("No book found with ISBN %s.\n", ISBN);
    } else {
        printf("ID\tTitle\tAuthor\tQuantity\tIssued\n");
        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
        }
    }

    mysql_free_result(res);
}

void updatesmember(MYSQL *conn) {
    int member_id;
    char name[50];
    char address[100];
    char query[200];

    printf("Enter member ID: ");
    scanf("%d", &member_id);
    printf("Enter new name: ");
    scanf("%s", name);
    printf("Enter new address: ");
    scanf("%s", address);

    sprintf(query, "UPDATE members SET name = '%s', address = '%s' WHERE id = %d", name, address, member_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Member updated successfully.\n");
}

void updatesbook(MYSQL *conn) {
    int book_id;
    char title[50];
    char author[50];
    int quantity;
    char query[200];

    printf("Enter book ID: ");
    scanf("%d", &book_id);
    printf("Enter new title: ");
    scanf("%s", title);
    printf("Enter new author: ");
    scanf("%s", author);
    printf("Enter new quantity: ");
    scanf("%d", &quantity);

    sprintf(query, "UPDATE books SET title = '%s', author = '%s', quantity = %d WHERE id = %d", title, author, quantity, book_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Book updated successfully.\n");
}
