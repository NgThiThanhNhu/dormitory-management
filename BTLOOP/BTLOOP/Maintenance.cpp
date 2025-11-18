#include "Maintenance.h"
#include <ctime>

Maintenance::Maintenance() {
    maintenanceId = "";
    roomId = "";
    requestedBy = "";
    deviceName = "";
    issueDescription = "";
    requestDate = "";
    completedDate = "";
    status = PENDING;
    priority = MEDIUM;
    assignedTo = "";
    cost = 0.0;
    notes = "";
}

Maintenance::Maintenance(string id, string roomId, string requestedBy,
    string device, string issue, string date) {
    this->maintenanceId = id;
    this->roomId = roomId;
    this->requestedBy = requestedBy;
    this->deviceName = device;
    this->issueDescription = issue;
    this->requestDate = date;
    this->completedDate = "";
    this->status = PENDING;
    this->priority = MEDIUM;
    this->assignedTo = "";
    this->cost = 0.0;
    this->notes = "";
}

Maintenance::~Maintenance() {}

// Getters
string Maintenance::getMaintenanceId() const { return maintenanceId; }
string Maintenance::getRoomId() const { return roomId; }
string Maintenance::getRequestedBy() const { return requestedBy; }
string Maintenance::getDeviceName() const { return deviceName; }
string Maintenance::getIssueDescription() const { return issueDescription; }
string Maintenance::getRequestDate() const { return requestDate; }
string Maintenance::getCompletedDate() const { return completedDate; }
MaintenanceStatus Maintenance::getStatus() const { return status; }
MaintenancePriority Maintenance::getPriority() const { return priority; }
string Maintenance::getAssignedTo() const { return assignedTo; }
double Maintenance::getCost() const { return cost; }
string Maintenance::getNotes() const { return notes; }

// Setters
void Maintenance::setMaintenanceId(string id) { this->maintenanceId = id; }
void Maintenance::setRoomId(string roomId) { this->roomId = roomId; }
void Maintenance::setRequestedBy(string requestedBy) { this->requestedBy = requestedBy; }
void Maintenance::setDeviceName(string device) { this->deviceName = device; }
void Maintenance::setIssueDescription(string issue) { this->issueDescription = issue; }
void Maintenance::setRequestDate(string date) { this->requestDate = date; }
void Maintenance::setCompletedDate(string date) { this->completedDate = date; }
void Maintenance::setStatus(MaintenanceStatus status) { this->status = status; }
void Maintenance::setPriority(MaintenancePriority priority) { this->priority = priority; }
void Maintenance::setAssignedTo(string assignedTo) { this->assignedTo = assignedTo; }
void Maintenance::setCost(double cost) { this->cost = cost; }
void Maintenance::setNotes(string notes) { this->notes = notes; }

// Business methods
void Maintenance::updateStatus(MaintenanceStatus newStatus) {
    status = newStatus;
    cout << "Da cap nhat trang thai thanh: " << statusToString(newStatus) << endl;
}

void Maintenance::complete(double repairCost) {
    status = COMPLETED;
    cost = repairCost;

    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    char buffer[11];
    sprintf_s(buffer, sizeof(buffer), "%02d/%02d/%04d",
        ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year);

    completedDate = buffer;

    cout << "Yeu cau bao tri da hoan thanh!" << endl;
}


void Maintenance::display() const {
    cout << "Ma bao tri: " << maintenanceId << endl;
    cout << "Ma phong: " << roomId << endl;
    cout << "Nguoi yeu cau: " << requestedBy << endl;
    cout << "Thiet bi: " << deviceName << endl;
    cout << "Van de: " << issueDescription << endl;
    cout << "Ngay yeu cau: " << requestDate << endl;
    cout << "Uu tien: " << priorityToString(priority) << endl;
    cout << "Trang thai: " << statusToString(status) << endl;
    if (!assignedTo.empty()) {
        cout << "Nguoi xu ly: " << assignedTo << endl;
    }
    if (status == COMPLETED) {
        cout << "Ngay hoan thanh: " << completedDate << endl;
        cout << "Chi phi: " << cost << " VND" << endl;
    }
    if (!notes.empty()) {
        cout << "Ghi chu: " << notes << endl;
    }
}

void Maintenance::input() {
    cout << "Nhap ma bao tri: ";
    cin.ignore();
    getline(cin, maintenanceId);
    cout << "Nhap ma phong: ";
    getline(cin, roomId);
    cout << "Nhap nguoi yeu cau: ";
    getline(cin, requestedBy);
    cout << "Nhap ten thiet bi: ";
    getline(cin, deviceName);
    cout << "Nhap mo ta van de: ";
    getline(cin, issueDescription);
    cout << "Nhap ngay yeu cau (dd/mm/yyyy): ";
    getline(cin, requestDate);

    cout << "\nChon muc do uu tien:" << endl;
    cout << "1. Thap" << endl;
    cout << "2. Trung binh" << endl;
    cout << "3. Cao" << endl;
    cout << "4. Khan cap" << endl;
    cout << "Chon: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1: priority = LOW; break;
    case 2: priority = MEDIUM; break;
    case 3: priority = HIGH; break;
    case 4: priority = URGENT; break;
    default: priority = MEDIUM;
    }
    cin.ignore();

    cout << "Nhap nguoi phu trach: ";
    getline(cin, assignedTo);
    cout << "Nhap ghi chu (neu co): ";
    getline(cin, notes);
}

string Maintenance::statusToString(MaintenanceStatus status) {
    switch (status) {
    case PENDING: return "Cho xu ly";
    case IN_PROGRESS: return "Dang xu ly";
    case COMPLETED: return "Da hoan thanh";
    case CANCELLED: return "Da huy";
    default: return "Khong xac dinh";
    }
}

string Maintenance::priorityToString(MaintenancePriority priority) {
    switch (priority) {
    case LOW: return "Thap";
    case MEDIUM: return "Trung binh";
    case HIGH: return "Cao";
    case URGENT: return "Khan cap";
    default: return "Khong xac dinh";
    }
}