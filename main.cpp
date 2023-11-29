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

// Функция task2 читает файл "text.txt", находит самое длинное слово и подсчитывает частоту встречаемости каждого уникального слова.
int task2() {
    // Указание имени файла
    string filename = "text.txt";
    // Создание объекта ifstream для чтения файла
    ifstream file(filename);

    // Проверка, успешно ли открыт файл
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return 1;
    }

    // Инициализация переменных
    string longestWord;        // Самое длинное слово
    string* words = new string[1000];    // Массив для хранения уникальных слов
    int* wordCount = new int[1000];      // Массив для хранения частоты встречаемости слов
    int wordIndex = 0;          // Индекс для отслеживания текущей позиции в массивах
    int longestWordIndex = 0;   // Индекс самого длинного слова в массиве

    // Чтение файла построчно
    string line;
    while (getline(file, line)) {
        istringstream iss(line);

        string word;
        // Разделение строки на слова
        while (iss >> word) {
            string cleanedWord;
            // Очистка слова от символов, отличных от букв и цифр
            for (char c : word) {
                if (isalpha(c) || isdigit(c)) {
                    cleanedWord += c;
                }
            }

            // Если слово не пустое после очистки
            if (!cleanedWord.empty()) {
                // Если текущее слово длиннее самого длинного, обновляем самое длинное слово
                if (cleanedWord.length() > longestWord.length()) {
                    longestWord = cleanedWord;
                    longestWordIndex = wordIndex;
                }

                // Проверка, встречается ли слово уже в массиве уникальных слов
                bool found = false;
                for (int i = 0; i < wordIndex; i++) {
                    if (words[i] == cleanedWord) {
                        // Если слово уже встречалось, увеличиваем счетчик
                        wordCount[i]++;
                        found = true;
                        break;
                    }
                }

                // Если слово не встречалось, добавляем его в массив
                if (!found) {
                    words[wordIndex] = cleanedWord;
                    wordCount[wordIndex] = 1;
                    wordIndex++;
                }
            }
        }
    }

    // Вывод самого длинного слова и его частоты встречаемости
    cout << "Самое длинное слово: " << longestWord << endl;
    cout << "Количество вхождений: " << wordCount[longestWordIndex] << endl;

    // Закрытие файла и освобождение памяти
    file.close();
    delete[] words;
    delete[] wordCount;

    // Возвращение 0, чтобы указать успешное завершение программы
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
