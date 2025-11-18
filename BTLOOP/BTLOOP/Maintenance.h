#pragma once
#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <string>
#include <iostream>
using namespace std;

enum MaintenanceStatus {
    PENDING,      // Chờ xử lý
    IN_PROGRESS,  // Đang xử lý
    COMPLETED,    // Đã hoàn thành
    CANCELLED     // Đã hủy
};

enum MaintenancePriority {
    LOW,
    MEDIUM,
    HIGH,
    URGENT
};

class Maintenance {
private:
    string maintenanceId;
    string roomId;
    string requestedBy;    // Sinh viên yêu cầu
    string deviceName;     // Tên thiết bị
    string issueDescription;
    string requestDate;
    string completedDate;
    MaintenanceStatus status;
    MaintenancePriority priority;
    string assignedTo;     // Người được giao
    double cost;
    string notes;

public:
    // Constructor
    Maintenance();
    Maintenance(string id, string roomId, string requestedBy,
        string device, string issue, string date);

    // Destructor
    ~Maintenance();

    // Getter methods
    string getMaintenanceId() const;
    string getRoomId() const;
    string getRequestedBy() const;
    string getDeviceName() const;
    string getIssueDescription() const;
    string getRequestDate() const;
    string getCompletedDate() const;
    MaintenanceStatus getStatus() const;
    MaintenancePriority getPriority() const;
    string getAssignedTo() const;
    double getCost() const;
    string getNotes() const;

    // Setter methods
    void setMaintenanceId(string id);
    void setRoomId(string roomId);
    void setRequestedBy(string requestedBy);
    void setDeviceName(string device);
    void setIssueDescription(string issue);
    void setRequestDate(string date);
    void setCompletedDate(string date);
    void setStatus(MaintenanceStatus status);
    void setPriority(MaintenancePriority priority);
    void setAssignedTo(string assignedTo);
    void setCost(double cost);
    void setNotes(string notes);

    // Business methods
    void updateStatus(MaintenanceStatus newStatus);
    void complete(double cost);
    void display() const;
    void input();

    // Static helpers
    static string statusToString(MaintenanceStatus status);
    static string priorityToString(MaintenancePriority priority);
};

#endif

