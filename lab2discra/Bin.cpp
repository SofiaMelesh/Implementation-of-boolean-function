#include "Bin.h"
#include <iostream>
#include <string>
#include <limits>
#include "func.h"

using namespace std;

Bin::Bin() {
    GreyCode(); // Генерируем коды Грея и заполняем таблицу
    fillf();
    SDNF();
    SKNF();
    PZhegalkina();
}

//операции
void Bin::Operations(int op) {
    switch (op)
    {
    case 0:
        break;
    case 1:
        printTable();
        break;
    case 2:
        cout  << sdnf << endl;
        break;
    case 3:
        cout << sknf << endl;
        break;
    case 4:
        cout << polynomial << endl;
        break;
    case 5:
        evaluateSDNF();
        break;
    case 6:
       evaluatePolynomial();
        break;
    case 7:
        evaluateBDRFromInput();
        break;
    }
};

void Bin::evaluateBDRFromInput() {

    string input;
    if (!checkBinaryInput(input)) {
        return; // Если ввод некорректен, то ничего не делаем
    }

    // Преобразуем строку в булевы значения
    bool a = input[0] == '1';
    bool b = input[1] == '1';
    bool c = input[2] == '1';
    bool d = input[3] == '1';

    // Создаем БДД
    auto root = createBDR();

    // Вычисляем значение БДД
    int result = evaluateBDR(root, a, b, c, d);

    cout << "Ответ по БДР: "<< result << endl;
    check(input);
};

void Bin::printTable() {
    int index = 0;
    int number = 48045; // Число, для которого мы хотим вывести двоичное представление

    cout << "a b c d  | f" << endl;

    for (const auto& pair : table) {
        for (const auto& elem : pair.first) {
            cout << elem << " ";
        }
        cout << " | " << f[index]; // Выводим двоичное представление рядом
        cout << endl;
        index++;
    }
    cout << endl;
}

//грей
vector<vector<int>> Bin::GreyCode() {
    vector<int> B(4, 0);
    table[B] = 0;  //начальный элемент
    for (int i = 1; i < 16; ++i) {
        int elnum = Q(i);
        B[elnum - 1] = 1 - B[elnum - 1];
        table[B] = 0;  //добавляем элемент с начальной кратностью 0 (будет изменена позже)
    }
    return {};
}

int Bin::Q(int i) {
    int q = 1;
    while (i % 2 == 0) {
        i /= 2;
        q++;
    }
    return q;
}

vector<int> Bin::fillf() {
    int number = 48045;
    for (int i = 15; i >= 0; --i) {
        f.push_back((number & (1 << i)) ? 1 : 0);
    }
    return f;
}

void Bin::SDNF() {
    int index = 0;
    for (const auto& pair : table) {
        if (f[index] == 1) { // Если значение функции равно 1
            sdnf += "(";
            for (size_t i = 0; i < pair.first.size(); ++i) {
                char variable = 'a' + i; // Преобразуем индекс в символ (a, b, c, d )
                if (pair.first[i] == 1) {
                    sdnf += variable + string(" "); // Добавляем переменную
                }
                else {
                    sdnf += "!" + string(1, variable) + " "; // Добавляем отрицание переменной
                }
                if (i < pair.first.size() - 1) {
                    sdnf += "AND ";
                }
            }
            sdnf += ") OR ";
        }
        index++;
    }
        sdnf = sdnf.substr(0, sdnf.size() - 4); // Удаляем последний " OR "
}

void Bin::SKNF() {
    int index = 0;
    for (const auto& pair : table) {
        if (f[index] == 0) { // Если значение функции равно 0
            sknf += "(";
            for (size_t i = 0; i < pair.first.size(); ++i) {
                char variable = 'a' + i; // Преобразуем индекс в символ (a, b, c, d и т.д.)
                if (pair.first[i] == 0) {
                    sknf += variable + string(" "); // Добавляем переменную
                }
                else {
                    sknf += "!" + string(1, variable) + " "; // Добавляем отрицание переменной
                }
                if (i < pair.first.size() - 1) {
                    sknf += "OR ";
                }
            }
            sknf += ") AND ";
        }
        index++;
    }
        sknf = sknf.substr(0, sknf.size() - 5); // Удаляем последний " AND "
}

void Bin::PZhegalkina() {
    vector<int> coeff = f; // Копируем значения функции
    vector<int> results;

    for (size_t i = 0; i < f.size(); ++i) {
        results.push_back(coeff[0]);
        vector<int> temp;
        for (size_t j = 0; j < coeff.size() - 1; ++j) {
            temp.push_back(coeff[j] ^ coeff[j + 1]); // XOR
        }
        coeff = temp;
    }

    // Построение полинома
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i] == 1) {
            if (!polynomial.empty()) polynomial += " + ";
            if (i == 0) { // Если индекс равен 0, добавляем свободный член
                polynomial += "1";
            }
            else {
                for (int j = 3; j >= 0; --j) { // Меняем порядок проверки битов (от старших к младшим)
                    if ((i >> j) & 1) { // Проверяем, установлен ли бит j в числе i
                        polynomial += string(1, 'a' + (3 - j)); // Преобразуем бит в правильную переменную
                    }
                }
            }
        }
    }
}

