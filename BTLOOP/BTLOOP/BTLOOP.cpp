#include <iostream>
#include <limits>
#include "DormManager.h"

using namespace std;

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

void displayMainMenu() {
    cout << "\n===============================================" << endl;
    cout << "    HE THONG QUAN LY KY TUC XA SINH VIEN      " << endl;
    cout << "===============================================" << endl;
    cout << "1.  Quan ly sinh vien" << endl;
    cout << "2.  Quan ly toa nha" << endl;
    cout << "3.  Quan ly phong" << endl;
    cout << "4.  Quan ly hop dong" << endl;
    cout << "5.  Phan phong cho sinh vien" << endl;
    cout << "6.  Xem thong ke" << endl;
    cout << "7.  Luu du lieu" << endl;
    cout << "8.  Doc du lieu" << endl;
    cout << "0.  Thoat chuong trinh" << endl;
    cout << "===============================================" << endl;
    cout << "Chon chuc nang: ";
}

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
            cout << "Nhap ma toa nha can xoa: ";
            cin >> id;
            manager.deleteBuilding(id);
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

int main() {
    DormManager manager;
    int choice;
    string studentId, roomId, filename;

    do {
        clearScreen();
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            studentMenu(manager);
            break;
        case 2:
            buildingMenu(manager);
            break;
        case 3:
            roomMenu(manager);
            break;
        case 4:
            contractMenu(manager);
            break;
        case 5:
            clearScreen();
            cout << "Nhap ma sinh vien: ";
            cin >> studentId;
            cout << "Nhap ma phong: ";
            cin >> roomId;
            manager.assignStudentToRoom(studentId, roomId);
            pause();
            break;
        case 6:
            clearScreen();
            manager.displayStatistics();
            pause();
            break;
        case 7:
            clearScreen();
            cout << "Nhap ten file: ";
            cin >> filename;
            manager.saveToFile(filename);
            pause();
            break;
        case 8:
            clearScreen();
            cout << "Nhap ten file: ";
            cin >> filename;
            manager.loadFromFile(filename);
            pause();
            break;
        case 0:
            cout << "\nCam on ban da su dung chuong trinh!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
        }
    } while (choice != 0);

    return 0;
}