#ifndef INVOICE_H
#define INVOICE_H

#include <string>

using namespace std;

class Invoice {
public:
    static void displayInvoicesMenu();
    
    static void displayInvoicesByDay(const string& filename, const string& date);
    
    static void displayInvoicesByMonth(const string& filename, const string& month);
    
    static void displayInvoicesByYear(const string& filename, const string& year);
    
    static void displayAllInvoices(const string& filename);
};

#endif // INVOICE_H