void Bin::evaluateSDNF() {
    string vars;
    if (!checkBinaryInput(vars)) {
        return; // Если ввод некорректен, то ничего не делаем
    }

    // Преобразуем строку ввода в значения переменных
    map<char, int> varValues;
    for (size_t i = 0; i < vars.size(); ++i) {
        char var = 'a' + i;
        varValues[var] = vars[i] == '1' ? 1 : 0; // Преобразуем символы '1' и '0' в соответствующие значения
    }

    // Удаляем пробелы из СДНФ
    string sdnfNoSpaces = "";
    for (char c : sdnf) {
        if (c != ' ') {
            sdnfNoSpaces += c;
        }
    }

    // Перебор всех термов в СДНФ
    bool result = false;
    size_t pos = 0;

    while (pos < sdnfNoSpaces.size()) {
        size_t start = sdnfNoSpaces.find("(", pos);
        size_t end = sdnfNoSpaces.find(")", pos);
        if (start == string::npos || end == string::npos) break;

        string term = sdnfNoSpaces.substr(start + 1, end - start - 1); // Извлекаем терм

        // Обработка терма (например, "!aANDbANDc")
        bool termResult = true;
        size_t andPos = 0;

        while (andPos < term.size()) {
            size_t nextAnd = term.find("AND", andPos); // Найти следующий "AND"
            string literal = (nextAnd == string::npos) ? term.substr(andPos) : term.substr(andPos, nextAnd - andPos);

            // Проверяем текущую переменную или её отрицание
            if (literal[0] == '!') {
                char var = literal[1];
                if (varValues.find(var) == varValues.end()) {
                    cerr << "Ошибка: Переменная " << var << " не найдена!" << endl;
                    return;
                }
                termResult &= (varValues[var] == 0); // Учитываем отрицание
            }
            else {
                char var = literal[0];
                if (varValues.find(var) == varValues.end()) {
                    cerr << "Ошибка: Переменная " << var << " не найдена!" << endl;
                    return;
                }
                termResult &= (varValues[var] == 1); // Учитываем положительное значение
            }

            andPos = (nextAnd == string::npos) ? term.size() : nextAnd + 3; // Переход к следующему "AND"
        }

        result |= termResult; // Если хотя бы один терм истинный, результат = true
        pos = end + 1; // Переход к следующему терму
    }

    cout << "Ответ по СДНФ: " << result << endl;
    check(vars);
}


void Bin::check(string vars) {

    // Генерация индекса для таблицы истинности по значению vars
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        // Преобразуем символ '1' или '0' в соответствующее число 1 или 0 и добавляем в индекс
        index |= (vars[i] - '0') << (3 - i); // 3-i для учета старших битов
    }

    // Печатаем результат в зависимости от значения функции в векторе f
    if (index >= 0 && index < 16) {  // Проверяем, что индекс в пределах 0-15
        if (f[index] == 1) {
            cout << "Ответ по таблице (проверка): 1" << endl;
        }
        else {
            cout << "Ответ по таблице (проверка): 0" << endl;
        }
    }
}

void Bin::evaluatePolynomial() {
    string vars;
    if (!checkBinaryInput(vars)) {
        return; // Если ввод некорректен, то ничего не делаем
    }

    // Преобразуем строку ввода в значения переменных
    map<char, int> varValues;
    for (size_t i = 0; i < vars.size(); ++i) {
        char var = 'a' + i;
        varValues[var] = vars[i] == '1' ? 1 : 0; // Преобразуем символы '1' и '0' в соответствующие значения
    }

    // Вычисление значения полинома Жегалкина
    int result = 0;
    size_t pos = 0;

    while (pos < polynomial.size()) {
        size_t termEnd = polynomial.find(" + ", pos); // Ищем конец текущего терма
        if (termEnd == string::npos) termEnd = polynomial.size();

        string term = polynomial.substr(pos, termEnd - pos); // Извлекаем текущий терм
        int termValue = 1;

        for (char c : term) {
            if (isalpha(c)) { // Если это переменная
                termValue &= varValues[c];
            }
        }

        result ^= termValue; // XOR терма с результатом
        pos = termEnd + 3; // Переход к следующему терму (учитываем " + ")
    }

    cout << "Ответ по полиному Жегалкина: " << result << endl;
    check(vars);
}

bool Bin::checkBinaryInput(string& input) {
    while (true) {
        cout << "Введите 4 бита (например, 1010): ";
        cin >> input;

        // Проверка на длину
        if (input.length() != 4) {
            cout << "Ошибка! Введите ровно 4 бита." << endl;
            continue;
        }

        // Проверка на правильность символов
        bool isValid = true;
        for (char c : input) {
            if (c != '0' && c != '1') {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            return true; // Ввод корректен, возвращаем true
        }
        else {
            cout << "Ошибка! Ввод должен содержать только 0 и 1." << endl;
        }
    }
}




