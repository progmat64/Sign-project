#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class SIGN {
private:
    char* surname;
    char* name;
    char* zodiacSign;
    int* birthDate;

public:
    SIGN() {
        this->surname = new char[1];
        this->surname[0] = '\0';

        this->name = new char[1];
        this->name[0] = '\0';

        this->zodiacSign = new char[1];
        this->zodiacSign[0] = '\0';

        this->birthDate = new int[3];
        this->birthDate[0] = 0;
        this->birthDate[1] = 0;
        this->birthDate[2] = 0;
    }

    // �����������
    SIGN(const char* surname, const char* name, const char* zodiacSign, int day, int month, int year) {
        this->surname = new char[strlen(surname) + 1];
        strcpy(this->surname, surname);

        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);

        this->zodiacSign = new char[strlen(zodiacSign) + 1];
        strcpy(this->zodiacSign, zodiacSign);

        this->birthDate = new int[3];
        this->birthDate[0] = day;
        this->birthDate[1] = month;
        this->birthDate[2] = year;
    }

    // ����������
    ~SIGN() {
        delete[] surname;
        delete[] name;
        delete[] zodiacSign;
        delete[] birthDate;
    }

    // ������ �������
    char* getSurname() { return surname; }
    char* getName() { return name; }
    char* getZodiacSign() { return zodiacSign; }
    int* getBirthDate() { return birthDate; }

    void setSurname(const char* surname) {
        delete[] this->surname;
        this->surname = new char[strlen(surname) + 1];
        strcpy(this->surname, surname);
    }

    void setName(const char* name) {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void setZodiacSign(const char* zodiacSign) {
        delete[] this->zodiacSign;
        this->zodiacSign = new char[strlen(zodiacSign) + 1];
        strcpy(this->zodiacSign, zodiacSign);
    }

    void setBirthDate(int day, int month, int year) {
        this->birthDate[0] = day;
        this->birthDate[1] = month;
        this->birthDate[2] = year;
    }
};


#include <iostream>

int main() {
    setlocale(LC_ALL, "RUS");

    // ������� ������ ������ SIGN
    SIGN sign1("������", "����", "����", 1, 1, 1980);

    // ������� ���������� �� �������
    std::cout << "�������: " << sign1.getSurname() << std::endl;
    std::cout << "���: " << sign1.getName() << std::endl;
    std::cout << "���� �������: " << sign1.getZodiacSign() << std::endl;
    std::cout << "���� ��������: " << sign1.getBirthDate()[0] << "/" << sign1.getBirthDate()[1] << "/" << sign1.getBirthDate()[2] << std::endl;

    // �������� ��������
    sign1.setSurname("������");
    sign1.setName("����");
    sign1.setZodiacSign("�����");
    sign1.setBirthDate(2, 2, 1981);

    // ������� ����������� ���������� �� �������
    std::cout << "�������: " << sign1.getSurname() << std::endl;
    std::cout << "���: " << sign1.getName() << std::endl;
    std::cout << "���� �������: " << sign1.getZodiacSign() << std::endl;
    std::cout << "���� ��������: " << sign1.getBirthDate()[0] << "/" << sign1.getBirthDate()[1] << "/" << sign1.getBirthDate()[2] << std::endl;

    SIGN sign2;

    // ������������� ��������
    sign2.setSurname("������");
    sign2.setName("����");
    sign2.setZodiacSign("����");
    sign2.setBirthDate(1, 1, 1980);


    std::cout << "�������: " << sign2.getSurname() << std::endl;
    std::cout << "���: " << sign2.getName() << std::endl;
    std::cout << "���� �������: " << sign2.getZodiacSign() << std::endl;
    std::cout << "���� ��������: " << sign2.getBirthDate()[0] << "/" << sign1.getBirthDate()[1] << "/" << sign1.getBirthDate()[2] << std::endl;

    return 0;
}