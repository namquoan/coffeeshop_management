#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Account.h"
#include "InvoiceItem.h"
#include "MenuItem.h"
#include "Utilities.h"
#include "Order.h"
#include "AdActions.h"
#include "Invoice.h"
#include "Revenue.h"

using namespace std;

// Hien thi menu chinh
void showMainMenu() {
    cout << "===================================" << endl;
    cout << "   XIN CHAO MUNG DEN VOI QP CAFE" << endl;
    cout << "===================================" << endl;
    cout << "1. Dang nhap" << endl;
    cout << "2. Dang ky" << endl;
    cout << "3. Thoat" << endl;
    cout << "===================================" << endl;
    cout << "Nhap lua chon: ";
}

// Ham chinh
int main() {
    vector<Account*> accounts;
    vector<Category> categories;
    Order currentOrder;

    string accountFile = "account.txt";
    string menuFile = "menu.txt";
    string invoiceFile = "invoice.txt";

    // Load tai khoan va menu vao file
    Account::loadAccountsFromFile(accountFile, accounts);
    Category::loadMenuFromFile(menuFile, categories);

    Account* loggedInAccount = nullptr;
    int choice;

    while (true) {
        if (!loggedInAccount) {
            showMainMenu(); 
            string choiceStr = OnlyNumber();
			int choice = stoi(choiceStr); 

            switch (choice) {
                case 1: {
                    system("cls");
                    loggedInAccount = Account::login(accounts);
                    break;
                }
                case 2: { 
                    system("cls");
                    User::registerUser(accounts, accountFile);
                    break;
                }
                case 3: { 
                    system("cls");
                    cout << "Cam on da su dung dich vu. Hen gap lai!" << endl;
                    return 0;
                }
                default:
                    cout << "Lua chon khong hop le. Vui long thu lai!" << endl;
            }
        } else if (loggedInAccount->getRole() == "admin") {
            // Menu danh cho admin
			loggedInAccount->displayMenu();
            string choiceStr = OnlyNumber(); 
			int choice = stoi(choiceStr);

            switch (choice) {
                case 1: { // Thay doi menu
                    system("cls");
                    cout << "Thay doi menu" << endl;
                    adminMenuActions(categories);  
                    break;
                }
                case 2: { // Hien thi hoa don
                    system("cls");
                    Invoice::displayInvoicesMenu();
                    break;
                }
                case 3: { // Tinh doanh thu
                    system("cls");
                    Revenue::revenueMenu(invoiceFile);
                    break;
                }
                case 4: { // Dang xuat
                    system("cls");
                    loggedInAccount = nullptr;
                    cout << "Dang xuat thanh cong!" << endl;
                    break;
                }
                default:
                    cout << "Lua chon khong hop le. Vui long thu lai!" << endl;
            }
        } else if (loggedInAccount->getRole() == "user") {
            // Menu danh cho user
			loggedInAccount->displayMenu();
            string choiceStr = OnlyNumber(); 
			int choice = stoi(choiceStr); 

            switch (choice) {
            	case 1: {
            		system("cls");
            		cout << "Xem thong tin nguoi dung" << endl;
            		loggedInAccount->displayUserInfo();
            		break;
            	}
                case 2: { // Xem danh sach mon an
                    system("cls");
                    cout << "Danh sach mon an" << endl;
                    MenuItem::showMenu(categories);
                    break;
                }
                case 3: { // Dat mon
                    system("cls");
                    Order::placeOrder(categories, currentOrder);
                    break;
                }
                case 4: { // Dang xuat
                    system("cls");
                    loggedInAccount = nullptr;
                    cout << "Dang xuat thanh cong!" << endl;
                    break;
                }
                default:
                    cout << "Lua chon khong hop le. Vui long thu lai!" << endl;
            }
        } else {
            cout << "Loi: Vai tro khong hop le!" << endl;
            loggedInAccount = nullptr;
        }
    }

    // Giai phong bo nho
    for (auto account : accounts) {
        delete account;
    }

    return 0;
}
