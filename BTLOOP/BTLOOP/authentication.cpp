#include "authentication.h"
#include <ctime>

// ==================== USER CLASS ====================

authentication::authentication() {
    userId = "";
    username = "";
    password = "";
    fullName = "";
    role = STUDENT;
    isActive = true;
    email = "";
    phoneNumber = "";
    createdDate = "";
    lastLogin = "";
}

authentication::authentication(string userId, string username, string password,
    string fullName, UserRole role) {
    this->userId = userId;
    this->username = username;
    this->password = password;
    this->fullName = fullName;
    this->role = role;
    this->isActive = true;
    this->email = "";
    this->phoneNumber = "";

    // Set created date
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    char buffer[11];
    sprintf_s(buffer, sizeof(buffer), "%02d/%02d/%04d",
        ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year);

    this->createdDate = buffer;

    this->lastLogin = "";
}

authentication::~authentication() {}

// Getters
string authentication::getUserId() const { return userId; }
string authentication::getUsername() const { return username; }
string authentication::getPassword() const { return password; }
string authentication::getFullName() const { return fullName; }
UserRole authentication::getRole() const { return role; }
bool authentication::getIsActive() const { return isActive; }
string authentication::getEmail() const { return email; }
string authentication::getPhoneNumber() const { return phoneNumber; }
string authentication::getCreatedDate() const { return createdDate; }
string authentication::getLastLogin() const { return lastLogin; }

// Setters
void authentication::setUserId(string id) { this->userId = id; }
void authentication::setUsername(string username) { this->username = username; }
void authentication::setPassword(string password) { this->password = password; }
void authentication::setFullName(string name) { this->fullName = name; }
void authentication::setRole(UserRole role) { this->role = role; }
void authentication::setIsActive(bool status) { this->isActive = status; }
void authentication::setEmail(string email) { this->email = email; }
void authentication::setPhoneNumber(string phone) { this->phoneNumber = phone; }
void authentication::setCreatedDate(string date) { this->createdDate = date; }
void authentication::setLastLogin(string date) { this->lastLogin = date; }

// Business methods
bool authentication::authenticate(string user, string pass) {
    return (username == user && password == pass && isActive);
}

void authentication::changePassword(string oldPass, string newPass) {
    if (password == oldPass) {
        password = newPass;
        cout << "Doi mat khau thanh cong!" << endl;
    }
    else {
        cout << "Mat khau cu khong dung!" << endl;
    }
}

void authentication::updateLastLogin() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    char buffer[20];
    sprintf_s(buffer, sizeof(buffer), "%02d/%02d/%04d %02d:%02d",
        ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year,
        ltm.tm_hour, ltm.tm_min);

    lastLogin = buffer;
}


bool authentication::hasPermission(string action) const {
    if (!isActive) return false;

    if (role == ADMIN) return true;

    if (role == MANAGER) {
        if (action == "delete_building" || action == "manage_users") {
            return false;
        }
        return true;
    }

    if (role == STAFF) {
        if (action == "view" || action == "maintenance" || action == "search") {
            return true;
        }
        return false;
    }

    if (role == STUDENT) {
        if (action == "view_own" || action == "request_maintenance") {
            return true;
        }
        return false;
    }

    return false;
}

void authentication::display() const {
    cout << "Ma nguoi dung: " << userId << endl;
    cout << "Ten dang nhap: " << username << endl;
    cout << "Ho ten: " << fullName << endl;
    cout << "Vai tro: " << roleToString(role) << endl;
    cout << "Trang thai: " << (isActive ? "Hoat dong" : "Khoa") << endl;
    if (!email.empty()) {
        cout << "Email: " << email << endl;
    }
    if (!phoneNumber.empty()) {
        cout << "So dien thoai: " << phoneNumber << endl;
    }
    cout << "Ngay tao: " << createdDate << endl;
    if (!lastLogin.empty()) {
        cout << "Dang nhap cuoi: " << lastLogin << endl;
    }
}

void authentication::input() {
    cout << "Nhap ma nguoi dung: ";
    cin.ignore();
    getline(cin, userId);
    cout << "Nhap ten dang nhap: ";
    getline(cin, username);
    cout << "Nhap mat khau: ";
    getline(cin, password);
    cout << "Nhap ho ten: ";
    getline(cin, fullName);

    cout << "\nChon vai tro:" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Manager" << endl;
    cout << "3. Staff" << endl;
    cout << "4. Student" << endl;
    cout << "Chon: ";
    int choice;
    cin >> choice;
    role = intToRole(choice);
    cin.ignore();

    cout << "Nhap email: ";
    getline(cin, email);
    cout << "Nhap so dien thoai: ";
    getline(cin, phoneNumber);
}

string authentication::roleToString(UserRole role) {
    switch (role) {
    case ADMIN: return "Quan tri vien";
    case MANAGER: return "Quan ly";
    case STAFF: return "Nhan vien";
    case STUDENT: return "Sinh vien";
    default: return "Khong xac dinh";
    }
}

UserRole authentication::intToRole(int choice) {
    switch (choice) {
    case 1: return ADMIN;
    case 2: return MANAGER;
    case 3: return STAFF;
    case 4: return STUDENT;
    default: return STUDENT;
    }
}

// ==================== AUTH MANAGER CLASS ====================

AuthManager::AuthManager() {
    currentUser = nullptr;
}

AuthManager::~AuthManager() {
    currentUser = nullptr;
}

// SỬA HÀM LOGIN ĐỂ NHẬN VECTOR
bool AuthManager::login(string username, string password, vector<authentication*>& authentications) {
    for (auto user : authentications) {
        if (user != nullptr && user->authenticate(username, password)) {
            currentUser = user;
            currentUser->updateLastLogin();
            cout << "\nDang nhap thanh cong!" << endl;
            cout << "Chao mung, " << currentUser->getFullName() << "!" << endl;
            cout << "Vai tro: " << authentication::roleToString(currentUser->getRole()) << endl;
            return true;
        }
    }
    cout << "Ten dang nhap hoac mat khau khong dung!" << endl;
    return false;
}

void AuthManager::logout() {
    if (currentUser != nullptr) {
        cout << "Dang xuat thanh cong. Tam biet!" << endl;
        currentUser = nullptr;
    }
}

authentication* AuthManager::getCurrentUser() const {
    return currentUser;
}

bool AuthManager::isLoggedIn() const {
    return currentUser != nullptr;
}

bool AuthManager::checkPermission(string action) const {
    if (!isLoggedIn()) return false;
    return currentUser->hasPermission(action);
}