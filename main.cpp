#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>
#include "Sign.h"
#include "Keeper.h"
#include <conio.h>

using namespace std;

void menu() {
    cout << "1. Добавить знак" << endl <<
    "2. Показать список знаков" << endl <<
    "3. Удалить знак" << endl <<
    "4. Редактировать знак" << endl <<
    "5. Получить данные по фамилии" << endl <<
    "6. Сохранить данные" << endl <<
    "7. Загрузить данные" << endl <<
    "0. Выход" << endl <<
    "Выберите пункт меню: ";
}


void task1() {
    Keeper* keeper;
    keeper = new Keeper;

    int input_point = 1;
    int input_number;
    string input_string, passKey;
    while (input_point != 0) {
        menu();
        cin >> input_point;
        system("cls");
        switch (input_point) {
        case 1:
            Sign * new_Sign;
            new_Sign = new Sign();
            new_Sign->edit();
            keeper->add(new_Sign);
            break;
        case 2:
            cout << "Список Знаков: " << keeper->get_len() << "" << endl;
            keeper->show();
            break;
        case 3:
            cout << "Введите индекс знака, который нужно удалить: ";
            cin >> input_number;
            keeper->remove(input_number);
            break;
        case 4:
            cout << "Введите индекс знака для редактирования: ";
            cin >> input_number;
            keeper->edit(input_number);
            break;
        case 5:
            cout << "Введите фамилию, чтобы получить данные: ";
            cin >> input_string;
            keeper->getBySurname(input_string);
            break;
        case 6:
            keeper->save();
            break;
        case 7:
            keeper->load();
            break;
        default:
            break;
        }
        cout << "Нажмите любую клавишу для продолжения...";
        _getch();
        system("cls");
    }
    keeper->~Keeper();
    cout << "Закрытие программы пользователем.";
}

int task2() {
    string filename = "text.txt";

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return 1;
    }

    string longestWord;
    string* words = new string[1000];
    int* wordCount = new int[1000];
    int wordIndex = 0;
    int longestWordIndex = 0;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);

        string word;
        while (iss >> word) {
            string cleanedWord;
            for (char c : word) {
                if (isalpha(c) || isdigit(c)) {
                    cleanedWord += c;
                }
            }

            if (!cleanedWord.empty()) {
                if (cleanedWord.length() > longestWord.length()) {
                    longestWord = cleanedWord;
                    longestWordIndex = wordIndex;
                }

                bool found = false;
                for (int i = 0; i < wordIndex; i++) {
                    if (words[i] == cleanedWord) {
                        wordCount[i]++;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    words[wordIndex] = cleanedWord;
                    wordCount[wordIndex] = 1;
                    wordIndex++;
                }
            }
        }
    }

    cout << "Самое длинное слово: " << longestWord << endl;
    cout << "Количество вхождений: " << wordCount[longestWordIndex] << endl;

    file.close();

    delete[] words;
    delete[] wordCount;

    return 0;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int task;
    cout << "Выберите задачу (1 или 2): ";
    cin >> task;
    if (task == 1) {
        task1();
    }
    else {
        task2();
    }
    return 0;
}
