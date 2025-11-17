#pragma once
#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include <iostream>
#include "Room.h"
using namespace std;

class Building {
private:
    string buildingId;
    string buildingName;
    string address;
    int totalFloors;
    string buildingType; // "Nam" hoac "Nu"
    vector<Room*> rooms;

public:
    // Constructor
    Building();
    Building(string id, string name, string addr, int floors, string type);

    // Destructor
    ~Building();

    // Getter methods
    string getBuildingId() const;
    string getBuildingName() const;
    string getAddress() const;
    int getTotalFloors() const;
    string getBuildingType() const;
    vector<Room*> getRooms() const;

    // Setter methods
    void setBuildingId(string id);
    void setBuildingName(string name);
    void setAddress(string addr);
    void setTotalFloors(int floors);
    void setBuildingType(string type);

    // Methods
    void addRoom(Room* room);
    bool removeRoom(string roomId);
    Room* findRoom(string roomId);
    void displayAllRooms() const;
    void display() const;
    void input();
};

#endif

