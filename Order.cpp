#include "Order.h"
#include "MenuItem.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Order::addItem(const MenuItem& item, int quantity) {
    MenuItem newItem = item; 
    newItem.setQuantity(quantity); 
    items.push_back(newItem);  
}

void Order::clearOrder() {
    items.clear();
    quantities.clear();
}

void Order::displayOrder() {
	cout << "=== Chi tiet don hang ===" << endl;
	cout << left << setw(25) << "Mon" << setw(10) << "So luong" << setw(15) << "Don gia" << "Tong" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (const auto& item : items) {
        long long total = item.getPrice() * item.getQuantity(); 
        cout << left << setw(25) << item.getName()
             << setw(10) << item.getQuantity()
             << setw(15) << item.getPrice()
             << total << " VND\n"; 
    }
    cout << "Tong tien: " << getTotal() << " VND\n";
}

void Order::printInvoice() const {
    if (items.empty()) {
        cout << "Hoa don trong!\n"; 
        return;
    }

    string currentDate = getCurrentDate();
    string currentTime = getCurrentTime();
    
    cout << "=============================================================\n";
    cout << "                         HOA DON\n";
    cout << "=============================================================\n";
    cout << "Ngay: " << currentDate << endl;
    cout << "Thoi gian: " << currentTime << endl;
    cout << left << setw(25) << "Mon" << setw(10) << "So luong" << setw(15) << "Don gia" << "Tong" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (const auto& item : items) {
    	long long total = item.getPrice() * item.getQuantity();
        cout << left << setw(25) << item.getName()
             << setw(10) << item.getQuantity()
             << setw(15) << item.getPrice()
             << total << " VND\n";
    }

    cout << "-------------------------------------------------------------\n";
    cout << left << setw(25) << "Tong cong" << setw(25) << " " << getTotal() << " VND\n";
    cout << "=============================================================\n";
}

long long Order::getTotal() const {
    long long total = 0;
    for (const auto& item : items) {
        total += item.getPrice() * item.getQuantity(); 
    }
    return total;
}

void Order::printInvoiceToFile(const string& filename) const {
    ofstream outFile(filename, ios::app); 

    if (!outFile) {
        cerr << "Khong the mo file ghi!" << endl;
        return;
    }

    string currentDate = getCurrentDate();
    string currentTime = getCurrentTime();

    outFile << "=============================================================\n";
    outFile << "                         HOA DON\n";
    outFile << "=============================================================\n";
    outFile << "Ngay: " << currentDate << "\n";
    outFile << "Thoi gian: " << currentTime << "\n";
    outFile << left << setw(25) << "Mon" << setw(10) << "So luong" << setw(15) << "Don gia" << "Tong" << endl;
    outFile << "-------------------------------------------------------------" << endl;

    for (const auto& item : items) {
    	long long total = item.getPrice() * item.getQuantity();
        outFile << left << setw(25) << item.getName()
                << setw(10) << item.getQuantity()
                << setw(15) << item.getPrice()
                << total << " VND\n";
    }

    outFile << "-------------------------------------------------------------\n";
    outFile << left << setw(25) << "Tong cong" << setw(25) << " " << getTotal() << " VND\n";
    outFile << "=============================================================\n\n";

    outFile.close();
}

void Order::addMenuItemToOrder(const vector<Category>& categories) {
	system("cls");
    string itemName;
    int quantity;
    
    cout << "=== MENU ===\n";
    for (const auto& category : categories) {
        cout << ">>> " << category.getCategoryName() << " <<<\n";
        category.displayMenu();
    }
	
    cout << "Nhap ten mon can them: ";
    itemName = OnlyAlphabet();

    cout << "Nhap so luong: ";
	string quantityStr = OnlyNumber();
	quantity = stoi(quantityStr);

    bool itemFound = false;
    for (const auto& category : categories) {
        const vector<MenuItem>& menuItems = category.getMenuItems();
        for (const auto& menuItem : menuItems) {
            if (menuItem.getName() == itemName) {
                addItem(menuItem, quantity);  
                cout << "Da them " << quantity << " x " << itemName << " vao don hang.\n";
                itemFound = true;
                break;
            }
        }
        if (itemFound) break;
    }
    if (!itemFound) {
        cout << "Mon '" << itemName << "' khong co trong menu.\n";
    }
}

void Order::removeItem() {
    system("cls");
    displayOrder();

    cout << "Nhap ten mon can xoa: ";
    string itemName = OnlyAlphabet();

    bool itemFound = false;
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].getName() == itemName) {
            items.erase(items.begin() + i);
            cout << "Mon '" << itemName << "' da duoc xoa khoi don hang.\n";
            itemFound = true;
            break;
        }
    }

    if (!itemFound) {
        cout << "Mon '" << itemName << "' khong co trong don hang.\n";
    }

    if (items.empty()) {
        cout << "Don hang hien tai rong.\n";
    }
}

void Order::updateItemQuantity() {
    system("cls");
    displayOrder();

    cout << "Nhap ten mon can thay doi so luong: ";
    string itemName = OnlyAlphabet();

    cout << "Nhap so luong moi: ";
    string newQuantityStr = OnlyNumber();
    int newQuantity = stoi(newQuantityStr);

    bool itemFound = false;
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].getName() == itemName) {
            items[i].setQuantity(newQuantity);
            cout << "So luong mon '" << itemName << "' da duoc cap nhat thanh " << newQuantity << ".\n";
            itemFound = true;
            break;
        }
    }

    if (!itemFound) {
        cout << "Mon '" << itemName << "' khong co trong don hang.\n";
    }
}

