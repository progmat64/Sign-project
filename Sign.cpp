#include "Sign.h"
#include <string>

using namespace std;

Sign::Sign() {
    cout << "������ ����������� Sign" << endl;
}
Sign::Sign(string sFirstName, string sSecondName, string sSign, int* sBirthday) :
    firstName(sFirstName),
    secondName(sSecondName),
    sign{ sSign } {
    this->birthday[0] = sBirthday[0];
    this->birthday[1] = sBirthday[1];
    this->birthday[2] = sBirthday[2];
    cout << "������ ����������� Sign" << endl;
}
Sign::Sign(const Sign& sCopy) : firstName(sCopy.firstName), secondName(sCopy.secondName), sign{ sCopy.sign } {
    this->birthday[0] = sCopy.birthday[0];
    this->birthday[1] = sCopy.birthday[1];
    this->birthday[2] = sCopy.birthday[2];
    cout << "������ ����������� Sign" << endl;
}
Sign::~Sign() {
    cout << "������ ���������� Sign" << endl;
}

string Sign::getName() const { return firstName + " " + secondName; }
string Sign::getSurname() const { return secondName; }
string Sign::getBirthday() const { return to_string(birthday[0]) + "." + to_string(birthday[1]) + "." + to_string(birthday[2]); }
int Sign::getBirthdayInt() { return birthday[0] + birthday[1] * 31 + birthday[2] * 365; }
string Sign::getSign() const { return sign; }


void Sign::setName(const string& sFirstName, const string& sSecondName) {
    this->firstName = sFirstName;
    this->secondName = sSecondName;
}

void Sign::setSign(const string& sSign) {
    this->sign = sSign;
}

void Sign::setBirthday(const int sBirthday[3]) {
    this->birthday[0] = sBirthday[0];
    this->birthday[1] = sBirthday[1];
    this->birthday[2] = sBirthday[2];
}

ostream& operator<<(ostream& out, const Sign& s) {
    out << s.firstName << " " << s.secondName << " " << s.sign << " " << s.birthday[0] << " " << s.birthday[1] << " " << s.birthday[2];
    return out;
}
istream& operator>>(istream& in, Sign& s) {
    in >> s.firstName >> s.secondName >> s.sign >> s.birthday[0] >> s.birthday[1] >> s.birthday[2];
    return in;
}

void Sign::printInfo() {
    cout << getName() << " - " << getSign() << " - " << getBirthday() << endl;
}
void Sign::edit() {
    if (firstName.empty() || secondName.empty())
        cout << "������� ��� (��� �������): ";
    else
        cout << "������� ��� (��� �������; ������� - " << getName() << "): ";
    cin >> firstName >> secondName;
    if (sign.empty())
        cout << "������� ����: ";
    else
        cout << "������� ���� (������� - " << getSign() << "): ";
    cin >> sign;
    if (birthday[0] == 0 && birthday[1] == 0 && birthday[2] == 0)
        cout << "������� ���� �������� (�� �� ��): ";
    else
        cout << "������� ���� �������� (�� �� ��; ������� - " << getBirthday() << "): ";
    cin >> birthday[0] >> birthday[1] >> birthday[2];
    cout << "" << endl;
    printInfo();
}
void Sign::save() {
    ofstream file;
    string file_name = "Sign.txt";
    file.open(file_name, ios::app);
    if (!file) {
        cout << "������ ��� �������� ����� " << file_name << " ��� �������� ������";
        return;
    }
    file << firstName << " " << secondName << endl << sign << endl << birthday[0] << " " << birthday[1] << " " << birthday[2] << endl;
    file.close();
}
