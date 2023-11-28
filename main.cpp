#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void menuf() {
    cout << "1. Добавить знак" << endl <<
        "2. Показать список знаков" << endl <<
        "3. Удалить знак" << endl <<
        "4. Редактировать знак" << endl <<
        "5. Получить данные по знаку" << endl <<
        "6. Сохранить данные" << endl <<
        "7. Загрузить данные" << endl <<
        "0. Выход" << endl <<
        "Выберите пункт меню: ";
}


void task1() {}

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
    cout << "chouse task (1/2): ";
    cin >> task;
    if (task == 1) {
        task1();
    }
    else {
        task2();
    }
    return 0;
}
