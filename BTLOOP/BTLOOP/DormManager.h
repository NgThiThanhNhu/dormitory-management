#pragma once
#ifndef DORMMANAGER_H
#define DORMMANAGER_H

#include <vector>
#include <string>
#include "Student.h"
#include "Room.h"
#include "Building.h"
#include "Contract.h"
using namespace std;

class DormManager {
private:
    vector<Student*> students;
    vector<Building*> buildings;
    vector<Contract*> contracts;

public:
    // Constructor & Destructor
    DormManager();
    ~DormManager();

    // Student Management
    void addStudent();
    void displayAllStudents() const;
    void searchStudentById(string id) const;
    void updateStudent(string id);
    void deleteStudent(string id);
    Student* findStudent(string id);

    // Building Management
    void addBuilding();
    void displayAllBuildings() const;
    void searchBuildingById(string id) const;
    void deleteBuilding(string id);
    Building* findBuilding(string id);

    // Room Management
    void addRoomToBuilding(string buildingId);
    void displayAllRooms() const;
    void searchRoomById(string roomId) const;
    void displayAvailableRooms() const;
    Room* findRoom(string roomId);

    // Contract Management
    void createContract();
    void displayAllContracts() const;
    void searchContractById(string id) const;
    void terminateContract(string id);
    Contract* findContract(string id);

    // Assignment Management
    bool assignStudentToRoom(string studentId, string roomId);
    bool removeStudentFromRoom(string studentId);

    // Statistics
    void displayStatistics() const;
    void displayRoomsByBuilding(string buildingId) const;

    // File Operations
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif

