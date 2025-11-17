#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

class Student : public Person {
private:
    string studentId;
    string major;
    string className;
    double gpa;
    string roomId;

public:
    // Constructor
    Student();
    Student(string id, string fullName, string dob, string gender,
        string phone, string addr, string stuId, string major,
        string className, double gpa);

    // Destructor
    ~Student();

    // Getter methods
    string getStudentId() const;
    string getMajor() const;
    string getClassName() const;
    double getGpa() const;
    string getRoomId() const;

    // Setter methods
    void setStudentId(string stuId);
    void setMajor(string major);
    void setClassName(string className);
    void setGpa(double gpa);
    void setRoomId(string roomId);

    // Override methods
    void display() const override;
    void input() override;
};

#endif

