#include "Student.h"

Student::Student() : Person() {
    studentId = "";
    major = "";
    className = "";
    gpa = 0.0;
    roomId = "";
}

Student::Student(string id, string fullName, string dob, string gender,
    string phone, string addr, string stuId, string major,
    string className, double gpa)
    : Person(id, fullName, dob, gender, phone, addr) {
    this->studentId = stuId;
    this->major = major;
    this->className = className;
    this->gpa = gpa;
    this->roomId = "";
}

Student::~Student() {}

string Student::getStudentId() const { return studentId; }
string Student::getMajor() const { return major; }
string Student::getClassName() const { return className; }
double Student::getGpa() const { return gpa; }
string Student::getRoomId() const { return roomId; }

void Student::setStudentId(string stuId) { this->studentId = stuId; }
void Student::setMajor(string major) { this->major = major; }
void Student::setClassName(string className) { this->className = className; }
void Student::setGpa(double gpa) { this->gpa = gpa; }
void Student::setRoomId(string roomId) { this->roomId = roomId; }

void Student::display() const {
    Person::display();
    cout << "Ma sinh vien: " << studentId << endl;
    cout << "Nganh hoc: " << major << endl;
    cout << "Lop: " << className << endl;
    cout << "GPA: " << gpa << endl;
    if (!roomId.empty()) {
        cout << "Ma phong: " << roomId << endl;
    }
    else {
        cout << "Chua duoc phan phong" << endl;
    }
}

void Student::input() {
    Person::input();
    cout << "Nhap ma sinh vien: ";
    getline(cin, studentId);
    cout << "Nhap nganh hoc: ";
    getline(cin, major);
    cout << "Nhap lop: ";
    getline(cin, className);
    cout << "Nhap GPA: ";
    cin >> gpa;
}