#include "AddressBook.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

AddressBook::AddressBook()
{

}

AddressBook::AddressBook(string newFirstname, string newLastname, string newPatronymic,
                         string newPhone_home, string newPhone_work, string newPhone_mobile,
                         DateType newBirthday, string newAddress1, string newAddress2,
                         string newCity, string newCountry)
{
    firstname = newFirstname;
    lastname = newLastname;
    patronymic = newPatronymic;
    phone_home = newPhone_home;
    phone_work = newPhone_work;
    phone_mobile = newPhone_mobile;
    birthday = newBirthday;
    address1 = newAddress1;
    address2 = newAddress2;
    city = newCity;
    country = newCountry;
}

string AddressBook::GetFirstname() {
    return firstname;
}

string AddressBook::GetLastname() {
    return lastname;
}

string AddressBook::GetPatronymic() {
    return patronymic;
}

string AddressBook::GetPhone_home() {
    return phone_home;
}

string AddressBook::GetPhone_work() {
    return phone_work;
}

string AddressBook::GetPhone_mobile() {
    return phone_mobile;
}

DateType AddressBook::GetBirthday() {
    return birthday;
}

string AddressBook::GetAddress1() {
    return address1;
}

string AddressBook::GetAddress2() {
    return address2;
}

string AddressBook::GetCity() {
    return city;
}

string AddressBook::GetCountry() {
    return country;
}

void AddressBook::SetFirstname(string newFirstname) {
    firstname = newFirstname;
}

void AddressBook::SetLastname(string newLastname) {
    lastname = newLastname;
}

void AddressBook::SetPatronymic(string newPatronymic) {
    patronymic = newPatronymic;
}

void AddressBook::SetPhone_home(string newPhone_home) {
    phone_home = newPhone_home;
}

void AddressBook::SetPhone_work(string newPhone_work) {
    phone_work = newPhone_work;
}

void AddressBook::SetPhone_mobile(string newPhone_mobile) {
    phone_mobile = newPhone_mobile;
}

void AddressBook::SetBirthday(DateType newBirthday) {
    birthday = newBirthday;
}

void AddressBook::SetAddress1(string newAddress1) {
    address1 = newAddress1;
}

void AddressBook::SetAddress2(string newAddress2) {
    address2 = newAddress2;
}

void AddressBook::SetCity(string newCity) {
    city = newCity;
}

void AddressBook::SetCountry(string newCountry) {
    country = newCountry;
}

void AddressBook::PrintAddress(ostream& out) {
    out << "Name: " << lastname << " " << firstname << " " << patronymic << endl;
    out << "Phones home: " << phone_home << ", work: " << phone_work << ", " << ", mobile: " << phone_mobile << endl;
    out << "Birthday: " << birthday.DateString() << endl;
    out << "Address: " << address1 << " " << address2 << ", " << city << ", " << country << endl;
}

bool AddressBook::operator<(AddressBook otherContact)
{
    string selfLastName = lastname;
    string selfFirstName = firstname;
    string otherLastName = otherContact.GetLastname();
    string otherFirstName = otherContact.GetFirstname();
    transform(selfLastName.begin(), selfLastName.end(), selfLastName.begin(), ::toupper);
    transform(selfFirstName.begin(), selfFirstName.end(), selfFirstName.begin(), ::toupper);
    transform(otherLastName.begin(), otherLastName.end(), otherLastName.begin(), ::toupper);
    transform(otherFirstName.begin(), otherFirstName.end(), otherFirstName.begin(), ::toupper);
    if (selfLastName > otherLastName)
        return false;
    else if (selfLastName == otherLastName)
        return (selfFirstName < otherFirstName);
    else
        return true;


}
bool AddressBook::operator==(AddressBook otherContact)
{
    string selfLastName = lastname;
    string selfFirstName = firstname;
    string otherLastName = otherContact.GetLastname();
    string otherFirstName = otherContact.GetFirstname();
    transform(selfLastName.begin(), selfLastName.end(), selfLastName.begin(), ::toupper);
    transform(selfFirstName.begin(), selfFirstName.end(), selfFirstName.begin(), ::toupper);
    transform(otherLastName.begin(), otherLastName.end(), otherLastName.begin(), ::toupper);
    transform(otherFirstName.begin(), otherFirstName.end(), otherFirstName.begin(), ::toupper);
    if (selfLastName == otherLastName && selfFirstName == otherFirstName)
        return true;
    else
        return false;
}

