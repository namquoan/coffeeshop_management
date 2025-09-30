#include "Account.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>

using namespace std;

// Lop Account
Account::Account(const string& username, const string& password)
    : username(username), password(password) {}

string Account::getUsername() const {
    return username;
}

string Account::getPassword() const {
    return password;
}

bool Account::login(const string& username, const string& password) const {
    return this->username == username && this->password == password;
}

Account* Account::login(const vector<Account*>& accounts) {
    string username, password;
    cout << "Nhap ten dang nhap: ";
    cin >> username;

    cout << "Nhap mat khau: ";
    password = ""; 

    char ch;
    while (true) {
        ch = _getch(); 
        if (ch == 13) { 
            break;
        } else if (ch == 8) { 
            if (!password.empty()) {
                password.pop_back(); 
                cout << "\b \b"; 
            }
        } else {
            password += ch; 
            cout << '*'; 
        }
    }
    cout << endl;

    for (auto& account : accounts) {
        if (account->login(username, password)) {
        		system("cls");
   			if (account->getRole() == "admin") {
                cout << "Dang nhap thanh cong!\n";
                cout << "Xin chao, " << account->getUsername() << "!\n";  // Admin
            } else if (account->getRole() == "user") {
                User* user = dynamic_cast<User*>(account);
                system("cls");
				  // Ep kieu sang User
                if (user) {
                    cout << "Dang nhap thanh cong!\n";
                    cout << "Xin chao, " << user->getFullName() << "!\n";  // User
                }
            }
            return account;
        }
    }

    cout << "Dang nhap that bai. Vui long thu lai.\n";
    return nullptr;
}

void Account::loadAccountsFromFile(const string& fileName, vector<Account*>& accounts) {
    ifstream inFile(fileName);
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string username, password, role, fullName, phoneNumber, address;

            ss >> username >> password >> role;
            getline(ss, fullName, ';');  
            getline(ss, phoneNumber, ';');  
            getline(ss, address); 

            if (role == "admin") {
                accounts.push_back(new Admin(username, password));
            } else if (role == "user") {
                accounts.push_back(new User(username, password, fullName, phoneNumber, address));
            }
        }
        inFile.close();
    } else {
        cout << "Khong the mo file tai khoan.\n";
    }
}

void Account::saveAccountsToFile(const string& fileName, const vector<Account*>& accounts) {
    ofstream outFile(fileName);

    if (outFile.is_open()) {
        for (const auto& account : accounts) {
            if (account->getRole() == "admin") {
                outFile << account->getUsername() << " "
                        << account->getPassword() << " "
                        << account->getRole() << endl;
            } else if (account->getRole() == "user") {
                User* user = dynamic_cast<User*>(account);
                if (user) {
                    outFile << user->getUsername() << " "
                            << user->getPassword() << " "
                            << user->getRole() << " "
                            << user->getFullName() << ";"
                            << user->getPhoneNumber() << ";"
                            << user->getAddress() << endl;
                }
            }
        }
        outFile.close();
    } else {
        cout << "Khong the mo file tai khoan.\n";
    }
}

// Trien khai lop Admin
Admin::Admin(const string& username, const string& password)
    : Account(username, password) {}

string Admin::getRole() const {
    return "admin";
}

void Admin::displayMenu() const {
    cout << "===============================" << endl;
    cout << "        MENU QUAN LY" << endl;
    cout << "===============================" << endl;
    cout << "1. Thay doi Menu" << endl;
    cout << "2. Hien thi hoa don" << endl;
    cout << "3. Tinh doanh thu" << endl;
    cout << "4. Dang xuat" << endl;
    cout << "===============================" << endl;
    cout << "Nhap lua chon: ";
}

// Trien khai lop User
User::User(const string& username, const string& password, const string& fullName, const string& phoneNumber, const string& address)
    : Account(username, password), fullName(fullName), phoneNumber(phoneNumber), address(address) {}

string User::getFullName() const {
    return fullName;
}

void User::setFullName(const string& fullName) {
    this->fullName = fullName;
}

string User::getPhoneNumber() const {
    return phoneNumber;
}

void User::setPhoneNumber(const string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

string User::getAddress() const {
    return address;
}

void User::setAddress(const string& address) {
    this->address = address;
}

string User::getRole() const {
    return "user";
}

void User::displayMenu() const {
    cout << "==============================" << endl;
    cout << "        MENU KHACH HANG" << endl;
    cout << "==============================" << endl;
    cout << "1. Xem thong tin nguoi dung" << endl;
    cout << "2. Xem danh sach mon an" << endl;
    cout << "3. Dat mon" << endl;
    cout << "4. Dang xuat" << endl;
    cout << "===============================" << endl;
	cout << "Nhap lua chon: ";
}

void User::displayUserInfo() const {
    cout << "========== THONG TIN CA NHAN ==========\n";
    cout << "Ho ten: " << fullName << endl;
    cout << "Dia chi nhan hang: " << address << endl;
    cout << "So dien thoai: " << phoneNumber << endl;
    cout << "=======================================\n" << endl;
    system("pause");
    system("cls");
}

void User::registerUser(vector<Account*>& accounts, const string& fileName) {
    string username, password, fullName, phoneNumber, address;
    cout << "Nhap ten dang nhap moi: ";
    cin >> username;
    cout << "Nhap mat khau: ";
    cin >> password;
    cin.ignore();
    cout << "Nhap ho ten: ";
    getline(cin, fullName);
    cout << "Nhap so dien thoai: ";
    getline(cin, phoneNumber);
    cout << "Nhap dia chi nhan hang: ";
    getline(cin, address);

    accounts.push_back(new User(username, password, fullName, phoneNumber, address));
    Account::saveAccountsToFile(fileName, accounts);
    cout << "Dang ky thanh cong!\n";
}
