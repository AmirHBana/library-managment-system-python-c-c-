
from genericpath import exists
from hashlib import sha1
from logging import LoggerAdapter
from multiprocessing.connection import wait
from re import X
from secrets import choice
from attr import s
import mysql.connector as mysql
import colored
from colored import stylize
from colored import fg, bg, attr
import getpass
import os
import time
fine_per_day =1.0

from datetime import date, datetime
from numpy import False_, True_, logical_not
from prettytable import from_db_cursor
from prettytable import prettytable

class person:
    def __init__(self, name, phone) -> None:
        self.__name = name
        self.__phone = phone
class member(person):
    def __init__(self, idm, name, phone) -> None:
        super().__init__(name, phone)
        self.__idm = idm
class librarian(person):
    def __init__(self, ID, code, username, password, name, phone) -> None:
        super().__init__(name, phone)
        self.__ID = ID
        self.__code = code
        self.__username = username
        self.__password = password 

    def login():
        db = mysql.connect(
                host = "127.0.0.1",
                user = "root",
                passwd = "",
                database = "library system"
                )
        cursor = db.cursor()
        os.system("pause")
        os.system('cls')
        
        print("%s%s Login Librarian Screen %s" % (fg('red'), bg('grey_70'), attr('reset')))
        print('-'*45)
        username = input("Enter username:")
        password = getpass.getpass("Enter Password ((Password screen is hide)):")
        sql = "select *from librarian where username = %s and password = %s"
        cursor.execute(sql, [(username), (password)])
        results = cursor.fetchall()
        if results:
            for i in results:   
                print(stylize("\n\nlogin successfully",colored.fg("yellow")))
                return True
               
        else:
            print(stylize("Wront username or password *** Please Try again",colored.fg("red")))
            return False

        
             

        
    def menulibrarian(self):
        os.system("pause")
        os.system('cls')
        
        print((('\033[10m'+ '%s%s ....WELCOME to library.... %s' % (fg('black'), bg('light_green_2'), attr('reset') + '\033[10m'))))
        print(stylize("***********_________************",colored.fg("cyan")))

        print(stylize('1. register member',colored.fg("green")))
        print(stylize('2. add book',colored.fg("blue")))
        print(stylize('3. lending book to the member', colored.fg("red")))
        print(stylize('4. return book to the library from member',colored.fg("yellow")))
        print(stylize('5. List of hole member',colored.fg("magenta")))
        print(stylize('6. List of librarian',colored.fg("cyan")))
        print(stylize('7. list of book',colored.fg("orange_4a")))
        print(stylize('8. search book ',colored.fg("aquamarine_3")))
        print(stylize('9. UPdates member',colored.fg("misty_rose_3")))
        print(stylize('10. Updated book',colored.fg("dark_orange")))
        print(stylize('11. Exit',colored.fg("magenta_2a")))
        choice = int(input(stylize("Enter your choice:",colored.fg("plum_1"))))
        return choice
    
    def registermember(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        name = input('Enter Member Name :')
        idm = input('Enter Member ID : ')
        phone = input('Enter Member Phone  : ')

        sql = 'insert into member(name,idm,phone) values ( "' + \
            name+'","'+idm + \
              '","'+phone+'");'
        cursor.execute(sql)
        db.commit()
        db.close() 
        print(stylize('\nNew Member added successfully',colored.fg("cyan_1")))
        

        
    def addbook(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        
        ISBN = input("Enter ISBN:")
        title = input("Enter Title of the book:")
        author = input("Enter author name of the book:")
        publisher = input("Enter Publisher of the book:")
        language = input("Enter language of the book:")
        page = input("Enter number pages of the book:")
        Genres = input("Enter Genres type of the book:")
        sql = 'insert into book(ISBN,title,author,publisher,language,page,Genres,status) values ( "' + \
               ISBN + '","' + title+ '","' + author+ '","' + publisher+ '","' + language+'",'+page+',"'+Genres+'","available");'
        
    
        cursor.execute(sql)
        db.commit()
        db.close()
        print(stylize('\n\nNew Book added successfully',colored.fg("red")))
        
    def updatesbook(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        for _ in range(65):
             print()
        print('%s%sUPdates BOOK Details Screen %s'% (fg('black'), bg('red'), attr('reset')))
        print('-'*80)
        print(stylize('\n1. Book Title',colored.fg("blue")))
        print(stylize('\n2. Book Author',colored.fg("green")))
        print(stylize('\n3. Book Publisher',colored.fg("yellow")))
        print(stylize('\n4. Book Language',colored.fg("misty_rose_3")))
        print(stylize('\n5. Book pages',colored.fg("red")))
        print(stylize('\n6. Book Genres',colored.fg("dark_orange")))
        print(stylize('\n7. book Status',colored.fg("aquamarine_3")))
        print('\n\n')
        choice = int(input(stylize('Enter your choice :',colored.fg("navajo_white_1"))))
        field = ''

        if choice == 1:
           field = 'title'
        if choice == 2:
           field = 'author'
        if choice == 3:
           field = 'publisher'
        if choice == 4:
           field = 'language'
        if choice == 5:
            field = 'page'
        if choice == 6:
            field = 'Genres'  
        if choice == 7:
            field= 'status'       
        ISBN = input(stylize('Enter Book ISBN :',colored.fg("slate_blue_3b")))
        value = input(stylize('Enter new value :',colored.fg("yellow_1")))
        if field =='page':
            sql = 'update book set ' + field + ' = '+value+' where ISBN = '+ ISBN +';'
        else:
            sql = 'update book set ' + field + ' = "'+value+'" where ISBN = '+ ISBN +';'
        #print(sql)
        cursor.execute(sql)
        db.commit()
        print(stylize('\nBook details Updated.....',colored.fg("magenta_2b")))
        db.close()
            

    def updatesmember(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
    
        os.system('cls')
        print('%s%s UPdates Memeber %s' % (fg('white'), bg('blue_3a'), attr('reset')))
        print('-'*60)
        print(stylize('\n1. name',colored.fg("light_green_2")))
        print(stylize('\n2. phone',colored.fg("plum_1")))
        sh = int(input(stylize('Enter your choice :',colored.fg("misty_rose_3"))))
        field =''
        if sh == 1:
           field ='name'
        if sh == 2:
           field = 'phone'
        idm =input('Enter member ID :')
        value = input('Enter new value :')

        sql = 'update member set '+field+' = "'+value+'" where idm = '+idm+';'
        cursor.execute(sql)
        db.commit()
        print(stylize('Member details Updated.....',colored.fg("slate_blue_1")))
        db.close()
        
                    
    def mem_issue_status(idm):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        sql ='select * from lending where idm ='+idm +' and time_return_book is NULL;'
        cursor.execute(sql)
        results = cursor.fetchall()
        return results


    def book_status(ISBN):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        
        sql = 'select * from book where ISBN ='+ISBN + ';'
        cursor.execute(sql)
        result = cursor.fetchone()
        return result
        

    def book_issue_status(ISBN,idm):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        sql = 'select * from lending  where ISBN ='+ISBN + ' and idm ='+ idm +' and time_return_book is NULL;'
        cursor.execute(sql)
        result = cursor.fetchone()
        return result
        

    def lendingbook(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        os.system('cls')
        print(stylize('\n BOOK Lending to Member ',colored.fg("cyan")))
        print('-'*65)
        ISBN = input(stylize('Enter Book  ISBN : ',colored.fg("dark_orange")))
        idm  = input(stylize('Enter Member ID :',colored.fg("aquamarine_3")))

        result = librarian.book_status(ISBN)
        result_1 = librarian.mem_issue_status(idm)

        
        today = datetime.today()
        if len(result_1) == 1:
           if result == 'select * from book where status = available':
              sql = 'insert into lending(ISBN,idm,time_get_book) values('+ISBN+','+idm+',"'+str(today)+'");'
              sql_book = 'update book set status="issue" where ISBN ='+ISBN + ';'
              cursor.execute(sql)
              cursor.execute(sql_book)
              print('\n Book issued successfully')
           else:
              print('\nBook is not available for ISSUE... Current status :',result_1)          
        else:
            if len(result_1)<5:
                sql = 'insert into lending(ISBN,idm,time_get_book) values(' + \
                    ISBN+','+idm+',"'+str(today)+'");'
                sql_book = 'update book set status="issue" where ISBN ='+ISBN + ';'
                cursor.execute(sql)
                cursor.execute(sql_book)
                print('\n\n\n Book issued successfully')
            else:
                print('\nMember already have book from the Library')  
        db.commit()          
        db.close()       

    def returnbook(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        global fine_per_day
        os.system('cls')
        print('%s%s BOOK RETURN %s' % (fg('white'), bg('blue_3a'), attr('reset')))
        print('-'*45)
        ISBN = input(stylize('Enter Book ISBN : ',colored.fg("yellow")))
        idm = input(stylize('Enter Member ID :',colored.fg("blue")))
        today =datetime.today()
        
        result = librarian.book_issue_status(ISBN,idm)
        if result == 'select * from book where status = available':
            print('Book was not issued...Check book ISBN and Member ID again..')
            
             

            
           
        else:
   
            sql1 = 'insert into lending(time_return_book) values("'+str(today)+'");'
            sql_book='update book set status ="available" where ISBN ='+ISBN +';'
            cursor.execute(sql1)
            cursor.execute(sql_book)
            db.commit()
            db.close()
            
            

            print('\nBook returned successfully')
            
            
           
    def listofmember(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        os.system('cls')
        cursor.execute("SELECT * FROM member")
        member = prettytable.from_db_cursor(cursor)
        print(member)
    def listoflibrarian(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        os.system('cls')
        cursor.execute("SELECT * FROM librarian")
        librarian = prettytable.from_db_cursor(cursor)
        print(librarian)
    def listofbook(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        os.system('cls')
        cursor.execute("SELECT * FROM book")
        book = prettytable.from_db_cursor(cursor)
        print(book)
    def searchbook(self):
        db = mysql.connect(
        host = "127.0.0.1",
        user = "root",
        passwd = "",
        database = "library system"
        )
        cursor = db.cursor()
        
        os.system('cls')
        print('%s%s S E A R C H   M E N U %s' % (fg('white'), bg('blue_3a'), attr('reset')))
        print(stylize("\n1.  Book Title",colored.fg("hot_pink_1a")))
        print(stylize('\n2.  Book Author',colored.fg("deep_pink_3b")))
        print(stylize('\n3.  Publisher',colored.fg("gold_3b")))
           
        print('\n')
        choice = int(input(stylize('Enter your choice ...: ',colored.fg("gold_1"))))
        field =''
        if choice == 1:
           field='title'
        if choice == 2:
           field = 'author'
        if choice == 3:
           field = 'publisher'
             
        os.system('cls')
        print('\n BOOK SEARCH SCREEN')
        print('-'*65)
        msg ='Enter '+ field +' Value :'
        title = input(msg)
        sql ='select * from book where '+ field + ' like "%'+ title+'%"'
        cursor.execute(sql)
        records = cursor.fetchall()
        os.system('cls')
        print('Search Result for :',field,' :' ,title)
        print('-'*80)
        for record in records:
            print(record)
        db.close()
                
    
    
          
class affiliatesofmember(person):
    def __init__(self, ID, idm, name, phone) -> None:
        super().__init__(name, phone)
        self.__ID = ID
        self.__idm = idm
class bookitem:
    def __init__(self, ISBN, title, author, publisher, language, page, Genres) -> None:
        self.__ISBN = ISBN
        self.__title = title
        self.__author = author
        self.__publisher = publisher
        self.__language = language
        self.__page = page
        self.__Genres = Genres
class book(bookitem):
    def __init__(self,ISBN, title, author, publisher, language, page, Genres) -> None:
        super().__init__( ISBN, title, author, publisher, language, page, Genres)
        pass
class codebook:
    def __init__(self, Genrestype, codeofGenrestype) -> None:
        self.__Genrestype = Genrestype
        self.__codeofGenrestype = codeofGenrestype
class lendingbook:
    def __init__(self, ISBN, code, idm, time_get_book, time_return_book) -> None:
        self.__ISBN = ISBN
        self.__code = code
        self.__idm = idm
        self.__time_get_book = time_get_book
        self.__time_return_book = time_return_book
        
def main():
    log = librarian.login()
    if log == True:
           while True:
                lib = librarian(982341347,55478988,982341347,'Ali50568088','Amir hossien bana',9197561235)
                choice = lib.menulibrarian()
                if choice == 1:
                   lib.registermember()
                elif choice == 2:
                   lib.addbook()
                elif choice == 3:
                   lib.lendingbook()
                elif choice == 4:
                   lib.returnbook()
                elif choice == 5:
                   lib.listofmember()
                elif choice == 6:
                   lib.listoflibrarian()
                elif choice == 7:
                   lib.listofbook()
                elif choice == 8:
                   lib.searchbook()
                elif choice == 9:
                   lib.updatesmember()
                elif choice == 10:
                   lib.updatesbook()
                elif choice == 11:
                   break

               
main()    
