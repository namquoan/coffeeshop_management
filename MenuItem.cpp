#include "MenuItem.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

MenuItem::MenuItem(const string& name, long long price)  : name(name), price(price) {}

string MenuItem::getName() const {
    return name;
}

long long MenuItem::getPrice() const {
    return price;
}

Category::Category(const string& name) : categoryName(name) {}

string Category::getCategoryName() const {
    return categoryName;	
}

const vector<MenuItem>& Category::getMenuItems() const {
    return menuItems;
}

void Category::addMenuItem(const MenuItem& item) {
    menuItems.push_back(item);
}

void Category::removeItem(const string& itemName) {
    for (auto it = menuItems.begin(); it != menuItems.end(); ++it) {
        if (it->getName() == itemName) {
            menuItems.erase(it);
            cout << "Da xoa mon: " << itemName << endl;
            return;
        }
    }
    cout << "Khong tim thay mon: " << itemName << " trong danh sach.\n";
}

void Category::updatePrice(const string& itemName, long long newPrice) {
    for (auto& item : menuItems) {
        if (item.getName() == itemName) {
            item.setPrice(newPrice);
            cout << "Da cap nhat gia cho mon: " << itemName << " thanh " << newPrice << " VND.\n";
            return;
        }
    }
    cout << "Khong tim thay mon: " << itemName << " trong danh sach.\n";
}

void Category::displayMenu() const {
    cout << "=== " << categoryName << " ===\n";
    if (menuItems.empty()) {
        cout << "Khong co mon an nao trong nhom nay!" << endl;
        return;
    }

    for (size_t i = 0; i < menuItems.size(); ++i) {
        cout << i + 1 << ". " << menuItems[i].getName()
             << " - " << menuItems[i].getPrice() << " VND\n";
    }
}

void Category::loadMenuFromFile(const string& filename, vector<Category>& categories) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Khong the mo file menu.\n";
        return;
    }

    Category* currentCategory = nullptr;

    while (getline(file, line)) {
        // Loai bo khoang trong dau va cuoi dong
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) continue;

        // Neu dong khong chua so, do la ten nhom mon an
        if (line.find_first_of("0123456789") == string::npos) {
            // Tao nhom moi va luu vao danh sach
            categories.emplace_back(line);
            currentCategory = &categories.back();
        } else if (currentCategory != nullptr) {
            // Tach ten mon va gia
            size_t lastSpacePos = line.find_last_of(" ");
            if (lastSpacePos != string::npos) {
                string itemName = line.substr(0, lastSpacePos);
                long long price = stod(line.substr(lastSpacePos + 1));
                currentCategory->addMenuItem(MenuItem(itemName, price));
            }
        }
    }
    file.close();
}

void Category::saveMenuToFile(const string& filename, const vector<Category>& categories) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Khong the ghi vao file menu.\n";
        return;
    }

    for (const auto& category : categories) {
        file << category.getCategoryName() << "\n";
        for (const auto& item : category.getMenuItems()) {
            file << item.getName() << " " << fixed << setprecision(2) << item.getPrice() << "\n";
        }
        file << "\n";
    }

    file.close();
    cout << "Da luu thay doi vao file menu.\n";
}

void MenuItem::showMenu(const vector<Category>& categories) {
    cout << "Menu:\n";
    for (size_t i = 0; i < categories.size(); i++) {
        cout << i + 1 << ". " << categories[i].getCategoryName() << endl;
    }

    int categoryChoice;
    cout << "Nhap so tuong ung de xem cac mon an: ";
    
    string categoryChoiceStr = OnlyNumber();
    categoryChoice = stoi(categoryChoiceStr);
    
      if (categoryChoice < 1 || categoryChoice > categories.size()) {
      	system("cls");
        cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        return showMenu(categories);  
    }

    const Category& selectedCategory = categories[categoryChoice - 1];
    cout << "\nDanh sach '" << selectedCategory.getCategoryName() << "':\n";
    selectedCategory.displayMenu();
}
