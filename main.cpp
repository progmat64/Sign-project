#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>
#include "Sign.h"
#include "Keeper.h"

using namespace std;

void menu() {
    cout << "1 - �������� ����" << endl;
    cout << "2 - �������� ������ ������" << endl;
    cout << "3 - ������������� ����" << endl;
    cout << "4 - ������� ����" << endl;
    cout << "5 - �������� ������ �� �������" << endl;
    cout << "6 - ��������� ������" << endl;
    cout << "7 - ��������� ������" << endl;
    cout << "0 - �����" << endl;
    cout << "��� �����: ";
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
            cout << "������ ������: " << keeper->getLen() << "" << endl;
            keeper->show();
            break;
        case 3:
            cout << "������� ������ ����� ��� ��������������: ";
            cin >> number;
            keeper->edit(number);
            break;
        case 4:
            cout << "������� ������ �����, ������� ����� �������: ";
            cin >> number;
            keeper->remove(number);
            break;
        case 5:
            cout << "������� �������, ����� �������� ������: ";
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
    cout << "�������� ���������.";
}

// ������� task2 ������ ���� "text.txt", ������� ����� ������� ����� � ������������ ������� ������������� ������� ����������� �����.
int task2() {
    // �������� ����� �����
    string filename = "text.txt";
    // �������� ������� ifstream ��� ������ �����
    ifstream file(filename);

    // ��������, ������� �� ������ ����
    if (!file.is_open()) {
        cerr << "�� ������� ������� ���� " << filename << endl;
        return 1;
    }

    // ������������� ����������
    string longestWord;        // ����� ������� �����
    string* words = new string[1000];    // ������ ��� �������� ���������� ����
    int* wordCount = new int[1000];      // ������ ��� �������� ������� ������������� ����
    int wordIndex = 0;          // ������ ��� ������������ ������� ������� � ��������
    int longestWordIndex = 0;   // ������ ������ �������� ����� � �������

    // ������ ����� ���������
    string line;
    while (getline(file, line)) {
        istringstream iss(line);

        string word;
        // ���������� ������ �� �����
        while (iss >> word) {
            string cleanedWord;
            // ������� ����� �� ��������, �������� �� ���� � ����
            for (char c : word) {
                if (isalpha(c) || isdigit(c)) {
                    cleanedWord += c;
                }
            }

            // ���� ����� �� ������ ����� �������
            if (!cleanedWord.empty()) {
                // ���� ������� ����� ������� ������ ��������, ��������� ����� ������� �����
                if (cleanedWord.length() > longestWord.length()) {
                    longestWord = cleanedWord;
                    longestWordIndex = wordIndex;
                }

                // ��������, ����������� �� ����� ��� � ������� ���������� ����
                bool found = false;
                for (int i = 0; i < wordIndex; i++) {
                    if (words[i] == cleanedWord) {
                        // ���� ����� ��� �����������, ����������� �������
                        wordCount[i]++;
                        found = true;
                        break;
                    }
                }

                // ���� ����� �� �����������, ��������� ��� � ������
                if (!found) {
                    words[wordIndex] = cleanedWord;
                    wordCount[wordIndex] = 1;
                    wordIndex++;
                }
            }
        }
    }

    // ����� ������ �������� ����� � ��� ������� �������������
    cout << "����� ������� �����: " << longestWord << endl;
    cout << "���������� ���������: " << wordCount[longestWordIndex] << endl;

    // �������� ����� � ������������ ������
    file.close();
    delete[] words;
    delete[] wordCount;

    // ����������� 0, ����� ������� �������� ���������� ���������
    return 0;
}


int main() {
    setlocale(LC_ALL, "Rus");
    int task;
    cout << "�������� ������ (1 ��� 2): ";
    cin >> task;
    if (task == 1) {
        task1();
    }
    else {
        task2();
    }
    return 0;
}
