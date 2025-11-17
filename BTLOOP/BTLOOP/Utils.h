#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Utils {
public:
    // String utilities
    static vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static string trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        if (string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    static string toUpper(string str) {
        for (char& c : str) {
            c = toupper(c);
        }
        return str;
    }

    static string toLower(string str) {
        for (char& c : str) {
            c = tolower(c);
        }
        return str;
    }

    // Validation utilities
    static bool isValidPhoneNumber(const string& phone) {
        if (phone.length() != 10) return false;
        for (char c : phone) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    static bool isValidDate(const string& date) {
        // Simple validation for dd/mm/yyyy format
        if (date.length() != 10) return false;
        if (date[2] != '/' || date[5] != '/') return false;

        string day = date.substr(0, 2);
        string month = date.substr(3, 2);
        string year = date.substr(6, 4);

        for (char c : day + month + year) {
            if (!isdigit(c)) return false;
        }

        int d = stoi(day);
        int m = stoi(month);
        int y = stoi(year);

        if (d < 1 || d > 31) return false;
        if (m < 1 || m > 12) return false;
        if (y < 1900 || y > 2100) return false;

        return true;
    }

    static bool isValidGPA(double gpa) {
        return gpa >= 0.0 && gpa <= 4.0;
    }

    // Format utilities
    static string formatCurrency(double amount) {
        stringstream ss;
        ss.precision(0);
        ss << fixed << amount;
        return ss.str() + " VND";
    }
};

#endif

