#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::string filename = "Sign.txt"; // �������� �� ��� ������ �����

    // ��������� ����
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ���� " << filename << std::endl;
        return 1;
    }

    std::string longestWord;
    std::string* words = new std::string[1000]; // ������ ��� �������� ����
    int* wordCount = new int[1000]; // ������ ��� �������� ���������� ���������
    int wordIndex = 0; // ������ ��� ������� ����
    int longestWordIndex = 0; // ������ ��� ������ �������� �����

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string word;
        while (iss >> word) {
            // ������� ����� ���������� � ������� �����
            std::string cleanedWord;
            for (char c : word) {
                if (isalpha(c) || isdigit(c)) {
                    cleanedWord += c;
                }
            }

            // ���� ��������� ����� �� ������, ��������� ����� ������� �����
            if (!cleanedWord.empty()) {
                if (cleanedWord.length() > longestWord.length()) {
                    longestWord = cleanedWord;
                    longestWordIndex = wordIndex;
                }

                // ����������� ������� ��� �����
                bool found = false;
                for (int i = 0; i < wordIndex; i++) {
                    if (words[i] == cleanedWord) {
                        wordCount[i]++;
                        found = true;
                        break;
                    }
                }

                // ���� ����� �� ���� �������, ��������� ��� � �������
                if (!found) {
                    words[wordIndex] = cleanedWord;
                    wordCount[wordIndex] = 1;
                    wordIndex++;
                }
            }
        }
    }

    // ������� ����������
    std::cout << "����� ������� �����: " << longestWord << std::endl;
    std::cout << "���������� ���������: " << wordCount[longestWordIndex] << std::endl;

    // ��������� ����
    file.close();

    // ����������� ������
    delete[] words;
    delete[] wordCount;

    return 0;
}
