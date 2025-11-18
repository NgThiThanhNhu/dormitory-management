#include <iostream>
#include <limits>
#include <vector>
#include "DormManager.h"
#include "Bill.h"
#include "Violation.h"
#include "Maintenance.h"
#include "authentication.h"
#include "Reports.h"
#include "Student.h"
#include "Violation.h"
#include "Utils.h"
#include "Room.h"
#include "Person.h"
#include "Contract.h"
#include "Building.h"

using namespace std;

// Global variables
AuthManager authManager;
vector<Bill*> bills;
vector<Violation*> violations;
vector<Maintenance*> maintenances;
vector<authentication*> authentications;  

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void initializeDefaultUsers() {
    // Create default admin account
    authentication* admin = new authentication("U001", "admin", "admin123", "Quan Tri Vien", ADMIN);
    authentications.push_back(admin);

    authentication* manager = new authentication("U002", "manager", "manager123", "Nguyen Van A", MANAGER);
    authentications.push_back(manager);

    authentication* staff = new authentication("U003", "staff", "staff123", "Tran Thi B", STAFF);
    authentications.push_back(staff);

    authentication* student = new authentication("U004", "student", "student1068", "Nguyen Thi Thanh Nhu", STUDENT);
    authentications.push_back(student);
}

// ✅ SỬA HÀM loginScreen
bool loginScreen() {
    clearScreen();
    cout << "\n===============================================" << endl;
    cout << "    HE THONG QUAN LY KY TUC XA SINH VIEN      " << endl;
    cout << "                DANG NHAP                      " << endl;
    cout << "===============================================" << endl;

    string username, password;
    cout << "Ten dang nhap: ";
    cin >> username;
    cout << "Mat khau: ";
    cin >> password;

    //GỌI TRỰC TIẾP VỚI VECTOR - KHÔNG CẦN CHUYỂN MẢNG
    return authManager.login(username, password, authentications);
}

void displayMainMenu() {
    cout << "\n===============================================" << endl;
    cout << "    HE THONG QUAN LY KY TUC XA    " << endl;
    cout << "    Nguoi dung: " << authManager.getCurrentUser()->getFullName() << endl;
    cout << "    Vai tro: " << authentication::roleToString(authManager.getCurrentUser()->getRole()) << endl;
    cout << "===============================================" << endl;
    cout << "1.  Quan ly sinh vien" << endl;
    cout << "2.  Quan ly toa nha" << endl;
    cout << "3.  Quan ly phong" << endl;
    cout << "4.  Quan ly hop dong" << endl;
    cout << "5.  Phan phong cho sinh vien" << endl;
    cout << "6.  Quan ly hoa don dien nuoc" << endl;
    cout << "7.  Quan ly vi pham noi quy" << endl;
    cout << "8.  Quan ly bao tri thiet bi" << endl;
    cout << "9.  Bao cao va thong ke" << endl;
    cout << "10. Quan ly nguoi dung" << endl;
    cout << "11. Thay doi mat khau" << endl;
    cout << "0.  Dang xuat" << endl;
    cout << "===============================================" << endl;
    cout << "Chon chuc nang: ";
}

// Forward declarations
void studentMenu(DormManager& manager);
void buildingMenu(DormManager& manager);
void roomMenu(DormManager& manager);
void contractMenu(DormManager& manager);

// ==================== BILL MANAGEMENT ====================

