#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Sign {
private:
    string firstName;
    string secondName;
    string sign;
    int birthday[3] = { 0 };

public:
    Sign();
    Sign(string sFirstName, string sSecondName, string sSign, int sBirthday[3]);
    Sign(const Sign& sCopy);
    ~Sign();

    string getName() const;
    string getSurname() const;
    string getSign() const;
    string getBirthday() const;
    int getBirthdayInt();

    void setName(const string& sFirstName, const string& sSecondName);
    void setSign(const string& sSign);
    void setBirthday(const int sBirthday[3]);

    // friend для доступа к приватным и защищенным членам класса Sign 
    friend ostream& operator<<(ostream& out, const Sign& s);
    friend istream& operator>>(istream& in, Sign& s);

    void printInfo();
    void edit();
    void save();
};
