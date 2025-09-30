#include "AdActions.h"
#include "Utilities.h"
#include "MenuItem.h"
#include <iostream>
#include <vector>

using namespace std;

void adminMenuActions(vector<Category>& categories) {
    int choice;

    do {
        cout << "========== QUAN LY MENU ==========\n";
        cout << "1. Them mon\n";
        cout << "2. Xoa mon\n";
        cout << "3. Cap nhat gia mon\n";
        cout << "4. Quay lai menu chinh\n";
        cout << "==================================\n";
        cout << "Nhap lua chon: ";
        string choiceStr = OnlyNumber();
        choice = stoi(choiceStr);

        switch (choice) {
            case 1:
                addMenuItem(categories); 
                break;
            case 2:
                removeMenuItem(categories); 
                break;
            case 3:
                updateMenuItemPrice(categories); 
                break;
            case 4:
                system("cls");
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 4);
}

void addMenuItem(std::vector<Category>& categories) {
    system("cls");
    int categoryChoice;
    cout << "MENU: \n";
    for (size_t i = 0; i < categories.size(); i++) {
        cout << i + 1 << ". " << categories[i].getCategoryName() << std::endl;
    }
    cout << "Nhap so de chon nhom mon: ";
    string categoryChoiceStr = OnlyNumber(); 
    categoryChoice = stoi(categoryChoiceStr);

    if (categoryChoice < 1 || categoryChoice > categories.size()) {
        cout << "Lua chon khong hop le!" << endl;
        return;
    }

    const Category& selectedCategory = categories[categoryChoice - 1];
    const vector<MenuItem>& menuItems = selectedCategory.getMenuItems();

    string itemName;
    long long price;
    cout << "Nhap ten mon an: ";
    itemName = OnlyAlphabet(); 

    cout << "Nhap gia mon an: ";
    string priceStr = OnlyNumber(); 
    price = stoll(priceStr);

    categories[categoryChoice - 1].addMenuItem(MenuItem(itemName, price));
    cout << "Da them mon '" << itemName << "' vao nhom '"
              << categories[categoryChoice - 1].getCategoryName() << "'.\n";
    Category::saveMenuToFile("menu.txt", categories);
}

void removeMenuItem(vector<Category>& categories) {
    system("cls");
    cout << "========== MENU ==========\n";
    for (size_t i = 0; i < categories.size(); ++i) {
        cout << i + 1 << ". " << categories[i].getCategoryName() << endl;
    }
    cout << "=====================================\n";
    cout << "Nhap so tuong ung: ";
    string groupChoiceStr = OnlyNumber(); 
    int groupChoice = stoi(groupChoiceStr);

    if (groupChoice < 1 || groupChoice > categories.size()) {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    const vector<MenuItem>& items = categories[groupChoice - 1].getMenuItems();
    cout << "========== MENU ==========\n";
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].getName() << " - "
                  << items[i].getPrice() << " VND\n";
    }
    cout << "===================================\n";
    cout << "Nhap so tuong ung voi mon an can xoa: ";
    string itemChoiceStr = OnlyNumber(); 
    int itemChoice = stoi(itemChoiceStr);

    if (itemChoice < 1 || itemChoice > items.size()) {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    string itemName = items[itemChoice - 1].getName();
    categories[groupChoice - 1].removeItem(itemName);
    cout << "Da xoa mon '" << itemName << "' khoi nhom '"
              << categories[groupChoice - 1].getCategoryName() << "'.\n";
    Category::saveMenuToFile("menu.txt", categories);
}

void updateMenuItemPrice(vector<Category>& categories) {
    system("cls");
    cout << "========== DANH SACH NHOM ==========\n";
    for (size_t i = 0; i < categories.size(); ++i) {
        cout << i + 1 << ". " << categories[i].getCategoryName() << endl;
    }
    cout << "=====================================\n";
    cout << "Nhap so tuong ung: ";
    string groupChoiceStr = OnlyNumber(); 
    int groupChoice = stoi(groupChoiceStr);

    if (groupChoice < 1 || groupChoice > categories.size()) {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    const vector<MenuItem>& items = categories[groupChoice - 1].getMenuItems();
    cout << "========== DANH SACH MON ==========\n";
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].getName() << " - "
                  << items[i].getPrice() << " VND\n";
    }
    cout << "===================================\n";
    cout << "Nhap so tuong ung voi mon an can cap nhat gia: ";
    string itemChoiceStr = OnlyNumber(); 
    int itemChoice = stoi(itemChoiceStr);

    if (itemChoice < 1 || itemChoice > items.size()) {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    long long newPrice;
    cout << "Nhap gia moi: ";
    string newPriceStr = OnlyNumber(); 
    newPrice = stoll(newPriceStr);

    string itemName = items[itemChoice - 1].getName();
    categories[groupChoice - 1].updatePrice(itemName, newPrice);
    cout << "Da cap nhat gia cua mon '" << itemName << "' thanh "
              << newPrice << " VND.\n";
    Category::saveMenuToFile("menu.txt", categories);
}

