#include "Bill.h"
#include <iomanip>

Bill::Bill() {
    billId = "";
    roomId = "";
    month = "";
    electricityUsed = 0;
    waterUsed = 0;
    electricityPrice = 2500.0;  // 2500 VND/kWh (default)
    waterPrice = 15000.0;       // 15000 VND/m3 (default)
    serviceCharges = 50000.0;   // 50000 VND (default)
    totalAmount = 0.0;
    isPaid = false;
    paymentDate = "";
    notes = "";
}

Bill::Bill(string billId, string roomId, string month,
    int elecUsed, int waterUsed) {
    this->billId = billId;
    this->roomId = roomId;
    this->month = month;
    this->electricityUsed = elecUsed;
    this->waterUsed = waterUsed;
    this->electricityPrice = 2500.0;
    this->waterPrice = 15000.0;
    this->serviceCharges = 50000.0;
    this->isPaid = false;
    this->paymentDate = "";
    this->notes = "";
    calculateTotal();
}

Bill::~Bill() {}

// Getters
string Bill::getBillId() const { return billId; }
string Bill::getRoomId() const { return roomId; }
string Bill::getMonth() const { return month; }
int Bill::getElectricityUsed() const { return electricityUsed; }
int Bill::getWaterUsed() const { return waterUsed; }
double Bill::getElectricityPrice() const { return electricityPrice; }
double Bill::getWaterPrice() const { return waterPrice; }
double Bill::getServiceCharges() const { return serviceCharges; }
double Bill::getTotalAmount() const { return totalAmount; }
bool Bill::getIsPaid() const { return isPaid; }
string Bill::getPaymentDate() const { return paymentDate; }
string Bill::getNotes() const { return notes; }

// Setters
void Bill::setBillId(string id) { this->billId = id; }
void Bill::setRoomId(string roomId) { this->roomId = roomId; }
void Bill::setMonth(string month) { this->month = month; }
void Bill::setElectricityUsed(int used) {
    this->electricityUsed = used;
    calculateTotal();
}
void Bill::setWaterUsed(int used) {
    this->waterUsed = used;
    calculateTotal();
}
void Bill::setElectricityPrice(double price) {
    this->electricityPrice = price;
    calculateTotal();
}
void Bill::setWaterPrice(double price) {
    this->waterPrice = price;
    calculateTotal();
}
void Bill::setServiceCharges(double charges) {
    this->serviceCharges = charges;
    calculateTotal();
}
void Bill::setNotes(string notes) { this->notes = notes; }

// Business methods
void Bill::calculateTotal() {
    double electricityCost = electricityUsed * electricityPrice;
    double waterCost = waterUsed * waterPrice;
    totalAmount = electricityCost + waterCost + serviceCharges;
}

void Bill::markAsPaid() {
    isPaid = true;

    time_t now = time(0);
    tm ltm;                    
    localtime_s(&ltm, &now);    

    char buffer[11];
    sprintf_s(buffer, "%02d/%02d/%04d",
        ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year);

    paymentDate = buffer;
    cout << "Hoa don da duoc thanh toan!" << endl;
}


void Bill::display() const {
    cout << "Ma hoa don: " << billId << endl;
    cout << "Ma phong: " << roomId << endl;
    cout << "Thang: " << month << endl;
    cout << "Dien tieu thu: " << electricityUsed << " kWh" << endl;
    cout << "Gia dien: " << electricityPrice << " VND/kWh" << endl;
    cout << "Tien dien: " << (electricityUsed * electricityPrice) << " VND" << endl;
    cout << "Nuoc tieu thu: " << waterUsed << " m3" << endl;
    cout << "Gia nuoc: " << waterPrice << " VND/m3" << endl;
    cout << "Tien nuoc: " << (waterUsed * waterPrice) << " VND" << endl;
    cout << "Phi dich vu: " << serviceCharges << " VND" << endl;
    cout << "Tong tien: " << totalAmount << " VND" << endl;
    cout << "Trang thai: " << (isPaid ? "Da thanh toan" : "Chua thanh toan") << endl;
    if (isPaid) {
        cout << "Ngay thanh toan: " << paymentDate << endl;
    }
    if (!notes.empty()) {
        cout << "Ghi chu: " << notes << endl;
    }
}

void Bill::input() {
    cout << "Nhap ma hoa don: ";
    cin.ignore();
    getline(cin, billId);
    cout << "Nhap ma phong: ";
    getline(cin, roomId);
    cout << "Nhap thang (MM/YYYY): ";
    getline(cin, month);
    cout << "Nhap so dien tieu thu (kWh): ";
    cin >> electricityUsed;
    cout << "Nhap gia dien (VND/kWh) [Enter = 2500]: ";
    cin >> electricityPrice;
    if (electricityPrice == 0) electricityPrice = 2500.0;
    cout << "Nhap so nuoc tieu thu (m3): ";
    cin >> waterUsed;
    cout << "Nhap gia nuoc (VND/m3) [Enter = 15000]: ";
    cin >> waterPrice;
    if (waterPrice == 0) waterPrice = 15000.0;
    cout << "Nhap phi dich vu (VND) [Enter = 50000]: ";
    cin >> serviceCharges;
    if (serviceCharges == 0) serviceCharges = 50000.0;
    cin.ignore();
    cout << "Nhap ghi chu (neu co): ";
    getline(cin, notes);
    calculateTotal();
}

void Bill::printReceipt() const {
    cout << "\n================================================" << endl;
    cout << "           PHIEU THANH TOAN HOA DON" << endl;
    cout << "           KY TUC XA SINH VIEN" << endl;
    cout << "================================================" << endl;
    cout << "Ma hoa don: " << billId << endl;
    cout << "Ma phong: " << roomId << endl;
    cout << "Thang: " << month << endl;
    cout << "------------------------------------------------" << endl;
    cout << left << setw(25) << "Chi tiet"
        << right << setw(10) << "So luong"
        << setw(15) << "Don gia"
        << setw(15) << "Thanh tien" << endl;
    cout << "------------------------------------------------" << endl;
    cout << left << setw(25) << "Dien"
        << right << setw(10) << electricityUsed
        << setw(15) << electricityPrice
        << setw(15) << (electricityUsed * electricityPrice) << endl;
    cout << left << setw(25) << "Nuoc"
        << right << setw(10) << waterUsed
        << setw(15) << waterPrice
        << setw(15) << (waterUsed * waterPrice) << endl;
    cout << left << setw(25) << "Phi dich vu"
        << right << setw(10) << "-"
        << setw(15) << "-"
        << setw(15) << serviceCharges << endl;
    cout << "------------------------------------------------" << endl;
    cout << left << setw(40) << "TONG CONG:"
        << right << setw(15) << totalAmount << " VND" << endl;
    cout << "================================================" << endl;
    cout << "Trang thai: " << (isPaid ? "DA THANH TOAN" : "CHUA THANH TOAN") << endl;
    if (isPaid) {
        cout << "Ngay thanh toan: " << paymentDate << endl;
    }
    cout << "================================================\n" << endl;
}