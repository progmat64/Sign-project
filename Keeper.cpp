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
    // Проверка, что список не пуст
    if (head != nullptr) {
        Queue* obj_ptr;

        // Пока голова списка не станет пустой
        while (head != nullptr) {
            obj_ptr = head; // Сохраняем указатель на текущий элемент
            head = head->next; // Переходим к следующему элементу
            delete obj_ptr; // Удаляем текущий элемент, освобождая память
        }
    }
    // Обнуление указателя головы списка
    head = nullptr;
}


int Keeper::getLen() { return len; }

void Keeper::edit(int index) {
    // Проверка корректности индекса и наличия элементов в списке
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;

        // Если индекс равен 0, редактирование данных первого элемента и завершение метода
        if (index == 0) {
            obj_ptr->data->edit();
            return;
        }

        // Перемещение по списку до нужного индекса
        for (int i = 0; i < index; i++) {
            obj_ptr = obj_ptr->next;
        }

        // Редактирование данных элемента
        obj_ptr->data->edit();
    }
    else {
        // Вывод сообщения об ошибке, если индекс некорректен или список пуст
        cout << "Нет данных" << endl;
    }
}


// сортировка вставками
void Keeper::add(Sign* new_data) {
    // Создание нового узла очереди
    Queue* new_obj = new Queue;
    new_obj->data = new_data;
    new_obj->next = nullptr;

    // Если список пуст или новый элемент имеет более раннюю или равную дату рождения,
    // то новый элемент становится головой списка
    if (head == nullptr || head->data->getBirthdayInt() >= new_data->getBirthdayInt()) {
        new_obj->next = head;
        head = new_obj;
    }
    else {
        // Иначе находим место для вставки нового элемента в упорядоченном порядке
        Queue* current = head;
        while (current->next != nullptr && current->next->data->getBirthdayInt() <= new_data->getBirthdayInt()) {
            current = current->next;
        }
        // Вставляем новый элемент между текущим элементом и следующим элементом
        new_obj->next = current->next;
        current->next = new_obj;
    }
    // Увеличиваем счетчик элементов в списке
    len++;
}



void Keeper::remove(int index) {
    // Проверка корректности индекса и наличия элементов в списке
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;
        Queue* tmp_ptr = head;

        // Перемещение по списку до нужного индекса
        for (int i = 0; i < index; i++) {
            tmp_ptr = obj_ptr;
            obj_ptr = obj_ptr->next;
        }

        // Если удаляемый элемент - первый в списке, обновляем голову
        if (obj_ptr == head) {
            head = obj_ptr->next;
        }
        else {
            // Иначе, обновляем указатель предыдущего элемента, чтобы пропустить удаляемый элемент
            tmp_ptr->next = obj_ptr->next;
        }

        // Уничтожение данных в удаляемом элементе и освобождение памяти
        obj_ptr->data->~Sign(); // Вызов деструктора для корректного освобождения ресурсов
        delete(obj_ptr);

        // Уменьшение счетчика элементов в списке
        len--;
    }
    else {
        // Вывод сообщения об ошибке, если индекс некорректен или список пуст
        cout << "Нет данных" << endl;
    }
}


void Keeper::save() {
    // Открытие файла для записи
    ofstream file;
    string file_name = "sign.txt";
    try {
        file.open(file_name);
        if (!file) {
            // Если произошла ошибка при открытии файла, генерируется исключение
            throw runtime_error("Ошибка при открытии файла " + file_name + " для сохранения данных");
        }
    }
    catch (const exception& e) {
        // Обработка и вывод сообщения об ошибке, если произошло исключение
        cout << "Ошибка: " << e.what() << endl;
        return;
    }

    // Запись количества элементов в файл
    file << len << endl;
    file.close();  // Закрытие файла после записи количества элементов

    // Обход списка и сохранение данных каждого элемента
    Queue* obj_ptr = head;
    while (obj_ptr != nullptr) {
        obj_ptr->data->save();  // Вызов метода save у объекта класса Sign для сохранения данных
        obj_ptr = obj_ptr->next;
    }

    // Вывод сообщения о успешном сохранении
    cout << "Сохранено " << len << " Знаков" << endl;
}


void Keeper::load() {
    // Если список не пуст, освобождаем его перед загрузкой новых данных
    if (len != 0) {
        clear();
    }

    // Переменные для считывания данных из файла
    int input_len;
    string inputName, inputSign, inputBirthday, firstName, secondName;
    int birthday[3];

    // Попытка открыть файл для чтения
    ifstream file;
    string file_name = "sign.txt";
    try {
        file.open(file_name);
        if (!file) {
            throw runtime_error("Ошибка при открытии файла " + file_name + " для чтения данных");
        }
    }
    catch (const exception& e) {
        // Обработка и вывод сообщения об ошибке, если произошло исключение
        cout << "Ошибка: " << e.what() << endl;
        return;
    }

    // Считываем количество элементов в файле
    file >> input_len;
    file.ignore(32767, '\n');

    // Загрузка данных из файла и добавление их в список
    for (int i = 0; i < input_len; i++) {
        getline(file, inputName);
        getline(file, inputSign);
        getline(file, inputBirthday);

        // Разбор строки с именем на отдельные части
        istringstream issn(inputName);
        issn >> firstName >> secondName;

        // Разбор строки с датой рождения на составляющие
        istringstream issb(inputBirthday);
        issb >> birthday[0] >> birthday[1] >> birthday[2];

        // Создание нового объекта Sign и добавление его в список
        Sign* new_Sign = new Sign(firstName, secondName, inputSign, birthday);
        add(new_Sign);
    }

    // Закрытие файла после чтения
    file.close();

    // Вывод сообщения о успешной загрузке данных
    cout << "Загружено " << len << " Знаков" << endl;
}


void Keeper::show() {
    if (head != nullptr) {
        Queue* obj_ptr = head;

        // Вывод информации о первом элементе списка
        cout << "";
        obj_ptr->data->printInfo();

        // Вывод информации об остальных элементах списка
        for (int i = 0; i < len - 1; i++) {
            obj_ptr = obj_ptr->next;
            cout << "" << i + 1 << ". ";
            obj_ptr->data->printInfo();
        }
    }
    else {
        cout << "Нет данных" << endl;
    }
}


Sign* Keeper::operator[](int index) {
    if (index >= 0 && index < len && head != nullptr) {
        Queue* obj_ptr = head;

        // Если индекс равен 0, редактирование данных первого элемента и возврат nullptr
        if (index == 0) {
            obj_ptr->data->edit();
            return nullptr;
        }

        // Перемещение по списку до нужного индекса
        for (int i = 0; i < index; i++) {
            obj_ptr = obj_ptr->next;
        }

        // Редактирование данных элемента
        obj_ptr->data->edit();
    }
    cout << "Нет данных" << endl;
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
        cout << "Нет данных" << endl;
    if (!has_obj)
        cout << "Нет данных" << endl;
}

