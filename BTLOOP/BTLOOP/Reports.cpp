#include "Reports.h"
#include <iomanip>
#include <ctime>

string Reports::getCurrentDate() {
    time_t now = time(0);
    tm ltm;

    localtime_s(&ltm, &now);

    char buffer[11];
    sprintf_s(buffer, sizeof(buffer), "%02d/%02d/%04d",
        ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year);

    return string(buffer);
}


string Reports::escapeCSV(const string& str) {
    string result = str;
    // Replace quotes with double quotes
    size_t pos = 0;
    while ((pos = result.find("\"", pos)) != string::npos) {
        result.replace(pos, 1, "\"\"");
        pos += 2;
    }
    // Wrap in quotes if contains comma or newline
    if (result.find(',') != string::npos || result.find('\n') != string::npos) {
        result = "\"" + result + "\"";
    }
    return result;
}

// ==================== STUDENT REPORTS ====================

void Reports::exportStudentsToCSV(const vector<Student*>& students,
    const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    // Header
    file << "Ma SV,Ho Ten,Ngay Sinh,Gioi Tinh,SDT,Dia Chi,Nganh,Lop,GPA,Ma Phong\n";

    // Data
    for (const auto& student : students) {
        file << escapeCSV(student->getStudentId()) << ","
            << escapeCSV(student->getFullName()) << ","
            << escapeCSV(student->getDateOfBirth()) << ","
            << escapeCSV(student->getGender()) << ","
            << escapeCSV(student->getPhoneNumber()) << ","
            << escapeCSV(student->getAddress()) << ","
            << escapeCSV(student->getMajor()) << ","
            << escapeCSV(student->getClassName()) << ","
            << student->getGpa() << ","
            << escapeCSV(student->getRoomId()) << "\n";
    }

    file.close();
    cout << "Xuat danh sach sinh vien thanh cong: " << filename << endl;
}

void Reports::exportStudentsToHTML(const vector<Student*>& students,
    const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Danh Sach Sinh Vien</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "h1 { color: #333; text-align: center; }\n";
    file << "table { width: 100%; border-collapse: collapse; margin-top: 20px; }\n";
    file << "th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }\n";
    file << "th { background-color: #4CAF50; color: white; }\n";
    file << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
    file << "tr:hover { background-color: #ddd; }\n";
    file << ".date { text-align: right; color: #666; margin-bottom: 20px; }\n";
    file << "</style>\n</head>\n<body>\n";

    file << "<h1>DANH SACH SINH VIEN KY TUC XA</h1>\n";
    file << "<div class='date'>Ngay xuat: " << getCurrentDate() << "</div>\n";

    file << "<table>\n<thead>\n<tr>\n";
    file << "<th>STT</th><th>Ma SV</th><th>Ho Ten</th><th>Ngay Sinh</th>";
    file << "<th>Gioi Tinh</th><th>SDT</th><th>Nganh</th><th>Lop</th>";
    file << "<th>GPA</th><th>Ma Phong</th>\n</tr>\n</thead>\n<tbody>\n";

    int stt = 1;
    for (const auto& student : students) {
        file << "<tr>\n";
        file << "<td>" << stt++ << "</td>";
        file << "<td>" << student->getStudentId() << "</td>";
        file << "<td>" << student->getFullName() << "</td>";
        file << "<td>" << student->getDateOfBirth() << "</td>";
        file << "<td>" << student->getGender() << "</td>";
        file << "<td>" << student->getPhoneNumber() << "</td>";
        file << "<td>" << student->getMajor() << "</td>";
        file << "<td>" << student->getClassName() << "</td>";
        file << "<td>" << fixed << setprecision(2) << student->getGpa() << "</td>";
        file << "<td>" << (student->getRoomId().empty() ? "Chua co" : student->getRoomId()) << "</td>";
        file << "\n</tr>\n";
    }

    file << "</tbody>\n</table>\n";
    file << "<div class='date'>Tong so sinh vien: " << students.size() << "</div>\n";
    file << "</body>\n</html>";

    file.close();
    cout << "Xuat bao cao HTML thanh cong: " << filename << endl;
}

