#include "Person.h"

Person::Person() {
    id = "";
    fullName = "";
    dateOfBirth = "";
    gender = "";
    phoneNumber = "";
    address = "";
}

Person::Person(string id, string fullName, string dob, string gender,
    string phone, string addr) {
    this->id = id;
    this->fullName = fullName;
    this->dateOfBirth = dob;
    this->gender = gender;
    this->phoneNumber = phone;
    this->address = addr;
}

Person::~Person() {}

string Person::getId() const { return id; }
string Person::getFullName() const { return fullName; }
string Person::getDateOfBirth() const { return dateOfBirth; }
string Person::getGender() const { return gender; }
string Person::getPhoneNumber() const { return phoneNumber; }
string Person::getAddress() const { return address; }

void Person::setId(string id) { this->id = id; }
void Person::setFullName(string name) { this->fullName = name; }
void Person::setDateOfBirth(string dob) { this->dateOfBirth = dob; }
void Person::setGender(string gender) { this->gender = gender; }
void Person::setPhoneNumber(string phone) { this->phoneNumber = phone; }
void Person::setAddress(string addr) { this->address = addr; }

void Person::display() const {
    cout << "ID: " << id << endl;
    cout << "Ho ten: " << fullName << endl;
    cout << "Ngay sinh: " << dateOfBirth << endl;
    cout << "Gioi tinh: " << gender << endl;
    cout << "So dien thoai: " << phoneNumber << endl;
    cout << "Dia chi: " << address << endl;
}

void Person::input() {
    cout << "Nhap ID: ";
    cin.ignore();
    getline(cin, id);
    cout << "Nhap ho ten: ";
    getline(cin, fullName);
    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    getline(cin, dateOfBirth);
    cout << "Nhap gioi tinh: ";
    getline(cin, gender);
    cout << "Nhap so dien thoai: ";
    getline(cin, phoneNumber);
    cout << "Nhap dia chi: ";
    getline(cin, address);
}
