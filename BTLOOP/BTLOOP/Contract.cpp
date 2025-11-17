#include "Contract.h"

Contract::Contract() {
    contractId = "";
    studentId = "";
    roomId = "";
    startDate = "";
    endDate = "";
    monthlyFee = 0.0;
    deposit = 0.0;
    isActive = true;
}

Contract::Contract(string contractId, string studentId, string roomId,
    string startDate, string endDate, double monthlyFee, double deposit) {
    this->contractId = contractId;
    this->studentId = studentId;
    this->roomId = roomId;
    this->startDate = startDate;
    this->endDate = endDate;
    this->monthlyFee = monthlyFee;
    this->deposit = deposit;
    this->isActive = true;
}

Contract::~Contract() {}

string Contract::getContractId() const { return contractId; }
string Contract::getStudentId() const { return studentId; }
string Contract::getRoomId() const { return roomId; }
string Contract::getStartDate() const { return startDate; }
string Contract::getEndDate() const { return endDate; }
double Contract::getMonthlyFee() const { return monthlyFee; }
double Contract::getDeposit() const { return deposit; }
bool Contract::getIsActive() const { return isActive; }

void Contract::setContractId(string id) { this->contractId = id; }
void Contract::setStudentId(string studentId) { this->studentId = studentId; }
void Contract::setRoomId(string roomId) { this->roomId = roomId; }
void Contract::setStartDate(string date) { this->startDate = date; }
void Contract::setEndDate(string date) { this->endDate = date; }
void Contract::setMonthlyFee(double fee) { this->monthlyFee = fee; }
void Contract::setDeposit(double deposit) { this->deposit = deposit; }
void Contract::setIsActive(bool status) { this->isActive = status; }

void Contract::terminateContract() {
    isActive = false;
    cout << "Hop dong " << contractId << " da duoc huy." << endl;
}

void Contract::display() const {
    cout << "Ma hop dong: " << contractId << endl;
    cout << "Ma sinh vien: " << studentId << endl;
    cout << "Ma phong: " << roomId << endl;
    cout << "Ngay bat dau: " << startDate << endl;
    cout << "Ngay ket thuc: " << endDate << endl;
    cout << "Phi hang thang: " << monthlyFee << " VND" << endl;
    cout << "Tien dat coc: " << deposit << " VND" << endl;
    cout << "Trang thai: " << (isActive ? "Con hieu luc" : "Da huy") << endl;
}

void Contract::input() {
    cout << "Nhap ma hop dong: ";
    cin.ignore();
    getline(cin, contractId);
    cout << "Nhap ma sinh vien: ";
    getline(cin, studentId);
    cout << "Nhap ma phong: ";
    getline(cin, roomId);
    cout << "Nhap ngay bat dau (dd/mm/yyyy): ";
    getline(cin, startDate);
    cout << "Nhap ngay ket thuc (dd/mm/yyyy): ";
    getline(cin, endDate);
    cout << "Nhap phi hang thang: ";
    cin >> monthlyFee;
    cout << "Nhap tien dat coc: ";
    cin >> deposit;
    isActive = true;
}