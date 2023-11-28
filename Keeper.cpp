#include <iostream>
#include <fstream>
#include "Keeper.h"
#include <string>
#include <sstream>

using namespace std;

Keeper::Keeper() : len(0), head(nullptr) {}
Keeper::Keeper(int len) : head(nullptr) { this->len = len; }
Keeper::Keeper(const Keeper& keeper_copy) {
    this->head = keeper_copy.head;
    this->len = keeper_copy.len;
}
Keeper::~Keeper() {
    clear();
}
void Keeper::clear() {
    // ��������, ��� ������ �� ����
    if (head != nullptr) {
        Queue* obj_ptr;

        // ���� ������ ������ �� ������ ������
        while (head != nullptr) {
            obj_ptr = head; // ��������� ��������� �� ������� �������
            head = head->next; // ��������� � ���������� ��������
            delete obj_ptr; // ������� ������� �������, ���������� ������
        }
    }
    // ��������� ��������� ������ ������
    head = nullptr;
}


int Keeper::getLen() { return len; }

void Keeper::edit(int index) {
    // �������� ������������ ������� � ������� ��������� � ������
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;

        // ���� ������ ����� 0, �������������� ������ ������� �������� � ���������� ������
        if (index == 0) {
            obj_ptr->data->edit();
            return;
        }

        // ����������� �� ������ �� ������� �������
        for (int i = 0; i < index; i++) {
            obj_ptr = obj_ptr->next;
        }

        // �������������� ������ ��������
        obj_ptr->data->edit();
    }
    else {
        // ����� ��������� �� ������, ���� ������ ����������� ��� ������ ����
        cout << "��� ������" << endl;
    }
}


// ���������� ���������
void Keeper::add(Sign* new_data) {
    // �������� ������ ���� �������
    Queue* new_obj = new Queue;
    new_obj->data = new_data;
    new_obj->next = nullptr;

    // ���� ������ ���� ��� ����� ������� ����� ����� ������ ��� ������ ���� ��������,
    // �� ����� ������� ���������� ������� ������
    if (head == nullptr || head->data->getBirthdayInt() >= new_data->getBirthdayInt()) {
        new_obj->next = head;
        head = new_obj;
    }
    else {
        // ����� ������� ����� ��� ������� ������ �������� � ������������� �������
        Queue* current = head;
        while (current->next != nullptr && current->next->data->getBirthdayInt() <= new_data->getBirthdayInt()) {
            current = current->next;
        }
        // ��������� ����� ������� ����� ������� ��������� � ��������� ���������
        new_obj->next = current->next;
        current->next = new_obj;
    }
    // ����������� ������� ��������� � ������
    len++;
}



void Keeper::remove(int index) {
    // �������� ������������ ������� � ������� ��������� � ������
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;
        Queue* tmp_ptr = head;

        // ����������� �� ������ �� ������� �������
        for (int i = 0; i < index; i++) {
            tmp_ptr = obj_ptr;
            obj_ptr = obj_ptr->next;
        }

        // ���� ��������� ������� - ������ � ������, ��������� ������
        if (obj_ptr == head) {
            head = obj_ptr->next;
        }
        else {
            // �����, ��������� ��������� ����������� ��������, ����� ���������� ��������� �������
            tmp_ptr->next = obj_ptr->next;
        }

        // ����������� ������ � ��������� �������� � ������������ ������
        obj_ptr->data->~Sign(); // ����� ����������� ��� ����������� ������������ ��������
        delete(obj_ptr);

        // ���������� �������� ��������� � ������
        len--;
    }
    else {
        // ����� ��������� �� ������, ���� ������ ����������� ��� ������ ����
        cout << "��� ������" << endl;
    }
}


