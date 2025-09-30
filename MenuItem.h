#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Dinh nghia lop MenuItem
class MenuItem {
private:
    string name;  
    long long price;
    int quantity;

public:
    MenuItem(const string& name, long long price);

    string getName() const;

    long long getPrice() const;
    
    int getQuantity() const { return quantity; }

 	void setQuantity(int qty) { quantity = qty; }

    void setPrice(long long newPrice) { price = newPrice; }
    
    static void showMenu(const vector<class Category>& categories);

};

class Category {
private:
    string categoryName;            
    vector<MenuItem> menuItems;     

public:
    Category(const string& name);

    string getCategoryName() const;

    const vector<MenuItem>& getMenuItems() const;

    void addMenuItem(const MenuItem& item);

    void removeItem(const string& itemName);

    void updatePrice(const string& itemName, long long newPrice);

    void displayMenu() const;

    static void loadMenuFromFile(const string& filename, vector<Category>& categories);

    static void saveMenuToFile(const string& filename, const vector<Category>& categories);
};

#endif // MENUITEM_H
