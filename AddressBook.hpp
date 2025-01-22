#ifndef ADDRESSBOOK_HPP
#define ADDRESSBOOK_HPP

#include "DateType.hpp"
#include <iostream>
using namespace std;

class AddressBook {

public:



    AddressBook();
    AddressBook(string newFirstname, string newLastname, string newPatronymic,
                             string newPhone_home, string newPhone_work, string newPhone_mobile, string newEmail,
                             DateType newBirthday, string newAddress1, string newAddress2,
                             string newCity, string newCountry);

    string GetFirstname();
    string GetLastname();
    string GetPatronymic();
    string GetPhone_home();
    string GetPhone_work();
    string GetPhone_mobile();
    string GetEmail();
    DateType GetBirthday();
    string GetAddress1();
    string GetAddress2();
    string GetCity();
    string GetCountry();

    void SetFirstname(string newFirstname);
    void SetLastname(string newLastname);
    void SetPatronymic(string newPatronymic);
    void SetPhone_home(string newPhone_home);
    void SetPhone_work(string newPhone_work);
    void SetPhone_mobile(string newPhone_mobile);
    void SetNewEmail(string newEnail);
    void SetBirthday(DateType newBirthday);
    void SetAddress1(string newAddress1);
    void SetAddress2(string newAddress2);
    void SetCity(string newCity);
    void SetCountry(string newCountry);

    void PrintAddress(ostream& out);

    bool operator<(AddressBook otherContact);
    bool operator==(AddressBook otherContact);

private:
    // Имя
    string firstname;

    // Фамилия
    string lastname;

    // Отчество
    string patronymic;

    // Домашний номер телефона
    string phone_home;

    // Рабочий номер телефона
    string phone_work;

    // Служебный номер телефона
    string phone_mobile;

    //Почта
    string Email;

    // Дата рождения
    DateType birthday;

    // Адрес1 (улица и номер дома)
    string address1;

    // Адрес2 (номер квартиры, офиса, и.т.д)
    string address2;

    // Город
    string city;

    // Страна
    string country;
};


#endif // ADDRESSBOOK_HPP
