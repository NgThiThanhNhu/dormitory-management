#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

class Person {
protected:
    string id;
    string fullName;
    string dateOfBirth;
    string gender;
    string phoneNumber;
    string address;

public:
    // Constructor
    Person();
    Person(string id, string fullName, string dob, string gender,
        string phone, string addr);

    // Destructor
    virtual ~Person();

    // Getter methods
    string getId() const;
    string getFullName() const;
    string getDateOfBirth() const;
    string getGender() const;
    string getPhoneNumber() const;
    string getAddress() const;

    // Setter methods
    void setId(string id);
    void setFullName(string name);
    void setDateOfBirth(string dob);
    void setGender(string gender);
    void setPhoneNumber(string phone);
    void setAddress(string addr);

    // Virtual methods
    virtual void display() const;
    virtual void input();
};

#endif

