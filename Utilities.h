#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using namespace std;

// Khai bao ham trim
string trim(const string& str);

// Khai bao ham lay ngay hien tai
string getCurrentDate();

// Khai bao ham lay thoi gian hien tai 
string getCurrentTime();

// Ham chi cho phep nhap so
string OnlyNumber();

// Ham chi cho phep nhap chu
string OnlyAlphabet();

// Ham chi cho phep nhap y/Y hoac n/N
string OnlyYorN();

#endif // UTILITIES_H

