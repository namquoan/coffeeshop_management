#include "Utilities.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <conio.h>

using namespace std;

// Ham chi cho phep nhap so
string OnlyNumber() {
    string input = "";
    char ch;

    while (true) {
        ch = _getch(); 

        if (ch == 13) { 
            cout << endl;
            break;
        } else if (ch == 8) { 
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b"; 
            }
        } else if (isdigit(ch)) { 
            input += ch;
            cout << ch;
        }
    }

    return input;
}

// Ham chi cho phep nhap chu
string OnlyAlphabet() {
    string input = "";
    char ch;

    while (true) {
        ch = _getch(); 

        if (ch == 13) { 
            cout << endl;
            break;
        } else if (ch == 8) { 
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b"; 
            }
        } else if (isalpha(ch) || ch == ' ') { 
            input += ch;
            cout << ch;
        }
    }

    return input;
}

// Ham chi cho nhap y/Y hoac n/N
string OnlyYorN() {
    string choice;
    while (true) {
        cin >> choice;
        if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") {
            return choice;
        } else {
            cout << "Lua chon khong hop le! Vui long nhap lai (y/Y or n/N): ";
        }
    }
}

// Ham trim() loai bo khoang trong dau va cuoi chuoi
string trim(const string& str) {
    // Xoa khoang trong dau chuoi
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos) {
        return ""; 
}

    // Xoa khoang trong cuoi chuoi
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    return str.substr(start, end - start + 1); 
}

// Ham lay ngay hien tai 
string getCurrentDate() {
    auto now = chrono::system_clock::now();             // Lay thoi gian he thong
    time_t now_time = chrono::system_clock::to_time_t(now); 
    struct tm* now_tm = localtime(&now_time);           // Chuyen doi sang dung struct tm 

    stringstream dateStream;
    dateStream << setw(2) << setfill('0') << (now_tm ->tm_mday) << "-" 		  // Ngay
               << setw(2) << setfill('0') << (now_tm->tm_mon + 1) << "-"      // Thang
               << setw(4) << setfill('0') << (now_tm->tm_year + 1900);        // Thang
    return dateStream.str();
}

// Ham lay thoi gian hien tai 
string getCurrentTime() {
    auto now = chrono::system_clock::now();             // Lay thoi gian he thong
    time_t now_time = chrono::system_clock::to_time_t(now); 
    struct tm* now_tm = localtime(&now_time);           // Chuyen doi sang dung struct tm

    stringstream timeStream;
    timeStream << setw(2) << setfill('0') << now_tm->tm_hour << ":"          // Gio
               << setw(2) << setfill('0') << now_tm->tm_min << ":"           // Phut
               << setw(2) << setfill('0') << now_tm->tm_sec;                 // Giay
    return timeStream.str();
}
