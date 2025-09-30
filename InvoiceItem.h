#ifndef INVOICEITEM_H
#define INVOICEITEM_H

#include <string>

using namespace std;

class InvoiceItem {
private:
    string name;  		
    int quantity;     
    long long price;      

public:
    InvoiceItem(const string& name, int quantity, long long price);

    string getName() const;
    int getQuantity() const;
    long long getPrice() const;

    long long getTotal() const;
    
    void setQuantity(int quantity);
};

#endif // INVOICEITEM_H

