#include <iostream>
#include <fstream>
#include <limits>
#include <unistd.h>
#include <conio.h>
#include <regex>
#include <Windows.h>
#include "AddressBook.hpp"
#include "DateType.hpp"
#include "LinkedList.hpp"
//#include <QCoreApplication>
//#include <QObject>
//#include <QWidget>

// тестовое изменение для проверки коммитов в гит

using namespace std;

#define PROGRAM_NAME "AdressBook"
#define VERSION_MAJOR 0
#define VERSION_MINOR 1

const char CMD_ADD_CONTACT = 'a', CMD_DELETE_CONTACT = 'd', CMD_SEARCH_CONTACT = 's',
    CMD_PRINT_CONTACTS = 'p', CMD_HELP = 'h', CMD_QUIT = 'q';

const string ADDRESS_BOOK_FILE = "C:\\projects\\lsh\\addressbook.txt";

void runProg(istream& input, ostream& output);
void versionShow();
void menuShowHelp();
void loadAddressBook ();
int addAdressBookItem(istream& input, LinkedListType<AddressBook>& addressBookList);
void deleteAddressBookItem(istream& input, LinkedListType<AddressBook>& addressBookList);
void searchAddressBookItem(istream& input, LinkedListType<AddressBook>& addressBookList);
void browseAddressBook(istream& input, LinkedListType<AddressBook>& addressBookList);
void loadAddressBook(LinkedListType<AddressBook>& addressBook);
void saveAddressBookList(LinkedListType<AddressBook>& addressBookList);



int main(int argc, char *argv[])
{

   // QWidget widget;
    // Установим кодировку ввода и вывода консоли
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    //setlocale(LC_CTYPE, "rus");

    // Отобразим версию программы
    versionShow();

    // Запуск
    runProg(cin, cout);


    return 0;
}

void runProg(istream& input, ostream& output) {
    LinkedListType<AddressBook> addressBookList;
    loadAddressBook(addressBookList);
    // Сюда будем сохранять ввод пользователя
    char userInput;

    // Запускаем цикл ожидания команд от пользователя, пока он не выберет выход
    while (userInput != CMD_QUIT) {
        cout << "Command (h for help): ";

        // Считываем ввод пользователя
        cin >> userInput;
        cout << "got it!" << endl;

        switch (userInput) {
        case CMD_ADD_CONTACT:
            addAdressBookItem(input, addressBookList);
            break;
        case CMD_DELETE_CONTACT:
            deleteAddressBookItem(input, addressBookList);
            break;
        case CMD_SEARCH_CONTACT:
            searchAddressBookItem(input, addressBookList);
            break;
        case CMD_PRINT_CONTACTS:
            browseAddressBook(input, addressBookList);
            break;
        case CMD_HELP:
            menuShowHelp();
            break;
        default: // Распознаватель неправильных команд
            cout << "Неизвестный символ. Попробуйте еще раз" << endl;
            break;
        }
    }

    saveAddressBookList(addressBookList);  // Сохраняем адресную книгу
    cout << "Normal exit!" << endl;
}

void versionShow() {
    // Выведем стартовое приветствие с именем программы и её версией
    printf("Welcome to %s version %d.%d\n", PROGRAM_NAME, VERSION_MAJOR, VERSION_MINOR);

}

void menuShowHelp() {
    cout << endl << "Help:" << endl << endl;
    cout << "    p    print address book" << endl;
    cout << "    a    add address" << endl;
    cout << "    d    delete address" << endl;
    cout << "    s    search address" << endl;
    cout << "    q    exit program" << endl << endl;
}


bool isValidEmail(string_view str) {
    static const regex r(R"(\w+@\w+\.(?:com|in|ru|net))");
    return regex_match(str.data(), r);
}

bool isValidPhoneNumber(string_view str) {
    static const regex r(R"(\+?[78]{1}\(?[0-9]{3}\)?[0-9]{3}\-?[0-9]{2}\-?[0-9]{2})");
    return regex_match(str.data(), r);
}

bool isValidName(string_view str) {
    std::regex pattern("^[a-zA-Zа-яА-Я][0-9a-zA-Zа-яА-Я\\s\\-]+[^-]$");
    return regex_match(str.data(), pattern);
}

// Обрезает пробелы в начале и в конце строки
string trimText(string str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                  return !std::isspace(ch);
              }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                  return !std::isspace(ch);
              }).base(), str.end());
    return str;
}


