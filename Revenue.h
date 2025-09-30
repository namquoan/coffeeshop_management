#ifndef REVENUE_H
#define REVENUE_H

#include <string>

using namespace std;

class Revenue {
public:
    static long long calculateRevenueFromFile(const string& filename);
    
    static long long calculateRevenueByDay(const string& filename, const string& date);
    
    static long long calculateRevenueByMonth(const string& filename, const string& month);
    
    static long long calculateRevenueByYear(const string& filename, const string& year);
    
    static void revenueMenu(const string& filename);
};

#endif // REVENUE_H

