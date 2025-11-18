#include "Violation.h"

Violation::Violation() {
    violationId = "";
    studentId = "";
    roomId = "";
    type = OTHER;
    description = "";
    date = "";
    fineAmount = 0.0;
    isPaid = false;
    reportedBy = "";
    notes = "";
}

Violation::Violation(string violationId, string studentId, string roomId,
    ViolationType type, string description, string date) {
    this->violationId = violationId;
    this->studentId = studentId;
    this->roomId = roomId;
    this->type = type;
    this->description = description;
    this->date = date;
    this->fineAmount = 0.0;
    this->isPaid = false;
    this->reportedBy = "";
    this->notes = "";
}

Violation::~Violation() {}

// Getters
string Violation::getViolationId() const { return violationId; }
string Violation::getStudentId() const { return studentId; }
string Violation::getRoomId() const { return roomId; }
ViolationType Violation::getType() const { return type; }
string Violation::getDescription() const { return description; }
string Violation::getDate() const { return date; }
double Violation::getFineAmount() const { return fineAmount; }
bool Violation::getIsPaid() const { return isPaid; }
string Violation::getReportedBy() const { return reportedBy; }
string Violation::getNotes() const { return notes; }

// Setters
void Violation::setViolationId(string id) { this->violationId = id; }
void Violation::setStudentId(string studentId) { this->studentId = studentId; }
void Violation::setRoomId(string roomId) { this->roomId = roomId; }
void Violation::setType(ViolationType type) { this->type = type; }
void Violation::setDescription(string desc) { this->description = desc; }
void Violation::setDate(string date) { this->date = date; }
void Violation::setFineAmount(double amount) { this->fineAmount = amount; }
void Violation::setReportedBy(string reporter) { this->reportedBy = reporter; }
void Violation::setNotes(string notes) { this->notes = notes; }

// Business methods
void Violation::markAsPaid() {
    isPaid = true;
    cout << "Tien phat da duoc dong!" << endl;
}

string Violation::getTypeString() const {
    return violationTypeToString(type);
}

string Violation::violationTypeToString(ViolationType type) {
    switch (type) {
    case NOISE: return "Gay on";
    case LATE_RETURN: return "Ve muon";
    case UNAUTHORIZED_GUEST: return "Khach khong phep";
    case SMOKING: return "Hut thuoc";
    case ALCOHOL: return "Su dung ruou bia";
    case DAMAGE_PROPERTY: return "Lam hu hong tai san";
    case ILLEGAL_DEVICE: return "Thiet bi khong cho phep";
    case HYGIENE: return "Vi pham ve sinh";
    case FIGHTING: return "Danh nhau";
    case OTHER: return "Khac";
    default: return "Khong xac dinh";
    }
}

ViolationType Violation::stringToViolationType(int choice) {
    switch (choice) {
    case 1: return NOISE;
    case 2: return LATE_RETURN;
    case 3: return UNAUTHORIZED_GUEST;
    case 4: return SMOKING;
    case 5: return ALCOHOL;
    case 6: return DAMAGE_PROPERTY;
    case 7: return ILLEGAL_DEVICE;
    case 8: return HYGIENE;
    case 9: return FIGHTING;
    default: return OTHER;
    }
}

void Violation::display() const {
    cout << "Ma vi pham: " << violationId << endl;
    cout << "Ma sinh vien: " << studentId << endl;
    cout << "Ma phong: " << roomId << endl;
    cout << "Loai vi pham: " << getTypeString() << endl;
    cout << "Mo ta: " << description << endl;
    cout << "Ngay vi pham: " << date << endl;
    cout << "Tien phat: " << fineAmount << " VND" << endl;
    cout << "Trang thai: " << (isPaid ? "Da dong phat" : "Chua dong phat") << endl;
    if (!reportedBy.empty()) {
        cout << "Nguoi bao cao: " << reportedBy << endl;
    }
    if (!notes.empty()) {
        cout << "Ghi chu: " << notes << endl;
    }
}

void Violation::input() {
    cout << "Nhap ma vi pham: ";
    cin.ignore();
    getline(cin, violationId);
    cout << "Nhap ma sinh vien: ";
    getline(cin, studentId);
    cout << "Nhap ma phong: ";
    getline(cin, roomId);

    cout << "\nChon loai vi pham:" << endl;
    cout << "1. Gay on" << endl;
    cout << "2. Ve muon" << endl;
    cout << "3. Khach khong phep" << endl;
    cout << "4. Hut thuoc" << endl;
    cout << "5. Su dung ruou bia" << endl;
    cout << "6. Lam hu hong tai san" << endl;
    cout << "7. Thiet bi khong cho phep" << endl;
    cout << "8. Vi pham ve sinh" << endl;
    cout << "9. Danh nhau" << endl;
    cout << "10. Khac" << endl;
    cout << "Chon: ";
    int choice;
    cin >> choice;
    type = stringToViolationType(choice);
    cin.ignore();

    cout << "Nhap mo ta vi pham: ";
    getline(cin, description);
    cout << "Nhap ngay vi pham (dd/mm/yyyy): ";
    getline(cin, date);
    cout << "Nhap tien phat (VND): ";
    cin >> fineAmount;
    cin.ignore();
    cout << "Nhap nguoi bao cao: ";
    getline(cin, reportedBy);
    cout << "Nhap ghi chu (neu co): ";
    getline(cin, notes);
}