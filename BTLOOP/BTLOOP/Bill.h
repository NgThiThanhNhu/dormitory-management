#pragma once
#ifndef BILL_H
#define BILL_H

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Bill {
private:
    string billId;
    string roomId;
    string month;          
    int electricityUsed;   
    int waterUsed;         
    double electricityPrice; 
    double waterPrice;      
    double serviceCharges;  
    double totalAmount;
    bool isPaid;
    string paymentDate;
    string notes;

public:
    Bill();
    Bill(string billId, string roomId, string month,
        int elecUsed, int waterUsed);

    ~Bill();

    string getBillId() const;
    string getRoomId() const;
    string getMonth() const;
    int getElectricityUsed() const;
    int getWaterUsed() const;
    double getElectricityPrice() const;
    double getWaterPrice() const;
    double getServiceCharges() const;
    double getTotalAmount() const;
    bool getIsPaid() const;
    string getPaymentDate() const;
    string getNotes() const;

    void setBillId(string id);
    void setRoomId(string roomId);
    void setMonth(string month);
    void setElectricityUsed(int used);
    void setWaterUsed(int used);
    void setElectricityPrice(double price);
    void setWaterPrice(double price);
    void setServiceCharges(double charges);
    void setNotes(string notes);

    void calculateTotal();
    void markAsPaid();
    void display() const;
    void input();
    void printReceipt() const;
};

#endif
