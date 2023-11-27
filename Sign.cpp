#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::string filename = "Sign.txt"; // Замените на имя вашего файла

    // Открываем файл
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return 1;
    }

    std::string longestWord;
    std::string* words = new std::string[1000]; // массив для хранения слов
    int* wordCount = new int[1000]; // массив для хранения количества вхождений
    int wordIndex = 0; // индекс для массива слов
    int longestWordIndex = 0; // индекс для самого длинного слова

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string word;
        while (iss >> word) {
            // Убираем знаки препинания с каждого слова
            std::string cleanedWord;
            for (char c : word) {
                if (isalpha(c) || isdigit(c)) {
                    cleanedWord += c;
                }
            }

            // Если очищенное слово не пустое, обновляем самое длинное слово
            if (!cleanedWord.empty()) {
                if (cleanedWord.length() > longestWord.length()) {
                    longestWord = cleanedWord;
                    longestWordIndex = wordIndex;
                }

                // Увеличиваем счетчик для слова
                bool found = false;
                for (int i = 0; i < wordIndex; i++) {
                    if (words[i] == cleanedWord) {
                        wordCount[i]++;
                        found = true;
                        break;
                    }
                }

                // Если слово не было найдено, добавляем его в массивы
                if (!found) {
                    words[wordIndex] = cleanedWord;
                    wordCount[wordIndex] = 1;
                    wordIndex++;
                }
            }
        }
    }

    // Выводим результаты
    std::cout << "Самое длинное слово: " << longestWord << std::endl;
    std::cout << "Количество вхождений: " << wordCount[longestWordIndex] << std::endl;

    // Закрываем файл
    file.close();

    // Освобождаем память
    delete[] words;
    delete[] wordCount;

    return 0;
}
