#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include "MenuItem.h"

using namespace std;

class Order {
    vector<MenuItem> items; 
    vector<int> quantities;

public:
	
    void addItem(const MenuItem& item, int quantity);
    
    int getItemCount() const;
    
    void removeItem();
    
    void addMenuItemToOrder(const vector<Category>& categories);
    
    void updateItemQuantity();
    
    void clearOrder();
    
    void modifyOrderItems(const vector<Category>& categories);
    
    long long getTotal() const;
    
    void displayOrder();
    
    const vector<MenuItem>& getItems() const;
    
    void printInvoice() const;

    void printInvoiceToFile(const string& filename) const;
    
    void finalizeOrder(const vector<Category>& categories);
    
    static void displayInvoices(const string& filename);

	static void placeOrder(vector<Category>& categories, Order& order);

};


#endif // ORDER_H
