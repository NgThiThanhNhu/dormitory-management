#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include <iostream>
#include <vector>  // ✅ Thêm include vector
using namespace std;

enum UserRole {
    ADMIN,      // Quản trị viên - toàn quyền
    MANAGER,    // Quản lý - quản lý sinh viên, phòng, hóa đơn
    STAFF,      // Nhân viên - xem thông tin, bảo trì
    STUDENT     // Sinh viên - chỉ xem thông tin của mình
};

class authentication {
private:
    string userId;
    string username;
    string password;
    string fullName;
    UserRole role;
    bool isActive;
    string email;
    string phoneNumber;
    string createdDate;
    string lastLogin;

public:
    // Constructor
    authentication();
    authentication(string userId, string username, string password,
        string fullName, UserRole role);

    // Destructor
    ~authentication();

    // Getter methods
    string getUserId() const;
    string getUsername() const;
    string getPassword() const;
    string getFullName() const;
    UserRole getRole() const;
    bool getIsActive() const;
    string getEmail() const;
    string getPhoneNumber() const;
    string getCreatedDate() const;
    string getLastLogin() const;

    // Setter methods
    void setUserId(string id);
    void setUsername(string username);
    void setPassword(string password);
    void setFullName(string name);
    void setRole(UserRole role);
    void setIsActive(bool status);
    void setEmail(string email);
    void setPhoneNumber(string phone);
    void setCreatedDate(string date);
    void setLastLogin(string date);

    // Business methods
    bool authenticate(string username, string password);
    void changePassword(string oldPass, string newPass);
    void updateLastLogin();
    bool hasPermission(string action) const;
    void display() const;
    void input();

    // Static helpers
    static string roleToString(UserRole role);
    static UserRole intToRole(int choice);
};

// Authentication Manager
class AuthManager {
private:
    authentication* currentUser;

public:
    AuthManager();
    ~AuthManager();

    // ✅ ĐỔI SANG NHẬN VECTOR
    bool login(string username, string password, vector<authentication*>& authentications);
    void logout();
    authentication* getCurrentUser() const;
    bool isLoggedIn() const;
    bool checkPermission(string action) const;
};

#endif