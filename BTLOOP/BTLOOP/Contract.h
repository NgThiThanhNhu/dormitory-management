#pragma once
#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <iostream>
using namespace std;

class Contract {
private:
    string contractId;
    string studentId;
    string roomId;
    string startDate;
    string endDate;
    double monthlyFee;
    double deposit;
    bool isActive;

public:
    
    Contract();
    Contract(string contractId, string studentId, string roomId,
        string startDate, string endDate, double monthlyFee, double deposit);
    
    ~Contract();

    string getContractId() const;
    string getStudentId() const;
    string getRoomId() const;
    string getStartDate() const;
    string getEndDate() const;
    double getMonthlyFee() const;
    double getDeposit() const;
    bool getIsActive() const;

    // Setter methods
    void setContractId(string id);
    void setStudentId(string studentId);
    void setRoomId(string roomId);
    void setStartDate(string date);
    void setEndDate(string date);
    void setMonthlyFee(double fee);
    void setDeposit(double deposit);
    void setIsActive(bool status);

    // Methods
    void terminateContract();
    void display() const;
    void input();
};

#endif