int addAdressBookItem(istream& input, LinkedListType<AddressBook>& addressBookList)
{
    string newFirstname, newLastname, newPatronymic, newPhone_home, newPhone_work,
        newPhone_mobile, newEmail, newAddress1, newAddress2, newCity, newCountry;
    DateType newBirthday;
    char hasBirthday;

    // В буффере ввода уже что-то находится и вычитывается в Фамилию, поэтому вычитаем в мусорку.
    string garbage;
    std::getline(cin, garbage);

    while (1) {
        cout << "Введите Фамилию: ";
        std::getline(cin, newLastname);
        newLastname = trimText(newLastname);

        if (isValidName(newLastname)) {
            break;
        }
        std::cout << "Фамилия должна содержать только буквы и цифры различных алфавитов, а "
                     "также дефис и пробел, но при этом должны начинаться только на буквы, и "
                     "не могли бы оканчиваться или начинаться на дефис." << std::endl;
    }


    while (1) {
        cout << "Введите Имя: ";
        std::getline(std::cin, newFirstname);
        newFirstname = trimText(newFirstname);

        if (isValidName(newFirstname)) {
            break;
        }
        std::cout << "Имя должно содержать только буквы и цифры различных алфавитов, а "
                     "также дефис и пробел, но при этом должны начинаться только на буквы, и "
                     "не могли бы оканчиваться или начинаться на дефис." << std::endl;

    }


    while (1) {
        cout << "Введите Отчество: ";
        std::getline(std::cin, newPatronymic);
        newPatronymic = trimText(newPatronymic);

        if (isValidName(newPatronymic)) {
            break;
        }
        std::cout << "Отчество должно содержать только буквы и цифры различных алфавитов, а "
                     "также дефис и пробел, но при этом должны начинаться только на буквы, и "
                     "не могли бы оканчиваться или начинаться на дефис." << std::endl;

    }

    while (1) {
        cout << "Введите домашний номер телефона: ";
        std::getline(std::cin, newPhone_home);
        newPhone_home = trimText(newPhone_home);

        if (isValidPhoneNumber(newPhone_home)) {
            break;
        }
        std::cout << "Вы указали некорректный номер телефона." << std::endl;
    }

    while (1) {
        cout << "Введите рабочий номер телефона: ";
        std::getline(std::cin, newPhone_work);
        newPhone_work = trimText(newPhone_work);

        if (isValidPhoneNumber(newPhone_mobile)) {
            break;
        }
        std::cout << "Вы указали некорректный номер телефона." << std::endl;
    }

    while (1) {
        cout << "Введите мобильный номер телефона: ";
        std::getline(std::cin, newPhone_mobile);
        newPhone_mobile = trimText(newPhone_mobile);

        if (isValidPhoneNumber(newPhone_mobile)) {
            break;
        }
        std::cout << "Вы указали некорректный номер телефона." << std::endl;
    }


    while (1) {
        cout << "Введите Email: ";
        std::getline(std::cin, newEmail);
        if (isValidEmail(newEmail)) {
            break;
        }
        std::cout << "Введён некорректный Email. Допустимо использовать только латинские буквы, цифры, знак подчеркивания, точку и минус. " << std::endl;
    }

    cout << "Введите адрес: ";
    std::getline(std::cin, newAddress1);

    cout << "Введите номер квартиры (0 если частный дом): ";
    std::getline(std::cin, newAddress2);

    cout << "Введите Город: ";
    std::getline(std::cin, newCity);

    cout << "Введите Страну: ";
    std::getline(std::cin, newCountry);

    cout << "Хотите указать дату рождения? Нажмите 'y' если да, 'n' если нет: ";
    input >> hasBirthday;
    if (hasBirthday == 'y' || hasBirthday == 'Y')
    {
        int newMonth, newDay, newYear;
        cout << "Введите день рождения (DD): ";
        input >> newDay;
        cout << "Ввдите месяц рождения (MM): ";
        input >> newMonth;
        cout << "Введите год рождения (YYYY): ";
        input >> newYear;
        try
        {
            newBirthday.Initialize(newDay, newMonth, newYear);
        }
        catch(...)
        {
            cout << "Дата введена неверно, поэтому сохранена не будет!" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            newBirthday = DateType();
        }
    }
    AddressBook newContact(newFirstname, newLastname, newPatronymic,
                           newPhone_home, newPhone_work, newPhone_mobile, newEmail,
                           newBirthday, newAddress1, newAddress2,
                           newCity, newCountry);
    try
    {
        addressBookList.PutItem(newContact);
        cout << "\nContact saved:" << endl;
        newContact.PrintAddress(cout);
    }
    catch(DuplicateItemException)
    {
        cout << "Error, contact with that name already exists.  Contact not saved." << endl;
        return 1;
    }

    return 0;
}

