#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void menuf() {
    cout << "1. �������� ����" << endl <<
        "2. �������� ������ ������" << endl <<
        "3. ������� ����" << endl <<
        "4. ������������� ����" << endl <<
        "5. �������� ������ �� �����" << endl <<
        "6. ��������� ������" << endl <<
        "7. ��������� ������" << endl <<
        "0. �����" << endl <<
        "�������� ����� ����: ";
}


void task1() {}

int task2() {
    string filename = "text.txt";

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "�� ������� ������� ���� " << filename << endl;
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

    cout << "����� ������� �����: " << longestWord << endl;
    cout << "���������� ���������: " << wordCount[longestWordIndex] << endl;

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
