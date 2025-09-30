#include "Revenue.h"
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <regex> 
#include <ctime>

using namespace std;

long long Revenue::calculateRevenueFromFile(const string& filename) {
    long long totalRevenue = 0;
    ifstream inFile(filename);
    string line;

    if (!inFile) {
        cout << "Khong the mo file hoa don.\n";
        return totalRevenue;
    }

    regex totalRegex(R"(Tong cong\s+([\d]+))"); 
    smatch match;

    while (getline(inFile, line)) {
        line = trim(line);

        if (regex_search(line, match, totalRegex)) {
            totalRevenue += stoll(match[1]); 
        }
    }

    inFile.close();
    return totalRevenue;
}

long long Revenue::calculateRevenueByDay(const string& filename, const string& date) {
    long long totalRevenue = 0;
    ifstream inFile(filename);
    string line;

    if (!inFile) {
        cout << "Khong the mo file hoa don.\n";
        return totalRevenue;
    }

    regex totalRegex(R"(Tong cong\s+([\d]+))");
    smatch match;
    bool isTargetDate = false;

    while (getline(inFile, line)) {
        line = trim(line);

        if (line.find("Ngay: " + date) != string::npos) {
            isTargetDate = true; 
        }

        if (isTargetDate && regex_search(line, match, totalRegex)) {
            totalRevenue += stoll(match[1]); 
            isTargetDate = false;         
        }
    }

    inFile.close();
    return totalRevenue;
}

long long Revenue::calculateRevenueByMonth(const string& filename, const string& month) {
    long long totalRevenue = 0;
    ifstream inFile(filename);
    string line;

    if (!inFile) {
        cout << "Khong the mo file hoa don.\n";
        return totalRevenue;
    }

    regex totalRegex(R"(Tong cong\s+([\d]+))");
    smatch match;
    bool isTargetMonth = false;

    while (getline(inFile, line)) {
        line = trim(line);

        if (line.find("Ngay: ") != string::npos && line.substr(9, 7) == month) {
            isTargetMonth = true; 
        }

        if (isTargetMonth && regex_search(line, match, totalRegex)) {
            totalRevenue += stoll(match[1]); 
            isTargetMonth = false;      
        }
    }

    inFile.close();
    return totalRevenue;
}

long long Revenue::calculateRevenueByYear(const string& filename, const string& year) {
    long long totalRevenue = 0;
    ifstream inFile(filename);
    string line;

    if (!inFile) {
        cout << "Khong the mo file hoa don.\n";
        return totalRevenue;
    }

    regex totalRegex(R"(Tong cong\s+([\d]+))");
    smatch match;
    bool isTargetYear = false;

    while (getline(inFile, line)) {
        line = trim(line);

        if (line.find("Ngay: ") != string::npos && line.substr(12, 4) == year) {
            isTargetYear = true; 
        }

        if (isTargetYear && regex_search(line, match, totalRegex)) {
            totalRevenue += stoll(match[1]); 
            isTargetYear = false;  
        }
    }

    inFile.close();
    return totalRevenue;
}

void Revenue::revenueMenu(const string& filename) {
    int choice;
    long long revenue;

    do {
        cout << "========== MENU TINH DOANH THU ==========\n";
        cout << "1. Tinh doanh thu theo ngay\n";
        cout << "2. Tinh doanh thu theo thang\n";
        cout << "3. Tinh doanh thu theo nam\n";
        cout << "4. Quay lai menu chinh\n";
        cout << "=========================================\n";
        cout << "Nhap lua chon cua ban: ";
        string choiceStr = OnlyNumber();
        choice = stoi(choiceStr);
        
        switch (choice) {
            case 1: { // Tinh doanh thu theo ngay
                int year, month, day;
                cout << "Nhap ngay (DD): ";
                cin >> day;
                cout << "Nhap thang (MM): ";
                cin >> month;
                cout << "Nhap nam (YYYY): ";
                cin >> year;
				
				system("cls");
                stringstream dateStream;
                dateStream << setw(2) << setfill('0') << day << "-"
                           << setw(2) << setfill('0') << month << "-"
                           << setw(4) << setfill('0') << year;
                string date = dateStream.str();

                revenue = Revenue::calculateRevenueByDay(filename, date);
                cout << "Doanh thu ngay " << date << ": " << revenue << " VND\n";
                break;
            }
            case 2: { // Tinh doanh thu theo thang
                int year, month;
                cout << "Nhap thang (MM): ";
                cin >> month;
                cout << "Nhap nam (YYYY): ";
                cin >> year;

				system("cls");
                stringstream monthStream;
                monthStream << setw(2) << setfill('0') << month << "-"
                            << setw(4) << setfill('0') << year;
                string monthStr = monthStream.str();

                revenue = Revenue::calculateRevenueByMonth(filename, monthStr);
                cout << "Doanh thu thang " << monthStr << ": " << revenue << " VND\n";
                break;
            }
            case 3: { // Tinh doanh thu theo nam
                int year;
                cout << "Nhap nam (YYYY): ";
                cin >> year;

				system("cls");	
                stringstream yearStream;
                yearStream << setw(4) << setfill('0') << year;
                string yearStr = yearStream.str();

                revenue = Revenue::calculateRevenueByYear(filename, yearStr);
                cout << "Doanh thu nam " << yearStr << ": " << revenue << " VND\n";
                break;
            }
            case 4: 
                cout << "Quay lai menu chinh\n";
                break;

            default:
                cout << "Lua chon khong hop le! Vui long thu lai.\n";
        }

    } while (choice != 4);
}

