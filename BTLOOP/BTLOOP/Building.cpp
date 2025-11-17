#include "Building.h"

Building::Building() {
    buildingId = "";
    buildingName = "";
    address = "";
    totalFloors = 0;
    buildingType = "";
}

Building::Building(string id, string name, string addr, int floors, string type) {
    this->buildingId = id;
    this->buildingName = name;
    this->address = addr;
    this->totalFloors = floors;
    this->buildingType = type;
}

Building::~Building() {
    for (auto room : rooms) {
        delete room;
    }
    rooms.clear();
}

string Building::getBuildingId() const { return buildingId; }
string Building::getBuildingName() const { return buildingName; }
string Building::getAddress() const { return address; }
int Building::getTotalFloors() const { return totalFloors; }
string Building::getBuildingType() const { return buildingType; }
vector<Room*> Building::getRooms() const { return rooms; }

void Building::setBuildingId(string id) { this->buildingId = id; }
void Building::setBuildingName(string name) { this->buildingName = name; }
void Building::setAddress(string addr) { this->address = addr; }
void Building::setTotalFloors(int floors) { this->totalFloors = floors; }
void Building::setBuildingType(string type) { this->buildingType = type; }

void Building::addRoom(Room* room) {
    if (room != nullptr) {
        rooms.push_back(room);
    }
}

bool Building::removeRoom(string roomId) {
    for (size_t i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomId() == roomId) {
            delete rooms[i];
            rooms.erase(rooms.begin() + i);
            return true;
        }
    }
    return false;
}

Room* Building::findRoom(string roomId) {
    for (auto room : rooms) {
        if (room->getRoomId() == roomId) {
            return room;
        }
    }
    return nullptr;
}

void Building::displayAllRooms() const {
    if (rooms.empty()) {
        cout << "Khong co phong nao trong toa nha nay." << endl;
        return;
    }

    for (const auto& room : rooms) {
        room->display();
        cout << "------------------------" << endl;
    }
}

void Building::display() const {
    cout << "Ma toa nha: " << buildingId << endl;
    cout << "Ten toa nha: " << buildingName << endl;
    cout << "Dia chi: " << address << endl;
    cout << "So tang: " << totalFloors << endl;
    cout << "Loai toa nha: " << buildingType << endl;
    cout << "So luong phong: " << rooms.size() << endl;
}

void Building::input() {
    cout << "Nhap ma toa nha: ";
    cin.ignore();
    getline(cin, buildingId);
    cout << "Nhap ten toa nha: ";
    getline(cin, buildingName);
    cout << "Nhap dia chi: ";
    getline(cin, address);
    cout << "Nhap so tang: ";
    cin >> totalFloors;
    cin.ignore();
    cout << "Nhap loai toa nha (Nam/Nu): ";
    getline(cin, buildingType);
}
