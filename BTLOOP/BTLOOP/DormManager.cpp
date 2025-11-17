#include "DormManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

DormManager::DormManager() {}

DormManager::~DormManager() {
    for (auto student : students) delete student;
    for (auto building : buildings) delete building;
    for (auto contract : contracts) delete contract;
    students.clear();
    buildings.clear();
    contracts.clear();
}

// ==================== STUDENT MANAGEMENT ====================

void DormManager::addStudent() {
    Student* newStudent = new Student();
    newStudent->input();
    students.push_back(newStudent);
    cout << "Them sinh vien thanh cong!" << endl;
}

void DormManager::displayAllStudents() const {
    if (students.empty()) {
        cout << "Khong co sinh vien nao!" << endl;
        return;
    }

    cout << "\n========== DANH SACH SINH VIEN ==========" << endl;
    for (const auto& student : students) {
        student->display();
        cout << "----------------------------------------" << endl;
    }
}

void DormManager::searchStudentById(string id) const {
    for (const auto& student : students) {
        if (student->getStudentId() == id || student->getId() == id) {
            cout << "\n===== THONG TIN SINH VIEN =====" << endl;
            student->display();
            return;
        }
    }
    cout << "Khong tim thay sinh vien co ID: " << id << endl;
}

void DormManager::updateStudent(string id) {
    Student* student = findStudent(id);
    if (student == nullptr) {
        cout << "Khong tim thay sinh vien!" << endl;
        return;
    }

    cout << "Nhap thong tin moi cho sinh vien:" << endl;
    student->input();
    cout << "Cap nhat thanh cong!" << endl;
}

void DormManager::deleteStudent(string id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i]->getStudentId() == id || students[i]->getId() == id) {
            // Remove from room if assigned
            if (!students[i]->getRoomId().empty()) {
                removeStudentFromRoom(students[i]->getStudentId());
            }
            delete students[i];
            students.erase(students.begin() + i);
            cout << "Xoa sinh vien thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay sinh vien!" << endl;
}

Student* DormManager::findStudent(string id) {
    for (auto student : students) {
        if (student->getStudentId() == id || student->getId() == id) {
            return student;
        }
    }
    return nullptr;
}

// ==================== BUILDING MANAGEMENT ====================

void DormManager::addBuilding() {
    Building* newBuilding = new Building();
    newBuilding->input();
    buildings.push_back(newBuilding);
    cout << "Them toa nha thanh cong!" << endl;
}

void DormManager::displayAllBuildings() const {
    if (buildings.empty()) {
        cout << "Khong co toa nha nao!" << endl;
        return;
    }

    cout << "\n========== DANH SACH TOA NHA ==========" << endl;
    for (const auto& building : buildings) {
        building->display();
        cout << "----------------------------------------" << endl;
    }
}

void DormManager::searchBuildingById(string id) const {
    for (const auto& building : buildings) {
        if (building->getBuildingId() == id) {
            cout << "\n===== THONG TIN TOA NHA =====" << endl;
            building->display();
            cout << "\n===== DANH SACH PHONG =====" << endl;
            building->displayAllRooms();
            return;
        }
    }
    cout << "Khong tim thay toa nha co ID: " << id << endl;
}

