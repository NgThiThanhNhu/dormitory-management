#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Room {
private:
    string roomId;
    string buildingId;
    int capacity;
    int currentOccupants;
    double pricePerMonth;
    string roomType; // "Nam" hoac "Nu"
    vector<string> studentIds; // Danh sach ma sinh vien trong phong

public:
    // Constructor
    Room();
    Room(string roomId, string buildingId, int capacity,
        double price, string type);

    // Destructor
    ~Room();

    // Getter methods
    string getRoomId() const;
    string getBuildingId() const;
    int getCapacity() const;
    int getCurrentOccupants() const;
    double getPricePerMonth() const;
    string getRoomType() const;
    vector<string> getStudentIds() const;

    // Setter methods
    void setRoomId(string id);
    void setBuildingId(string buildingId);
    void setCapacity(int capacity);
    void setPricePerMonth(double price);
    void setRoomType(string type);

    // Methods
    bool isFull() const;
    bool addStudent(string studentId);
    bool removeStudent(string studentId);
    void display() const;
    void input();
};

#endif

