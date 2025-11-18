#pragma once
#ifndef VIOLATION_H
#define VIOLATION_H

#include <string>
#include <iostream>
using namespace std;

enum ViolationType {
    NOISE,              // Gây ồn
    LATE_RETURN,        // Về muộn
    UNAUTHORIZED_GUEST, // Khách không phép
    SMOKING,            // Hút thuốc
    ALCOHOL,            // Sử dụng rượu bia
    DAMAGE_PROPERTY,    // Làm hư hỏng tài sản
    ILLEGAL_DEVICE,     // Sử dụng thiết bị không cho phép
    HYGIENE,            // Vi phạm vệ sinh
    FIGHTING,           // Đánh nhau
    OTHER               // Khác
};

class Violation {
private:
    string violationId;
    string studentId;
    string roomId;
    ViolationType type;
    string description;
    string date;
    double fineAmount;
    bool isPaid;
    string reportedBy;    // Người báo cáo
    string notes;

public:
    // Constructor
    Violation();
    Violation(string violationId, string studentId, string roomId,
        ViolationType type, string description, string date);

    // Destructor
    ~Violation();

    // Getter methods
    string getViolationId() const;
    string getStudentId() const;
    string getRoomId() const;
    ViolationType getType() const;
    string getDescription() const;
    string getDate() const;
    double getFineAmount() const;
    bool getIsPaid() const;
    string getReportedBy() const;
    string getNotes() const;

    // Setter methods
    void setViolationId(string id);
    void setStudentId(string studentId);
    void setRoomId(string roomId);
    void setType(ViolationType type);
    void setDescription(string desc);
    void setDate(string date);
    void setFineAmount(double amount);
    void setReportedBy(string reporter);
    void setNotes(string notes);

    // Business methods
    void markAsPaid();
    string getTypeString() const;
    void display() const;
    void input();

    // Static helper
    static string violationTypeToString(ViolationType type);
    static ViolationType stringToViolationType(int choice);
};

#endif