void searchAddressBookItem(istream& input, LinkedListType<AddressBook>& addressBookList)
{
    string newFirstname, newLastname, newPatronymic, newPhone_home, newPhone_work,
        newPhone_mobile, newEmail,  newAddress1, newAddress2, newCity, newCountry;

    cout << "Введите Имя: ";
    input >> newFirstname;
    cout << "Введите Фамилию: ";
    input >> newLastname;
    DateType newBirthday;

    AddressBook newContact(newFirstname, newLastname, newPatronymic,
                           newPhone_home, newPhone_work, newPhone_mobile, newEmail,
                           newBirthday, newAddress1, newAddress2,
                           newCity, newCountry);

    try
    {
        newContact = addressBookList.SearchList(newContact);
    }
    catch(...)
    {
        cout << "Запись не найдена!" << endl;
        return;
    }

    cout << "Найденная запись:" << endl;
    newContact.PrintAddress(cout);

    char willEdit;
    cout << "Редактировать записть (y/n)? ";
    input >> willEdit;
    if (willEdit == 'y' || willEdit == 'Y')
    {
        addressBookList.DeleteItem(newContact);
        int editSuccess = addAdressBookItem(input, addressBookList);
        if (editSuccess == 0)
        {
            cout << "Запись успешно отредактирована." << endl;
            return;
        }
        else
        {
            cout << "Ошибка редактирования записи!" << endl;
            addressBookList.PutItem(newContact);
            return;
        }
    }

}


void deleteAddressBookItem(istream& input, LinkedListType<AddressBook>& addressBookList)
{
    string newFirstname, newLastname, newPatronymic, newPhone_home, newPhone_work,
        newPhone_mobile, newEmail, newAddress1, newAddress2, newCity, newCountry;

    cout << "Enter first name of contact to delete: ";
    input >> newFirstname;
    cout << "Enter last name of contact to delete: ";
    input >> newLastname;
    DateType newBirthday;

    AddressBook newContact(newFirstname, newLastname, newPatronymic,
                           newPhone_home, newPhone_work, newPhone_mobile, newEmail,
                           newBirthday, newAddress1, newAddress2,
                           newCity, newCountry);

    try
    {
        addressBookList.DeleteItem(newContact);
        cout << "\nЗапись успешно удалена." << endl;
    }
    catch(...)
    {
        cout << "\nЗапись не найдена!" << endl;
    }

}

