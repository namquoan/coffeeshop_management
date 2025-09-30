#include "InvoiceItem.h"

using namespace std;

InvoiceItem::InvoiceItem(const string& name, int quantity, long long price)
    : name(name), quantity(quantity), price(price) {}

string InvoiceItem::getName() const {
    return name;
}

int InvoiceItem::getQuantity() const {
    return quantity;
}

long long InvoiceItem::getPrice() const {
    return price;
}

long long InvoiceItem::getTotal() const {
    return quantity * price;
}

void InvoiceItem::setQuantity(int quantity) {
    this->quantity = quantity;
}


