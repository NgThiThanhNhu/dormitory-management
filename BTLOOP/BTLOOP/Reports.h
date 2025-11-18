#pragma once
#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <vector>
#include <fstream>
#include "Student.h"
#include "Room.h"
#include "Building.h"
#include "Bill.h"
#include "Violation.h"
#include "Maintenance.h"
using namespace std;

class Reports {
public:
    // Student Reports
    static void exportStudentsToCSV(const vector<Student*>& students,
        const string& filename);
    static void exportStudentsToHTML(const vector<Student*>& students,
        const string& filename);

    // Room Reports
    static void exportRoomOccupancyReport(const vector<Building*>& buildings,
        const string& filename);
    static void exportAvailableRoomsReport(const vector<Building*>& buildings,
        const string& filename);

    // Financial Reports
    static void exportBillSummaryReport(const vector<Bill*>& bills,
        const string& filename);
    static void exportUnpaidBillsReport(const vector<Bill*>& bills,
        const string& filename);
    static void exportMonthlyRevenueReport(const vector<Bill*>& bills,
        const string& month,
        const string& filename);

    // Violation Reports
    static void exportViolationReport(const vector<Violation*>& violations,
        const string& filename);
    static void exportViolationByStudentReport(const vector<Violation*>& violations,
        const string& studentId,
        const string& filename);

    // Maintenance Reports
    static void exportMaintenanceReport(const vector<Maintenance*>& maintenances,
        const string& filename);
    static void exportPendingMaintenanceReport(const vector<Maintenance*>& maintenances,
        const string& filename);

    // Statistical Reports
    static void generateStatisticsReport(const vector<Student*>& students,
        const vector<Building*>& buildings,
        const vector<Bill*>& bills,
        const string& filename);

    // Helper methods
    static string getCurrentDate();
    static string escapeCSV(const string& str);
};

#endif

