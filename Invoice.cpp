#include "Invoice.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


void Invoice::displayInvoicesByDay(const string& filename, const string& date) {
    ifstream inFile(filename);
    string line;
    bool found = false;

    if (!inFile.is_open()) {
        cout << "Khong the mo file hoa don.\n";
        return;
    }

    cout << "========== HOA DON NGAY " << date << " ==========\n";

    while (getline(inFile, line)) {
        if (line.find("Ngay: " + date) != string::npos) {
            found = true;
            do {
                cout << line << endl;
            } while (getline(inFile, line) && !line.empty());
            cout << "===============================================\n";
        }
    }

    if (!found) {
        cout << "Khong tim thay hoa don cho ngay " << date << ".\n";
    }

    inFile.close();
}

void Invoice::displayInvoicesByMonth(const string& filename, const string& month) {
    ifstream inFile(filename);
    string line;
    bool found = false;

    if (!inFile.is_open()) {
        cout << "Khong the mo file hoa don.\n";
        return;
    }

    cout << "========== HOA DON THANG " << month << " ==========\n";

    while (getline(inFile, line)) {
        if (line.find("Ngay: ") != string::npos && line.substr(9, 7) == month) {
            found = true;
            do {
                cout << line << endl;
            } while (getline(inFile, line) && !line.empty());
            cout << "===============================================\n";
        }
    }

    if (!found) {
        cout << "Khong the tim thay hoa don cho thang " << month << ".\n";
    }

    inFile.close();
}

void Invoice::displayInvoicesByYear(const string& filename, const string& year) {
    ifstream inFile(filename);
    string line;
    bool found = false;

    if (!inFile.is_open()) {
        cout << "Khong the mo file hoa don.\n";
        return;
    }

    cout << "========== HOA DON NAM " << year << " ==========\n";

    while (getline(inFile, line)) {
        if (line.find("Ngay: ") != string::npos && line.substr(12, 4) == year) {
            found = true;
            do {
                cout << line << endl;
            } while (getline(inFile, line) && !line.empty());
            cout << "===============================================\n";
        }
    }

    if (!found) {
        cout << "Khong tim thay hoa don cho nam " << year << ".\n";
    }

    inFile.close();
}

void Invoice::displayAllInvoices(const string& filename) {
    ifstream inFile(filename);
    string line;

    if (!inFile.is_open()) {
        cout << "Khong the mo file hoa don.\n";
        return;
    }

    cout << "========== TOAN BO HOA DON ==========\n";
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    cout << "======================================\n";

    inFile.close();
}


void Invoice::displayInvoicesMenu() {
    int choice;
    int day, month, year;

    do {
        cout << "========== HIEN THI HOA DON ==========\n";
        cout << "1. Hien thi hoa don theo ngay\n";
        cout << "2. Hien thi hoa don theo thang\n";
        cout << "3. Hien thi hoa don theo nam\n";
        cout << "4. Hien thi toan bo hoa don\n";
        cout << "5. Quay lai menu chinh\n";
        cout << "=======================================\n";
        cout << "Nhap lua chon cua ban: ";
        string choiceStr = OnlyNumber();
        choice = stoi(choiceStr);

        switch (choice) {
            case 1: { 
            	system("cls");
                cout << "Nhap ngay (DD): ";
                cin >> day;
                cout << "Nhap thang (MM): ";
                cin >> month;
                cout << "Nhap nam (YYYY): ";
                cin >> year;

                stringstream dateStream;
                dateStream << setw(2) << setfill('0') << day << "-"
                           << setw(2) << setfill('0') << month << "-"
                           << setw(4) << year;
                string date = dateStream.str();

                displayInvoicesByDay("invoice.txt", date);
                system("pause");
                system("cls");
                break;
            }
            case 2: { 
            	system("cls");
                cout << "Nhap thang (MM): ";
                cin >> month;
                cout << "Nhap nam (YYYY): ";
                cin >> year;

                stringstream monthStream;
                monthStream << setw(2) << setfill('0') << month << "-"
                            << setw(4) << year;
                string monthStr = monthStream.str();

                displayInvoicesByMonth("invoice.txt", monthStr);
                system("pause");
                system("cls");
                break;
            }
            case 3: { 
            	system("cls");
                cout << "Nhap nam (YYYY): ";
                cin >> year;

                displayInvoicesByYear("invoice.txt", to_string(year));
                system("pause");
                system("cls");
                break;
            }
            case 4: {
				system("cls"); 
                displayAllInvoices("invoice.txt");
                system("pause");
                system("cls");
                break;
            }
            case 5: 
            	system("cls");
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    } while (choice != 5);
}