// ==================== ROOM REPORTS ====================

void Reports::exportRoomOccupancyReport(const vector<Building*>& buildings,
    const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file << "BAO CAO TY LE LAP DAY PHONG\n";
    file << "Ngay: " << getCurrentDate() << "\n\n";

    file << left << setw(15) << "Ma Toa Nha"
        << setw(25) << "Ten Toa Nha"
        << setw(15) << "Ma Phong"
        << setw(12) << "Suc Chua"
        << setw(12) << "Da O"
        << setw(12) << "Con Trong"
        << setw(10) << "Ty Le\n";
    file << string(100, '-') << "\n";

    for (const auto& building : buildings) {
        for (const auto& room : building->getRooms()) {
            int capacity = room->getCapacity();
            int occupied = room->getCurrentOccupants();
            int available = capacity - occupied;
            double rate = capacity > 0 ? (occupied * 100.0 / capacity) : 0;

            file << left << setw(15) << building->getBuildingId()
                << setw(25) << building->getBuildingName()
                << setw(15) << room->getRoomId()
                << setw(12) << capacity
                << setw(12) << occupied
                << setw(12) << available
                << setw(10) << fixed << setprecision(1) << rate << "%\n";
        }
    }

    file.close();
    cout << "Xuat bao cao ty le lap day thanh cong: " << filename << endl;
}

// ==================== BILL REPORTS ====================