void billMenu(DormManager& manager) {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY HOA DON DIEN NUOC ==========" << endl;
        cout << "1. Tao hoa don moi" << endl;
        cout << "2. Hien thi tat ca hoa don" << endl;
        cout << "3. Tim kiem hoa don" << endl;
        cout << "4. Thanh toan hoa don" << endl;
        cout << "5. Hien thi hoa don chua thanh toan" << endl;
        cout << "6. In phieu thanh toan" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (!authManager.checkPermission("manage_bills")) {
                cout << "Ban khong co quyen thuc hien chuc nang nay!" << endl;
                pause();
                break;
            }
            clearScreen();
            Bill* newBill = new Bill();
            newBill->input();
            bills.push_back(newBill);
            cout << "Tao hoa don thanh cong!" << endl;
            pause();
            break;
        }
        case 2: {
            clearScreen();
            if (bills.empty()) {
                cout << "Khong co hoa don nao!" << endl;
            }
            else {
                for (const auto& bill : bills) {
                    bill->display();
                    cout << "----------------------------------------" << endl;
                }
            }
            pause();
            break;
        }
        case 3: {
            clearScreen();
            cout << "Nhap ma hoa don: ";
            cin >> id;
            bool found = false;
            for (const auto& bill : bills) {
                if (bill->getBillId() == id) {
                    bill->display();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay hoa don!" << endl;
            }
            pause();
            break;
        }
        case 4: {
            if (!authManager.checkPermission("manage_bills")) {
                cout << "Ban khong co quyen thuc hien chuc nang nay!" << endl;
                pause();
                break;
            }
            clearScreen();
            cout << "Nhap ma hoa don can thanh toan: ";
            cin >> id;
            bool found = false;
            for (auto& bill : bills) {
                if (bill->getBillId() == id) {
                    bill->markAsPaid();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay hoa don!" << endl;
            }
            pause();
            break;
        }
        case 5: {
            clearScreen();
            cout << "DANH SACH HOA DON CHUA THANH TOAN:\n" << endl;
            bool found = false;
            for (const auto& bill : bills) {
                if (!bill->getIsPaid()) {
                    bill->display();
                    cout << "----------------------------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Tat ca hoa don da duoc thanh toan!" << endl;
            }
            pause();
            break;
        }
        case 6: {
            clearScreen();
            cout << "Nhap ma hoa don: ";
            cin >> id;
            bool found = false;
            for (const auto& bill : bills) {
                if (bill->getBillId() == id) {
                    bill->printReceipt();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay hoa don!" << endl;
            }
            pause();
            break;
        }
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

// ==================== VIOLATION MANAGEMENT ====================

void violationMenu(DormManager& manager) {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY VI PHAM NOI QUY ==========" << endl;
        cout << "1. Them vi pham moi" << endl;
        cout << "2. Hien thi tat ca vi pham" << endl;
        cout << "3. Tim kiem vi pham theo sinh vien" << endl;
        cout << "4. Danh dau da dong phat" << endl;
        cout << "5. Hien thi vi pham chua xu ly" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (!authManager.checkPermission("manage_violations")) {
                cout << "Ban khong co quyen thuc hien chuc nang nay!" << endl;
                pause();
                break;
            }
            clearScreen();
            Violation* newViolation = new Violation();
            newViolation->input();
            violations.push_back(newViolation);
            cout << "Them vi pham thanh cong!" << endl;
            pause();
            break;
        }
        case 2: {
            clearScreen();
            if (violations.empty()) {
                cout << "Khong co vi pham nao!" << endl;
            }
            else {
                for (const auto& violation : violations) {
                    violation->display();
                    cout << "----------------------------------------" << endl;
                }
            }
            pause();
            break;
        }
        case 3: {
            clearScreen();
            cout << "Nhap ma sinh vien: ";
            cin >> id;
            bool found = false;
            for (const auto& violation : violations) {
                if (violation->getStudentId() == id) {
                    violation->display();
                    cout << "----------------------------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Khong tim thay vi pham nao!" << endl;
            }
            pause();
            break;
        }
        case 4: {
            if (!authManager.checkPermission("manage_violations")) {
                cout << "Ban khong co quyen thuc hien chuc nang nay!" << endl;
                pause();
                break;
            }
            clearScreen();
            cout << "Nhap ma vi pham: ";
            cin >> id;
            bool found = false;
            for (auto& violation : violations) {
                if (violation->getViolationId() == id) {
                    violation->markAsPaid();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay vi pham!" << endl;
            }
            pause();
            break;
        }
        case 5: {
            clearScreen();
            cout << "VI PHAM CHUA DONG PHAT:\n" << endl;
            bool found = false;
            for (const auto& violation : violations) {
                if (!violation->getIsPaid()) {
                    violation->display();
                    cout << "----------------------------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Tat ca vi pham da duoc xu ly!" << endl;
            }
            pause();
            break;
        }
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

// ==================== MAINTENANCE MANAGEMENT ====================

void maintenanceMenu(DormManager& manager) {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY BAO TRI THIET BI ==========" << endl;
        cout << "1. Tao yeu cau bao tri" << endl;
        cout << "2. Hien thi tat ca yeu cau" << endl;
        cout << "3. Cap nhat trang thai" << endl;
        cout << "4. Hoan thanh bao tri" << endl;
        cout << "5. Hien thi yeu cau cho xu ly" << endl;
        cout << "6. Hien thi yeu cau khan cap" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            clearScreen();
            Maintenance* newMaintenance = new Maintenance();
            newMaintenance->input();
            maintenances.push_back(newMaintenance);
            cout << "Tao yeu cau bao tri thanh cong!" << endl;
            pause();
            break;
        }
        case 2: {
            clearScreen();
            if (maintenances.empty()) {
                cout << "Khong co yeu cau bao tri nao!" << endl;
            }
            else {
                for (const auto& maintenance : maintenances) {
                    maintenance->display();
                    cout << "----------------------------------------" << endl;
                }
            }
            pause();
            break;
        }
        case 3: {
            if (!authManager.checkPermission("maintenance")) {
                cout << "Ban khong co quyen thuc hien chuc nang nay!" << endl;
                pause();
                break;
            }
            clearScreen();
            cout << "Nhap ma bao tri: ";
            cin >> id;
            bool found = false;
            for (auto& maintenance : maintenances) {
                if (maintenance->getMaintenanceId() == id) {
                    cout << "\nChon trang thai moi:" << endl;
                    cout << "1. Cho xu ly" << endl;
                    cout << "2. Dang xu ly" << endl;
                    cout << "3. Da hoan thanh" << endl;
                    cout << "4. Da huy" << endl;
                    int statusChoice;
                    cin >> statusChoice;
                    MaintenanceStatus newStatus;
                    switch (statusChoice) {
                    case 1: newStatus = PENDING; break;
                    case 2: newStatus = IN_PROGRESS; break;
                    case 3: newStatus = COMPLETED; break;
                    case 4: newStatus = CANCELLED; break;
                    default: newStatus = PENDING;
                    }
                    maintenance->updateStatus(newStatus);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay yeu cau bao tri!" << endl;
            }
            pause();
            break;
        }
        case 4: {
            if (!authManager.checkPermission("maintenance")) {
                cout << "Ban khong co quyen thuc hien chuc nang nay!" << endl;
                pause();
                break;
            }
            clearScreen();
            cout << "Nhap ma bao tri: ";
            cin >> id;
            bool found = false;
            for (auto& maintenance : maintenances) {
                if (maintenance->getMaintenanceId() == id) {
                    double cost;
                    cout << "Nhap chi phi bao tri: ";
                    cin >> cost;
                    maintenance->complete(cost);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay yeu cau bao tri!" << endl;
            }
            pause();
            break;
        }
        case 5: {
            clearScreen();
            cout << "YEU CAU BAO TRI CHO XU LY:\n" << endl;
            bool found = false;
            for (const auto& maintenance : maintenances) {
                if (maintenance->getStatus() == PENDING) {
                    maintenance->display();
                    cout << "----------------------------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Khong co yeu cau nao cho xu ly!" << endl;
            }
            pause();
            break;
        }
        case 6: {
            clearScreen();
            cout << "YEU CAU BAO TRI KHAN CAP:\n" << endl;
            bool found = false;
            for (const auto& maintenance : maintenances) {
                if (maintenance->getPriority() == URGENT) {
                    maintenance->display();
                    cout << "----------------------------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Khong co yeu cau khan cap!" << endl;
            }
            pause();
            break;
        }
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

// ==================== REPORT MENU ====================

void reportMenu(DormManager& manager) {
    int choice;
    string filename, month;

    do {
        clearScreen();
        cout << "\n========== BAO CAO VA THONG KE ==========" << endl;
        cout << "1. Xuat danh sach sinh vien (CSV)" << endl;
        cout << "2. Xuat danh sach sinh vien (HTML)" << endl;
        cout << "3. Bao cao ty le lap day phong" << endl;
        cout << "4. Bao cao tong hop hoa don" << endl;
        cout << "5. Bao cao hoa don chua thanh toan" << endl;
        cout << "6. Bao cao doanh thu theo thang" << endl;
        cout << "7. Thong ke tong quan he thong" << endl;
        cout << "8. Xem thong ke man hinh" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
        case 2:
        case 3:
        case 7:
            clearScreen();
            cout << "Chuc nang dang phat trien..." << endl;
            pause();
            break;
        case 4: {
            clearScreen();
            cout << "Nhap ten file (vd: bills_summary.html): ";
            cin >> filename;
            Reports::exportBillSummaryReport(bills, filename);
            pause();
            break;
        }
        case 5: {
            clearScreen();
            cout << "Nhap ten file (vd: unpaid_bills.txt): ";
            cin >> filename;
            Reports::exportUnpaidBillsReport(bills, filename);
            pause();
            break;
        }
        case 6: {
            clearScreen();
            cout << "Nhap thang (MM/YYYY): ";
            cin.ignore();
            getline(cin, month);
            cout << "Nhap ten file (vd: revenue_01_2024.txt): ";
            getline(cin, filename);
            Reports::exportMonthlyRevenueReport(bills, month, filename);
            pause();
            break;
        }
        case 8: {
            clearScreen();
            manager.displayStatistics();
            pause();
            break;
        }
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

// ==================== USER MANAGEMENT ====================

// ✅ SỬA HÀM userManagementMenu
void userManagementMenu() {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY NGUOI DUNG ==========" << endl;
        cout << "1. Them nguoi dung moi" << endl;
        cout << "2. Hien thi tat ca nguoi dung" << endl;
        cout << "3. Khoa/Mo khoa nguoi dung" << endl;
        cout << "4. Dat lai mat khau" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (authManager.getCurrentUser()->getRole() != ADMIN) {
                cout << "Chi Admin moi co quyen them nguoi dung!" << endl;
                pause();
                break;
            }
            clearScreen();
            authentication* newUser = new authentication();
            newUser->input();
            authentications.push_back(newUser);  // ✅ SỬA: dùng authentications thay vì users
            cout << "Them nguoi dung thanh cong!" << endl;
            pause();
            break;
        }
        case 2: {
            clearScreen();
            for (const auto& user : authentications) {  // ✅ SỬA: dùng authentications
                user->display();
                cout << "----------------------------------------" << endl;
            }
            pause();
            break;
        }
        case 3: {
            if (authManager.getCurrentUser()->getRole() != ADMIN) {
                cout << "Chi Admin moi co quyen khoa nguoi dung!" << endl;
                pause();
                break;
            }
            clearScreen();
            cout << "Nhap ID nguoi dung: ";
            cin >> id;
            bool found = false;
            for (auto& user : authentications) {  // ✅ SỬA: dùng authentications
                if (user->getUserId() == id) {
                    user->setIsActive(!user->getIsActive());
                    cout << "Da cap nhat trang thai!" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Khong tim thay nguoi dung!" << endl;
            }
            pause();
            break;
        }
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

void changePasswordMenu() {
    clearScreen();
    string oldPass, newPass, confirmPass;

    cout << "\n========== THAY DOI MAT KHAU ==========" << endl;
    cout << "Nhap mat khau cu: ";
    cin >> oldPass;
    cout << "Nhap mat khau moi: ";
    cin >> newPass;
    cout << "Xac nhan mat khau moi: ";
    cin >> confirmPass;

    if (newPass != confirmPass) {
        cout << "Mat khau xac nhan khong khop!" << endl;
    }
    else {
        authManager.getCurrentUser()->changePassword(oldPass, newPass);
    }
    pause();
}

// ==================== MAIN FUNCTION ====================

int main() {
    DormManager manager;

    string dataFilename = "dorm_data.txt";

    // Initialize default users
    initializeDefaultUsers();

    // Login screen
    while (!authManager.isLoggedIn()) {
        if (!loginScreen()) {
            char retry;
            cout << "\nBan co muon thu lai? (y/n): ";
            cin >> retry;
            if (retry != 'y' && retry != 'Y') {
                cout << "Tam biet!" << endl;
                return 0;
            }
        }
    }

    // Main program loop
    int choice;
    string studentId, roomId;

    do {
        clearScreen();
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            if (authManager.checkPermission("manage_students")) {
                studentMenu(manager);
            }
            else {
                cout << "Ban khong co quyen truy cap!" << endl;
                pause();
            }
            break;

        case 2:
            if (authManager.checkPermission("manage_buildings")) {
                buildingMenu(manager);
            }
            else {
                cout << "Ban khong co quyen truy cap!" << endl;
                pause();
            }
            break;

        case 3:
            if (authManager.checkPermission("manage_rooms")) {
                roomMenu(manager);
            }
            else {
                cout << "Ban khong co quyen truy cap!" << endl;
                pause();
            }
            break;

        case 4:
            if (authManager.checkPermission("manage_contracts")) {
                contractMenu(manager);
            }
            else {
                cout << "Ban khong co quyen truy cap!" << endl;
                pause();
            }
            break;

        case 5:
            if (authManager.checkPermission("assign_rooms")) {
                clearScreen();
                cout << "Nhap ma sinh vien: ";
                cin >> studentId;
                cout << "Nhap ma phong: ";
                cin >> roomId;
                manager.assignStudentToRoom(studentId, roomId);
                pause();
            }
            else {
                cout << "Ban khong co quyen truy cap!" << endl;
                pause();
            }
            break;

        case 6:
            billMenu(manager);
            break;

        case 7:
            violationMenu(manager);
            break;

        case 8:
            maintenanceMenu(manager);
            break;

        case 9:
            if (authManager.checkPermission("view_reports")) {
                reportMenu(manager);
            }
            else {
                cout << "Ban khong co quyen truy cap!" << endl;
                pause();
            }
            break;

        case 10:
            if (authManager.getCurrentUser()->getRole() == ADMIN) {
                userManagementMenu();
            }
            else {
                cout << "Chi Admin moi co quyen quan ly nguoi dung!" << endl;
                pause();
            }
            break;

        case 11:
            changePasswordMenu();
            break;

        case 0:
            authManager.logout();
            cout << "\nBan co muon dang nhap lai? (y/n): ";
            char retry;
            cin >> retry;
            if (retry == 'y' || retry == 'Y') {
                while (!authManager.isLoggedIn()) {
                    if (!loginScreen()) {
                        cout << "\nBan co muon thu lai? (y/n): ";
                        cin >> retry;
                        if (retry != 'y' && retry != 'Y') {
                            break;
                        }
                    }
                }
                if (!authManager.isLoggedIn()) {
                    choice = -1;
                }
            }
            else {
                choice = -1;
            }
            break;

        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != -1 && authManager.isLoggedIn());

    // Cleanup
    for (auto bill : bills) delete bill;
    for (auto violation : violations) delete violation;
    for (auto maintenance : maintenances) delete maintenance;
    for (auto user : authentications) delete user;  // ✅ SỬA: dùng authentications

    bills.clear();
    violations.clear();
    maintenances.clear();
    authentications.clear();

    cout << "\nCam on ban da su dung chuong trinh!" << endl;
    cout << "Hen gap lai!" << endl;

    return 0;
}

// ==================== MENU IMPLEMENTATIONS ====================

void studentMenu(DormManager& manager) {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY SINH VIEN ==========" << endl;
        cout << "1. Them sinh vien moi" << endl;
        cout << "2. Hien thi tat ca sinh vien" << endl;
        cout << "3. Tim kiem sinh vien" << endl;
        cout << "4. Cap nhat thong tin sinh vien" << endl;
        cout << "5. Xoa sinh vien" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            clearScreen();
            manager.addStudent();
            pause();
            break;
        case 2:
            clearScreen();
            manager.displayAllStudents();
            pause();
            break;
        case 3:
            clearScreen();
            cout << "Nhap ma sinh vien: ";
            cin >> id;
            manager.searchStudentById(id);
            pause();
            break;
        case 4:
            clearScreen();
            cout << "Nhap ma sinh vien can cap nhat: ";
            cin >> id;
            manager.updateStudent(id);
            pause();
            break;
        case 5:
            clearScreen();
            cout << "Nhap ma sinh vien can xoa: ";
            cin >> id;
            manager.deleteStudent(id);
            pause();
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

void buildingMenu(DormManager& manager) {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY TOA NHA ==========" << endl;
        cout << "1. Them toa nha moi" << endl;
        cout << "2. Hien thi tat ca toa nha" << endl;
        cout << "3. Tim kiem toa nha" << endl;
        cout << "4. Xoa toa nha" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            clearScreen();
            manager.addBuilding();
            pause();
            break;
        case 2:
            clearScreen();
            manager.displayAllBuildings();
            pause();
            break;
        case 3:
            clearScreen();
            cout << "Nhap ma toa nha: ";
            cin >> id;
            manager.searchBuildingById(id);
            pause();
            break;
        case 4:
            clearScreen();
            if (authManager.getCurrentUser()->getRole() != ADMIN) {
                cout << "Chi Admin moi co quyen xoa toa nha!" << endl;
            }
            else {
                cout << "Nhap ma toa nha can xoa: ";
                cin >> id;
                manager.deleteBuilding(id);
            }
            pause();
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

void roomMenu(DormManager& manager) {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY PHONG ==========" << endl;
        cout << "1. Them phong moi vao toa nha" << endl;
        cout << "2. Hien thi tat ca phong" << endl;
        cout << "3. Tim kiem phong" << endl;
        cout << "4. Hien thi phong con trong" << endl;
        cout << "5. Hien thi phong theo toa nha" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            clearScreen();
            cout << "Nhap ma toa nha: ";
            cin >> id;
            manager.addRoomToBuilding(id);
            pause();
            break;
        case 2:
            clearScreen();
            manager.displayAllRooms();
            pause();
            break;
        case 3:
            clearScreen();
            cout << "Nhap ma phong: ";
            cin >> id;
            manager.searchRoomById(id);
            pause();
            break;
        case 4:
            clearScreen();
            manager.displayAvailableRooms();
            pause();
            break;
        case 5:
            clearScreen();
            cout << "Nhap ma toa nha: ";
            cin >> id;
            manager.displayRoomsByBuilding(id);
            pause();
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}

void contractMenu(DormManager& manager) {
    int choice;
    string id;

    do {
        clearScreen();
        cout << "\n========== QUAN LY HOP DONG ==========" << endl;
        cout << "1. Tao hop dong moi" << endl;
        cout << "2. Hien thi tat ca hop dong" << endl;
        cout << "3. Tim kiem hop dong" << endl;
        cout << "4. Huy hop dong" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            clearScreen();
            manager.createContract();
            pause();
            break;
        case 2:
            clearScreen();
            manager.displayAllContracts();
            pause();
            break;
        case 3:
            clearScreen();
            cout << "Nhap ma hop dong: ";
            cin >> id;
            manager.searchContractById(id);
            pause();
            break;
        case 4:
            clearScreen();
            cout << "Nhap ma hop dong can huy: ";
            cin >> id;
            manager.terminateContract(id);
            pause();
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);
}