void Keeper::save() {
    // �������� ����� ��� ������
    ofstream file;
    string file_name = "sign.txt";
    try {
        file.open(file_name);
        if (!file) {
            // ���� ��������� ������ ��� �������� �����, ������������ ����������
            throw runtime_error("������ ��� �������� ����� " + file_name + " ��� ���������� ������");
        }
    }
    catch (const exception& e) {
        // ��������� � ����� ��������� �� ������, ���� ��������� ����������
        cout << "������: " << e.what() << endl;
        return;
    }

    // ������ ���������� ��������� � ����
    file << len << endl;
    file.close();  // �������� ����� ����� ������ ���������� ���������

    // ����� ������ � ���������� ������ ������� ��������
    Queue* obj_ptr = head;
    while (obj_ptr != nullptr) {
        obj_ptr->data->save();  // ����� ������ save � ������� ������ Sign ��� ���������� ������
        obj_ptr = obj_ptr->next;
    }

    // ����� ��������� � �������� ����������
    cout << "��������� " << len << " ������" << endl;
}


void Keeper::load() {
    // ���� ������ �� ����, ����������� ��� ����� ��������� ����� ������
    if (len != 0) {
        clear();
    }

    // ���������� ��� ���������� ������ �� �����
    int input_len;
    string inputName, inputSign, inputBirthday, firstName, secondName;
    int birthday[3];

    // ������� ������� ���� ��� ������
    ifstream file;
    string file_name = "sign.txt";
    try {
        file.open(file_name);
        if (!file) {
            throw runtime_error("������ ��� �������� ����� " + file_name + " ��� ������ ������");
        }
    }
    catch (const exception& e) {
        // ��������� � ����� ��������� �� ������, ���� ��������� ����������
        cout << "������: " << e.what() << endl;
        return;
    }

    // ��������� ���������� ��������� � �����
    file >> input_len;
    file.ignore(32767, '\n');

    // �������� ������ �� ����� � ���������� �� � ������
    for (int i = 0; i < input_len; i++) {
        getline(file, inputName);
        getline(file, inputSign);
        getline(file, inputBirthday);

        // ������ ������ � ������ �� ��������� �����
        istringstream issn(inputName);
        issn >> firstName >> secondName;

        // ������ ������ � ����� �������� �� ������������
        istringstream issb(inputBirthday);
        issb >> birthday[0] >> birthday[1] >> birthday[2];

        // �������� ������ ������� Sign � ���������� ��� � ������
        Sign* new_Sign = new Sign(firstName, secondName, inputSign, birthday);
        add(new_Sign);
    }

    // �������� ����� ����� ������
    file.close();

    // ����� ��������� � �������� �������� ������
    cout << "��������� " << len << " ������" << endl;
}


void Keeper::show() {
    if (head != nullptr) {
        Queue* obj_ptr = head;

        // ����� ���������� � ������ �������� ������
        cout << "";
        obj_ptr->data->printInfo();

        // ����� ���������� �� ��������� ��������� ������
        for (int i = 0; i < len - 1; i++) {
            obj_ptr = obj_ptr->next;
            cout << "" << i + 1 << ". ";
            obj_ptr->data->printInfo();
        }
    }
    else {
        cout << "��� ������" << endl;
    }
}


Sign* Keeper::operator[](int index) {
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;

        // ���� ������ ����� 0, �������������� ������ ������� �������� � ������� nullptr
        if (index == 0) {
            obj_ptr->data->edit();
            return nullptr;
        }

        // ����������� �� ������ �� ������� �������
        for (int i = 0; i < index; i++) {
            obj_ptr = obj_ptr->next;
        }

        // �������������� ������ ��������
        obj_ptr->data->edit();
    }
    cout << "��� ������" << endl;
    return nullptr;
}


void Keeper::getBySurname(const string& surname) {
    bool has_obj = false;
    if (head != nullptr) {
        Queue* obj_ptr = head;
        if (obj_ptr->data->getSurname() == surname) {
            cout << "";
            obj_ptr->data->printInfo();
            has_obj = true;
        }
        for (int i = 0; i < len - 1; i++) {
            obj_ptr = obj_ptr->next;
            if (obj_ptr->data->getSurname() == surname) {
                cout << "" << i + 1 << ". ";
                obj_ptr->data->printInfo();
                has_obj = true;
            }
        }
    }
    else
        cout << "��� ������" << endl;
    if (!has_obj)
        cout << "��� ������" << endl;
}