void Order::finalizeOrder(const vector<Category>& categories) {
    system("cls");
    cout << "========== CHOT DON HANG ==========\n";
    displayOrder();
    cout << "Ban co muon chot don hang khong? (Y/N): ";
    string confirm = OnlyYorN();
    if (tolower(confirm[0]) == 'y') {
        cout << "Ban da mua hang thanh cong!\n";
        printInvoice();
        printInvoiceToFile("invoice.txt");
        cout << "Cam on quy khach!\n";
        clearOrder();
    } else {
        cout << "Don hang chua duoc chot. Ban co the tiep tuc chinh sua don hang.\n";
        modifyOrderItems(categories);
    }
}

void Order::modifyOrderItems(const vector<Category>& categories) {
    int choice;
    do {
        cout << "\n========== CHINH SUA DON HANG ==========\n";
        cout << "1. Them mon moi\n";
        cout << "2. Xoa mon khoi don hang\n";
        cout << "3. Thay doi so luong mon\n";
        cout << "4. Chot don hang\n";
        cout << "5. Quay lai\n";
        cout << "=========================================\n";
        cout << "Nhap lua chon: ";
        string choiceStr = OnlyNumber();  
        choice = stoi(choiceStr);

        switch (choice) {
            case 1: {
                addMenuItemToOrder(categories);  
                break;
            }
            case 2: { 
                removeItem();  
                break;
            }
            case 3: {  
                updateItemQuantity();  
                break;
            }
            case 4: {
            	finalizeOrder(categories);
            	break;
            	}
            case 5: { 
                cout << "Quay lai menu chinh.\n";
                break;
            }
            default:
                cout << "Lua chon khong hop le! Vui long thu lai.\n";
                break;
        }
    } while (choice != 4); 
}

void Order::placeOrder(vector<Category>& categories, Order& order) {
    int categoryChoice, itemChoice, quantity;
    char continueOrder, closeOrder, modifyOrder;
	string confirm;
	
    do {
        cout << "MENU: \n";
        for (size_t i = 0; i < categories.size(); i++) {
            cout << i + 1 << ". " << categories[i].getCategoryName() << endl;
        }

        cout << "Nhap so de chon mon: ";
        string categoryChoiceStr = OnlyNumber();  
        categoryChoice = stoi(categoryChoiceStr);

        if (categoryChoice < 1 || categoryChoice > categories.size()) {
            cout << "Lua chon khong hop le!" << endl;
            continue; 
        }

        const Category& selectedCategory = categories[categoryChoice - 1];
        const vector<MenuItem>& menuItems = selectedCategory.getMenuItems();

        for (size_t i = 0; i < menuItems.size(); ++i) {
            cout << i + 1 << ". " << menuItems[i].getName() 
                 << " - " << menuItems[i].getPrice() << " VND\n";
        }

        cout << "Ban muon order gi? (nhap so tuong ung): ";
        string itemChoiceStr = OnlyNumber(); 
        itemChoice = stoi(itemChoiceStr);

        if (itemChoice < 1 || itemChoice > menuItems.size()) {
            cout << "Lua chon mon khong hop le!" << endl;
            continue;  
        }

        cout << "Nhap so luong: ";
        string quantityStr = OnlyNumber();  
        quantity = stoi(quantityStr);

        if (quantity <= 0) {
            cout << "So luong khong hop le!" << endl;
            continue; 
        }

        order.addItem(menuItems[itemChoice - 1], quantity);
        cout << "Da them " << quantity << " x " 
             << menuItems[itemChoice - 1].getName() << " vao don hang.\n";
        
        cout << "Ban co muon dat them mon? (Y/N): ";
    	string confirm = OnlyYorN();
        system("cls");
        
    } while (tolower(confirm[0]) == 'y');  

    order.displayOrder();  
    cout << "Ban co muon chot don hang khong? (Y/N): ";
    string confirmCloseOrder = OnlyYorN();
    system("cls");

    if (tolower(confirmCloseOrder[0]) == 'y') {
        cout << "Ban da mua hang thanh cong!" << endl;
        order.printInvoice();
        order.printInvoiceToFile("invoice.txt");
        cout << "Cam on quy khach!" << endl;
        cin.ignore();
        cin.get();
        system("cls");
        return; 
    } else {
        cout << "Ban co muon:\n";
        cout << "1. Dat lai mon tu dau\n";
        cout << "2. Thay doi mon da dat\n";
        cout << "Nhap lua chon: ";
        string modifyChoiceStr = OnlyNumber(); 
        int modifyChoice = stoi(modifyChoiceStr);

       switch (modifyChoice) {
            case 1: {
                order.clearOrder(); 
                cout << "Ban da xoa het mon trong don hang. Chon mon lai tu dau.\n";
                placeOrder(categories, order);  
                break;
            }
            case 2: {
                order.modifyOrderItems(categories); 
                break;
            }
            default:
                cout << "Lua chon khong hop le! Quay lai menu chinh.\n";
                break;
        }
    }
}
