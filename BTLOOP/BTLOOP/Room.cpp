#include "Room.h"

Room::Room() {
    roomId = "";
    buildingId = "";
    capacity = 0;
    currentOccupants = 0;
    pricePerMonth = 0.0;
    roomType = "";
}

Room::Room(string roomId, string buildingId, int capacity,
    double price, string type) {
    this->roomId = roomId;
    this->buildingId = buildingId;
    this->capacity = capacity;
    this->currentOccupants = 0;
    this->pricePerMonth = price;
    this->roomType = type;
}

Room::~Room() {}

string Room::getRoomId() const { return roomId; }
string Room::getBuildingId() const { return buildingId; }
int Room::getCapacity() const { return capacity; }
int Room::getCurrentOccupants() const { return currentOccupants; }
double Room::getPricePerMonth() const { return pricePerMonth; }
string Room::getRoomType() const { return roomType; }
vector<string> Room::getStudentIds() const { return studentIds; }

void Room::setRoomId(string id) { this->roomId = id; }
void Room::setBuildingId(string buildingId) { this->buildingId = buildingId; }
void Room::setCapacity(int capacity) { this->capacity = capacity; }
void Room::setPricePerMonth(double price) { this->pricePerMonth = price; }
void Room::setRoomType(string type) { this->roomType = type; }

bool Room::isFull() const {
    return currentOccupants >= capacity;
}

bool Room::addStudent(string studentId) {
    if (isFull()) {
        cout << "Phong da day!" << endl;
        return false;
    }
    studentIds.push_back(studentId);
    currentOccupants++;
    return true;
}

bool Room::removeStudent(string studentId) {
    for (size_t i = 0; i < studentIds.size(); i++) {
        if (studentIds[i] == studentId) {
            studentIds.erase(studentIds.begin() + i);
            currentOccupants--;
            return true;
        }
    }
    return false;
}

void Room::display() const {
    cout << "Ma phong: " << roomId << endl;
    cout << "Ma toa nha: " << buildingId << endl;
    cout << "Suc chua: " << capacity << endl;
    cout << "So nguoi hien tai: " << currentOccupants << endl;
    cout << "Gia thue/thang: " << pricePerMonth << " VND" << endl;
    cout << "Loai phong: " << roomType << endl;
    cout << "Danh sach sinh vien: ";
    if (studentIds.empty()) {
        cout << "Trong" << endl;
    }
    else {
        cout << endl;
        for (const auto& id : studentIds) {
            cout << "  - " << id << endl;
        }
    }
}

void Room::input() {
    cout << "Nhap ma phong: ";
    cin.ignore();
    getline(cin, roomId);
    cout << "Nhap ma toa nha: ";
    getline(cin, buildingId);
    cout << "Nhap suc chua: ";
    cin >> capacity;
    cout << "Nhap gia thue/thang: ";
    cin >> pricePerMonth;
    cin.ignore();
    cout << "Nhap loai phong (Nam/Nu): ";
    getline(cin, roomType);
    currentOccupants = 0;
}