void Reports::exportBillSummaryReport(const vector<Bill*>& bills,
    const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<meta charset=\"UTF-8\">\n";
    file << "<title>Bao Cao Hoa Don</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "h1 { color: #333; text-align: center; }\n";
    file << "table { width: 100%; border-collapse: collapse; margin-top: 20px; }\n";
    file << "th, td { border: 1px solid #ddd; padding: 10px; text-align: left; }\n";
    file << "th { background-color: #2196F3; color: white; }\n";
    file << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
    file << ".paid { color: green; font-weight: bold; }\n";
    file << ".unpaid { color: red; font-weight: bold; }\n";
    file << ".summary { margin-top: 20px; padding: 15px; background: #e3f2fd; border-radius: 5px; }\n";
    file << "</style>\n</head>\n<body>\n";

    file << "<h1>BAO CAO TONG HOP HOA DON</h1>\n";
    file << "<div style='text-align: right; color: #666;'>Ngay: " << getCurrentDate() << "</div>\n";

    file << "<table>\n<thead>\n<tr>\n";
    file << "<th>Ma Hoa Don</th><th>Ma Phong</th><th>Thang</th>";
    file << "<th>Dien (kWh)</th><th>Nuoc (m3)</th><th>Tong Tien</th><th>Trang Thai</th>\n";
    file << "</tr>\n</thead>\n<tbody>\n";

    double totalRevenue = 0;
    double paidAmount = 0;
    double unpaidAmount = 0;
    int paidCount = 0;
    int unpaidCount = 0;

    for (const auto& bill : bills) {
        file << "<tr>\n";
        file << "<td>" << bill->getBillId() << "</td>";
        file << "<td>" << bill->getRoomId() << "</td>";
        file << "<td>" << bill->getMonth() << "</td>";
        file << "<td>" << bill->getElectricityUsed() << "</td>";
        file << "<td>" << bill->getWaterUsed() << "</td>";
        file << "<td>" << fixed << setprecision(0) << bill->getTotalAmount() << " VND</td>";

        if (bill->getIsPaid()) {
            file << "<td class='paid'>Da thanh toan</td>";
            paidAmount += bill->getTotalAmount();
            paidCount++;
        }
        else {
            file << "<td class='unpaid'>Chua thanh toan</td>";
            unpaidAmount += bill->getTotalAmount();
            unpaidCount++;
        }
        file << "\n</tr>\n";

        totalRevenue += bill->getTotalAmount();
    }

    file << "</tbody>\n</table>\n";

    // Summary
    file << "<div class='summary'>\n";
    file << "<h3>THONG KE TONG HOP</h3>\n";
    file << "<p><strong>Tong so hoa don:</strong> " << bills.size() << "</p>\n";
    file << "<p><strong>Da thanh toan:</strong> " << paidCount << " hoa don - "
        << fixed << setprecision(0) << paidAmount << " VND</p>\n";
    file << "<p><strong>Chua thanh toan:</strong> " << unpaidCount << " hoa don - "
        << unpaidAmount << " VND</p>\n";
    file << "<p><strong>Tong doanh thu:</strong> " << totalRevenue << " VND</p>\n";
    file << "<p><strong>Ty le thanh toan:</strong> "
        << fixed << setprecision(1) << (bills.size() > 0 ? paidCount * 100.0 / bills.size() : 0) << "%</p>\n";
    file << "</div>\n";

    file << "</body>\n</html>";
    file.close();
    cout << "Xuat bao cao hoa don thanh cong: " << filename << endl;
}

void Reports::exportUnpaidBillsReport(const vector<Bill*>& bills,
    const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file << "BAO CAO HOA DON CHUA THANH TOAN\n";
    file << "Ngay: " << getCurrentDate() << "\n\n";

    file << left << setw(15) << "Ma Hoa Don"
        << setw(12) << "Ma Phong"
        << setw(12) << "Thang"
        << setw(12) << "Dien(kWh)"
        << setw(12) << "Nuoc(m3)"
        << setw(15) << "Tong Tien\n";
    file << string(80, '-') << "\n";

    double totalUnpaid = 0;
    int count = 0;

    for (const auto& bill : bills) {
        if (!bill->getIsPaid()) {
            file << left << setw(15) << bill->getBillId()
                << setw(12) << bill->getRoomId()
                << setw(12) << bill->getMonth()
                << setw(12) << bill->getElectricityUsed()
                << setw(12) << bill->getWaterUsed()
                << setw(15) << fixed << setprecision(0) << bill->getTotalAmount() << "\n";
            totalUnpaid += bill->getTotalAmount();
            count++;
        }
    }

    file << string(80, '-') << "\n";
    file << "Tong so hoa don chua thanh toan: " << count << "\n";
    file << "Tong tien chua thu: " << totalUnpaid << " VND\n";

    file.close();
    cout << "Xuat bao cao hoa don chua thanh toan thanh cong: " << filename << endl;
}

void Reports::exportMonthlyRevenueReport(const vector<Bill*>& bills,
    const string& month,
    const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    file << "BAO CAO DOANH THU THANG " << month << "\n";
    file << "Ngay xuat: " << getCurrentDate() << "\n\n";

    double totalElectricity = 0;
    double totalWater = 0;
    double totalService = 0;
    double totalRevenue = 0;
    int billCount = 0;

    for (const auto& bill : bills) {
        if (bill->getMonth() == month && bill->getIsPaid()) {
            totalElectricity += bill->getElectricityUsed() * bill->getElectricityPrice();
            totalWater += bill->getWaterUsed() * bill->getWaterPrice();
            totalService += bill->getServiceCharges();
            totalRevenue += bill->getTotalAmount();
            billCount++;
        }
    }

    file << "So hoa don da thanh toan: " << billCount << "\n\n";
    file << "CHI TIET DOANH THU:\n";
    file << string(50, '-') << "\n";
    file << left << setw(30) << "Doanh thu dien:"
        << right << setw(15) << fixed << setprecision(0) << totalElectricity << " VND\n";
    file << left << setw(30) << "Doanh thu nuoc:"
        << right << setw(15) << totalWater << " VND\n";
    file << left << setw(30) << "Phi dich vu:"
        << right << setw(15) << totalService << " VND\n";
    file << string(50, '-') << "\n";
    file << left << setw(30) << "TONG DOANH THU:"
        << right << setw(15) << totalRevenue << " VND\n";

    file.close();
    cout << "Xuat bao cao doanh thu thang thanh cong: " << filename << endl;
}