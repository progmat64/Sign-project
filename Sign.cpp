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

    // Конструктор
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

    // Деструктор
    ~SIGN() {
        delete[] surname;
        delete[] name;
        delete[] zodiacSign;
        delete[] birthDate;
    }

    // Методы доступа
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

    // Создаем объект класса SIGN
    SIGN sign1("Иванов", "Иван", "Овен", 1, 1, 1980);

    // Выводим информацию об объекте
    std::cout << "Фамилия: " << sign1.getSurname() << std::endl;
    std::cout << "Имя: " << sign1.getName() << std::endl;
    std::cout << "Знак зодиака: " << sign1.getZodiacSign() << std::endl;
    std::cout << "Дата рождения: " << sign1.getBirthDate()[0] << "/" << sign1.getBirthDate()[1] << "/" << sign1.getBirthDate()[2] << std::endl;

    // Изменяем значение
    sign1.setSurname("Петров");
    sign1.setName("Петр");
    sign1.setZodiacSign("Телец");
    sign1.setBirthDate(2, 2, 1981);

    // Выводим обновленную информацию об объекте
    std::cout << "Фамилия: " << sign1.getSurname() << std::endl;
    std::cout << "Имя: " << sign1.getName() << std::endl;
    std::cout << "Знак зодиака: " << sign1.getZodiacSign() << std::endl;
    std::cout << "Дата рождения: " << sign1.getBirthDate()[0] << "/" << sign1.getBirthDate()[1] << "/" << sign1.getBirthDate()[2] << std::endl;

    SIGN sign2;

    // Устанавливаем значения
    sign2.setSurname("Иванов");
    sign2.setName("Иван");
    sign2.setZodiacSign("Овен");
    sign2.setBirthDate(1, 1, 1980);


    std::cout << "Фамилия: " << sign2.getSurname() << std::endl;
    std::cout << "Имя: " << sign2.getName() << std::endl;
    std::cout << "Знак зодиака: " << sign2.getZodiacSign() << std::endl;
    std::cout << "Дата рождения: " << sign2.getBirthDate()[0] << "/" << sign1.getBirthDate()[1] << "/" << sign1.getBirthDate()[2] << std::endl;

    return 0;
}