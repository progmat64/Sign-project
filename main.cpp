#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>
#include "Sign.h"
#include "Keeper.h"

using namespace std;

void menu() {
    cout << "1 - Добавить знак" << endl;
    cout << "2 - Показать список знаков" << endl;
    cout << "3 - Редактировать знак" << endl;
    cout << "4 - Удалить знак" << endl;
    cout << "5 - Получить данные по фамилии" << endl;
    cout << "6 - Сохранить данные" << endl;
    cout << "7 - Загрузить данные" << endl;
    cout << "0 - Выход" << endl;
    cout << "Ваш выбор: ";
}

void task1() {
    Keeper* keeper;
    keeper = new Keeper;

    int chooise = 1;
    int number;
    string surname;
    while (chooise != 0) {
        menu();
        cin >> chooise;
        switch (chooise) {
        case 1:
            Sign * new_Sign;
            new_Sign = new Sign();
            new_Sign->edit();
            keeper->add(new_Sign);
            break;
        case 2:
            cout << "Список Знаков: " << keeper->getLen() << "" << endl;
            keeper->show();
            break;
        case 3:
            cout << "Введите индекс знака для редактирования: ";
            cin >> number;
            keeper->edit(number);
            break;
        case 4:
            cout << "Введите индекс знака, который нужно удалить: ";
            cin >> number;
            keeper->remove(number);
            break;
        case 5:
            cout << "Введите фамилию, чтобы получить данные: ";
            cin >> surname;
            keeper->getBySurname(surname);
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
    }
    keeper->~Keeper();
    cout << "Закрытие программы.";
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Функция для выполнения задачи по обработке текстового файла
int task2() {
    // Имя файла для чтения
    string filename = "text.txt";

    // Открытие файла
    ifstream file(filename);

    // Проверка успешного открытия файла
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return 1;
    }

    // Переменные для хранения самого длинного слова и его индекса
    string longestWord;
    int longestWordIndex = 0;

    // Динамически выделенные массивы для хранения уникальных слов и их частоты встречаемости
    string* words = new string[1000];
    int* wordCount = new int[1000];

    // Индекс текущего слова и строки
    int wordIndex = 0;

    // Чтение файла по строкам
    string line;
    while (getline(file, line)) {
        // Создание потока для разбора строки на слова
        istringstream iss(line);

        // Переменная для хранения очищенного слова от знаков препинания и других символов
        string cleanedWord;

        // Обработка каждого слова в строке
        while (iss >> cleanedWord) {
            // Очистка слова от знаков препинания и других символов
            for (char c : cleanedWord) {
                if (isalpha(c) || isdigit(c)) {
                    cleanedWord += c;
                }
            }

            // Если очищенное слово не пусто
            if (!cleanedWord.empty()) {
                // Если текущее слово длиннее самого длинного, обновляем данные о самом длинном слове
                if (cleanedWord.length() > longestWord.length()) {
                    longestWord = cleanedWord;
                    longestWordIndex = wordIndex;
                }

                // Проверка, есть ли слово в массиве уникальных слов
                bool found = false;
                for (int i = 0; i < wordIndex; i++) {
                    if (words[i] == cleanedWord) {
                        // Увеличение счетчика встречаемости слова
                        wordCount[i]++;
                        found = true;
                        break;
                    }
                }

                // Если слово не найдено в массиве, добавляем его и устанавливаем счетчик в 1
                if (!found) {
                    words[wordIndex] = cleanedWord;
                    wordCount[wordIndex] = 1;
                    wordIndex++;
                }
            }
        }
    }

    // Вывод результатов
    cout << "Самое длинное слово: " << longestWord << endl;
    cout << "Количество вхождений: " << wordCount[longestWordIndex] << endl;

    // Закрытие файла и освобождение памяти
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