void browseAddressBook(istream& input, LinkedListType<AddressBook>& addressBookList)
{
    int listLength = addressBookList.GetLength();
    int editSuccess = 1;
    if (listLength == 0)
    {
        cout << "Адресная книга пустая." << endl;
        return;
    }

    int menuChoice = 1;
    AddressBook currentContact = addressBookList.GetFirstItem();

    while(menuChoice == 1 || menuChoice == 2)
    {
        cout << "------------------------------------------" << endl;
        cout << "Просмотр записей адресной книги. Текущая запись #:" << addressBookList.GetCurrentIndex() << "/" << listLength << endl;
        currentContact.PrintAddress(cout);
        cout << "------------------------------------------" << endl;
        cout << "1:Следующая запись" << endl;
        cout << "2:Предыдущая запись" << endl;
        cout << "3:Удалить запись" << endl;
        cout << "4:Редактировать запись" << endl;
        cout << "5:Вернуться в основное меню" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Enter selection (1-7): ";
        input >> menuChoice;


        switch (menuChoice)
        {
        case 1:
            currentContact = addressBookList.GetNextItem();
            break;
        case 2:
            currentContact = addressBookList.GetPreviousItem();
            break;
        case 3:
            addressBookList.DeleteItem(currentContact);
            cout << "Запись удалена. Возврат в основное меню.";
            return;
        case 4: //edit
            addressBookList.DeleteItem(currentContact);
            editSuccess = addAdressBookItem(input, addressBookList);
            if (editSuccess == 0)
            {
                cout << "Запись успешно отредактирована." << endl;
                return;
            }
            else
            {
                cout << "Ошибка редактирования записи. Возврат в основное меню." << endl;
                addressBookList.PutItem(currentContact);
                return;
            }
            return;
        case 5:
            return;
        default:
            cout << "Неизвестная комадна. Возврат в основное меню." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
    }
}


void loadAddressBook(LinkedListType<AddressBook>& addressBookList)
{
    ifstream addressBook;
    addressBook.open(ADDRESS_BOOK_FILE);
    if (!addressBook)
        cout << "NOTE: '" << ADDRESS_BOOK_FILE <<"' NOT FOUND.  Program will create a new file on exit." << endl;
    else
    {
        cout << "Address Book found, loading to memory..." << endl;
        try
        {
            int fileLength;
            string itemsCnt;

            // Вычитаем как строку, потом сконвертируем в int
            std::getline(addressBook, itemsCnt);
            fileLength = strtol(itemsCnt.c_str(), NULL, 10);

            std::cout << "Records found: " << fileLength << endl;
            //addressBook >> fileLength;
            for(int i = 0; i < fileLength; i++)
            {
                int newMonth, newDay, newYear;
                string newFirstname, newLastname, newPatronymic, newPhone_home, newPhone_work,
                    newPhone_mobile, newEmail, newAddress1, newAddress2, newCity, newCountry;
                DateType newBirthday;

                string hasDateStr;
                int hasDate;

                std::getline(addressBook, newLastname);
                std::getline(addressBook, newFirstname);
                std::getline(addressBook, newPatronymic);
                std::getline(addressBook, newPhone_home);
                std::getline(addressBook, newPhone_work);
                std::getline(addressBook, newPhone_mobile);
                std::getline(addressBook, newEmail);
                std::getline(addressBook, newAddress1);
                std::getline(addressBook, newAddress2);
                std::getline(addressBook, newCity);
                std::getline(addressBook, newCountry);

                std::getline(addressBook, hasDateStr);
                hasDate = strtol(hasDateStr.c_str(), NULL, 10);

                /*
                cout << "newLastname: " << newLastname << endl;
                cout << "newFirstname: " << newFirstname << endl;
                cout << "newPatronymic: " << newPatronymic << endl;
                cout << "newPhone_home: " << newPhone_home << endl;
                cout << "newPhone_work: " << newPhone_work << endl;
                cout << "newPhone_mobile: " << newPhone_mobile << endl;
                cout << "newAddress1: " << newAddress1 << endl;
                cout << "newAddress2: " << newAddress2 << endl;
                cout << "newCity: " << newCity << endl;
                cout << "newCountry: " << newCountry << endl;
*/

                if (hasDate)
                {
                    addressBook >> newMonth >> newDay >> newYear;
                    newBirthday.Initialize(newMonth,newDay,newYear);
                }
                AddressBook newContact(newFirstname, newLastname, newPatronymic,
                                       newPhone_home, newPhone_work, newPhone_mobile, newEmail,
                                       newBirthday, newAddress1, newAddress2,
                                       newCity, newCountry);

                addressBookList.PutItem(newContact);

            }
            cout << "done!" << endl;
        }
        catch(...)
        {
            std::cerr << "\n ERROR: '" << ADDRESS_BOOK_FILE << "' corrupted, new file will be created on exit." << endl;
            addressBookList = LinkedListType<AddressBook>();
        }
    }
    addressBook.close();
}

void saveAddressBookList(LinkedListType<AddressBook>& addressBookList)
{
    cout << "Saving to '" << ADDRESS_BOOK_FILE << "'...";
    ofstream addressBook;
    addressBook.open(ADDRESS_BOOK_FILE);
    int listLength = addressBookList.GetLength();
    addressBook << listLength << endl;
    if (listLength == 0)
    {
        addressBook.close();
        return;
    }

    AddressBook newContact = addressBookList.GetFirstItem();

    for (int i = 0; i < listLength; i++)
    {
        string contactFirstname = newContact.GetFirstname();
        string contactLastname = newContact.GetLastname();
        string contactPatronymic = newContact.GetPatronymic();
        string contactPhone_home = newContact.GetPhone_home();
        string contactPhone_work = newContact.GetPhone_work();
        string contactPhone_mobile = newContact.GetPhone_mobile();
        string contactEmail = newContact.GetEmail();
        string contactAddress1 = newContact.GetAddress1();
        string contactAddress2 = newContact.GetAddress2();
        string contactCity = newContact.GetCity();
        string contactCountry = newContact.GetCountry();

        DateType contactBirthday = newContact.GetBirthday();

        addressBook << contactLastname << endl;
        addressBook << contactFirstname << endl;
        addressBook << contactPatronymic << endl;
        addressBook << contactPhone_home << endl;
        addressBook << contactPhone_work << endl;
        addressBook << contactPhone_mobile << endl;
        addressBook << contactAddress1 << endl;
        addressBook << contactAddress2 << endl;
        addressBook << contactCity << endl;
        addressBook << contactCountry << endl;

        bool hasDate = contactBirthday.IsInitialized();

        addressBook << hasDate << endl;
        if (hasDate)
            addressBook << contactBirthday.GetMonth() << " " << contactBirthday.GetDay()
                        << " " << contactBirthday.GetYear() << endl;

        newContact = addressBookList.GetNextItem();
    }

    addressBook.close();
    cout << "done!" << endl;
}