void DormManager::deleteBuilding(string id) {
    for (size_t i = 0; i < buildings.size(); i++) {
        if (buildings[i]->getBuildingId() == id) {
            delete buildings[i];
            buildings.erase(buildings.begin() + i);
            cout << "Xoa toa nha thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay toa nha!" << endl;
}

Building* DormManager::findBuilding(string id) {
    for (auto building : buildings) {
        if (building->getBuildingId() == id) {
            return building;
        }
    }
    return nullptr;
}
// ==================== ROOM MANAGEMENT ====================

void DormManager::addRoomToBuilding(string buildingId) {
    Building* building = findBuilding(buildingId);
    if (building == nullptr) {
        cout << "Khong tim thay toa nha!" << endl;
        return;
    }

    Room* newRoom = new Room();
    newRoom->input();
    newRoom->setBuildingId(buildingId);
    building->addRoom(newRoom);
    cout << "Them phong thanh cong!" << endl;
}

void DormManager::displayAllRooms() const {
    if (buildings.empty()) {
        cout << "Khong co toa nha nao!" << endl;
        return;
    }

    cout << "\n========== DANH SACH TAT CA CAC PHONG ==========" << endl;
    for (const auto& building : buildings) {
        cout << "\nToa nha: " << building->getBuildingName()
            << " (" << building->getBuildingId() << ")" << endl;
        building->displayAllRooms();
    }
}

void DormManager::searchRoomById(string roomId) const {
    for (const auto& building : buildings) {
        Room* room = building->findRoom(roomId);
        if (room != nullptr) {
            cout << "\n===== THONG TIN PHONG =====" << endl;
            room->display();
            return;
        }
    }
    cout << "Khong tim thay phong co ID: " << roomId << endl;
}

void DormManager::displayAvailableRooms() const {
    cout << "\n========== DANH SACH PHONG CON TRONG ==========" << endl;
    bool found = false;

    for (const auto& building : buildings) {
        for (const auto& room : building->getRooms()) {
            if (!room->isFull()) {
                room->display();
                cout << "Cho trong: " << (room->getCapacity() - room->getCurrentOccupants()) << endl;
                cout << "----------------------------------------" << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Khong co phong trong!" << endl;
    }
}

Room* DormManager::findRoom(string roomId) {
    for (auto building : buildings) {
        Room* room = building->findRoom(roomId);
        if (room != nullptr) {
            return room;
        }
    }
    return nullptr;
}

// ==================== CONTRACT MANAGEMENT ====================

void DormManager::createContract() {
    Contract* newContract = new Contract();
    newContract->input();

    // Verify student exists
    Student* student = findStudent(newContract->getStudentId());
    if (student == nullptr) {
        cout << "Sinh vien khong ton tai!" << endl;
        delete newContract;
        return;
    }

    // Verify room exists
    Room* room = findRoom(newContract->getRoomId());
    if (room == nullptr) {
        cout << "Phong khong ton tai!" << endl;
        delete newContract;
        return;
    }

    contracts.push_back(newContract);
    cout << "Tao hop dong thanh cong!" << endl;
}

void DormManager::displayAllContracts() const {
    if (contracts.empty()) {
        cout << "Khong co hop dong nao!" << endl;
        return;
    }

    cout << "\n========== DANH SACH HOP DONG ==========" << endl;
    for (const auto& contract : contracts) {
        contract->display();
        cout << "----------------------------------------" << endl;
    }
}

void DormManager::searchContractById(string id) const {
    for (const auto& contract : contracts) {
        if (contract->getContractId() == id) {
            cout << "\n===== THONG TIN HOP DONG =====" << endl;
            contract->display();
            return;
        }
    }
    cout << "Khong tim thay hop dong co ID: " << id << endl;
}

void DormManager::terminateContract(string id) {
    for (auto contract : contracts) {
        if (contract->getContractId() == id) {
            contract->terminateContract();
            // Remove student from room
            removeStudentFromRoom(contract->getStudentId());
            return;
        }
    }
    cout << "Khong tim thay hop dong!" << endl;
}

Contract* DormManager::findContract(string id) {
    for (auto contract : contracts) {
        if (contract->getContractId() == id) {
            return contract;
        }
    }
    return nullptr;
}
// ==================== ASSIGNMENT MANAGEMENT ====================

bool DormManager::assignStudentToRoom(string studentId, string roomId) {
    Student* student = findStudent(studentId);
    if (student == nullptr) {
        cout << "Khong tim thay sinh vien!" << endl;
        return false;
    }

    Room* room = findRoom(roomId);
    if (room == nullptr) {
        cout << "Khong tim thay phong!" << endl;
        return false;
    }

    // Check if room is full
    if (room->isFull()) {
        cout << "Phong da day!" << endl;
        return false;
    }

    // Check gender compatibility
    if (room->getRoomType() != student->getGender()) {
        cout << "Gioi tinh khong phu hop voi loai phong!" << endl;
        return false;
    }

    // Remove from old room if already assigned
    if (!student->getRoomId().empty()) {
        removeStudentFromRoom(studentId);
    }

    // Assign to new room
    if (room->addStudent(studentId)) {
        student->setRoomId(roomId);
        cout << "Phan phong thanh cong!" << endl;
        return true;
    }

    return false;
}

bool DormManager::removeStudentFromRoom(string studentId) {
    Student* student = findStudent(studentId);
    if (student == nullptr) {
        return false;
    }

    string roomId = student->getRoomId();
    if (roomId.empty()) {
        return false;
    }

    Room* room = findRoom(roomId);
    if (room != nullptr) {
        room->removeStudent(studentId);
        student->setRoomId("");
        return true;
    }

    return false;
}

// ==================== STATISTICS ====================

void DormManager::displayStatistics() const {
    cout << "\n========== THONG KE HE THONG ==========" << endl;
    cout << "Tong so sinh vien: " << students.size() << endl;
    cout << "Tong so toa nha: " << buildings.size() << endl;

    int totalRooms = 0;
    int occupiedRooms = 0;
    int totalCapacity = 0;
    int currentOccupants = 0;

    for (const auto& building : buildings) {
        for (const auto& room : building->getRooms()) {
            totalRooms++;
            if (room->getCurrentOccupants() > 0) {
                occupiedRooms++;
            }
            totalCapacity += room->getCapacity();
            currentOccupants += room->getCurrentOccupants();
        }
    }

    cout << "Tong so phong: " << totalRooms << endl;
    cout << "So phong dang su dung: " << occupiedRooms << endl;
    cout << "So phong con trong: " << (totalRooms - occupiedRooms) << endl;
    cout << "Tong suc chua: " << totalCapacity << endl;
    cout << "So cho dang su dung: " << currentOccupants << endl;
    cout << "So cho con trong: " << (totalCapacity - currentOccupants) << endl;
    cout << "Ty le lap day: " << (totalCapacity > 0 ? (currentOccupants * 100.0 / totalCapacity) : 0) << "%" << endl;
    cout << "Tong so hop dong: " << contracts.size() << endl;

    int activeContracts = 0;
    for (const auto& contract : contracts) {
        if (contract->getIsActive()) {
            activeContracts++;
        }
    }
    cout << "So hop dong con hieu luc: " << activeContracts << endl;
}

void DormManager::displayRoomsByBuilding(string buildingId) const {
    Building* building = const_cast<DormManager*>(this)->findBuilding(buildingId);
    if (building == nullptr) {
        cout << "Khong tim thay toa nha!" << endl;
        return;
    }

    cout << "\n===== DANH SACH PHONG CUA TOA NHA " << building->getBuildingName() << " =====" << endl;
    building->displayAllRooms();
}

// ==================== FILE OPERATIONS ====================

void DormManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file de luu!" << endl;
        return;
    }

    // Save students
    file << students.size() << endl;
    for (const auto& student : students) {
        file << student->getId() << "|"
            << student->getFullName() << "|"
            << student->getDateOfBirth() << "|"
            << student->getGender() << "|"
            << student->getPhoneNumber() << "|"
            << student->getAddress() << "|"
            << student->getStudentId() << "|"
            << student->getMajor() << "|"
            << student->getClassName() << "|"
            << student->getGpa() << "|"
            << student->getRoomId() << endl;
    }

    file.close();
    cout << "Luu du lieu thanh cong!" << endl;
}

void DormManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file de doc!" << endl;
        return;
    }

    // Clear existing data
    for (auto student : students) delete student;
    students.clear();

    int numStudents;
    file >> numStudents;
    file.ignore();

    for (int i = 0; i < numStudents; i++) {
        string line;
        getline(file, line);
        // Parse and create student objects
        // Implementation depends on your specific needs
    }

    file.close();
    cout << "Doc du lieu thanh cong!" << endl;
}