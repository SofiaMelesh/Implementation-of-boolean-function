#include "Bin.h"
#include <iostream>
#include <string>
#include <limits>
#include "func.h"

using namespace std;

Bin::Bin() {
    GreyCode(); // ���������� ���� ���� � ��������� �������
    fillf();
    SDNF();
    SKNF();
    PZhegalkina();
}

//��������
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
        return; // ���� ���� �����������, �� ������ �� ������
    }

    // ����������� ������ � ������ ��������
    bool a = input[0] == '1';
    bool b = input[1] == '1';
    bool c = input[2] == '1';
    bool d = input[3] == '1';

    // ������� ���
    auto root = createBDR();

    // ��������� �������� ���
    int result = evaluateBDR(root, a, b, c, d);

    cout << "����� �� ���: "<< result << endl;
    check(input);
};

void Bin::printTable() {
    int index = 0;
    int number = 48045; // �����, ��� �������� �� ����� ������� �������� �������������

    cout << "a b c d  | f" << endl;

    for (const auto& pair : table) {
        for (const auto& elem : pair.first) {
            cout << elem << " ";
        }
        cout << " | " << f[index]; // ������� �������� ������������� �����
        cout << endl;
        index++;
    }
    cout << endl;
}

//����
vector<vector<int>> Bin::GreyCode() {
    vector<int> B(4, 0);
    table[B] = 0;  //��������� �������
    for (int i = 1; i < 16; ++i) {
        int elnum = Q(i);
        B[elnum - 1] = 1 - B[elnum - 1];
        table[B] = 0;  //��������� ������� � ��������� ���������� 0 (����� �������� �����)
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
        if (f[index] == 1) { // ���� �������� ������� ����� 1
            sdnf += "(";
            for (size_t i = 0; i < pair.first.size(); ++i) {
                char variable = 'a' + i; // ����������� ������ � ������ (a, b, c, d )
                if (pair.first[i] == 1) {
                    sdnf += variable + string(" "); // ��������� ����������
                }
                else {
                    sdnf += "!" + string(1, variable) + " "; // ��������� ��������� ����������
                }
                if (i < pair.first.size() - 1) {
                    sdnf += "AND ";
                }
            }
            sdnf += ") OR ";
        }
        index++;
    }
        sdnf = sdnf.substr(0, sdnf.size() - 4); // ������� ��������� " OR "
}

void Bin::SKNF() {
    int index = 0;
    for (const auto& pair : table) {
        if (f[index] == 0) { // ���� �������� ������� ����� 0
            sknf += "(";
            for (size_t i = 0; i < pair.first.size(); ++i) {
                char variable = 'a' + i; // ����������� ������ � ������ (a, b, c, d � �.�.)
                if (pair.first[i] == 0) {
                    sknf += variable + string(" "); // ��������� ����������
                }
                else {
                    sknf += "!" + string(1, variable) + " "; // ��������� ��������� ����������
                }
                if (i < pair.first.size() - 1) {
                    sknf += "OR ";
                }
            }
            sknf += ") AND ";
        }
        index++;
    }
        sknf = sknf.substr(0, sknf.size() - 5); // ������� ��������� " AND "
}

void Bin::PZhegalkina() {
    vector<int> coeff = f; // �������� �������� �������
    vector<int> results;

    for (size_t i = 0; i < f.size(); ++i) {
        results.push_back(coeff[0]);
        vector<int> temp;
        for (size_t j = 0; j < coeff.size() - 1; ++j) {
            temp.push_back(coeff[j] ^ coeff[j + 1]); // XOR
        }
        coeff = temp;
    }

    // ���������� ��������
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i] == 1) {
            if (!polynomial.empty()) polynomial += " + ";
            if (i == 0) { // ���� ������ ����� 0, ��������� ��������� ����
                polynomial += "1";
            }
            else {
                for (int j = 3; j >= 0; --j) { // ������ ������� �������� ����� (�� ������� � �������)
                    if ((i >> j) & 1) { // ���������, ���������� �� ��� j � ����� i
                        polynomial += string(1, 'a' + (3 - j)); // ����������� ��� � ���������� ����������
                    }
                }
            }
        }
    }
}

void Bin::evaluateSDNF() {
    string vars;
    if (!checkBinaryInput(vars)) {
        return; // ���� ���� �����������, �� ������ �� ������
    }

    // ����������� ������ ����� � �������� ����������
    map<char, int> varValues;
    for (size_t i = 0; i < vars.size(); ++i) {
        char var = 'a' + i;
        varValues[var] = vars[i] == '1' ? 1 : 0; // ����������� ������� '1' � '0' � ��������������� ��������
    }

    // ������� ������� �� ����
    string sdnfNoSpaces = "";
    for (char c : sdnf) {
        if (c != ' ') {
            sdnfNoSpaces += c;
        }
    }

    // ������� ���� ������ � ����
    bool result = false;
    size_t pos = 0;

    while (pos < sdnfNoSpaces.size()) {
        size_t start = sdnfNoSpaces.find("(", pos);
        size_t end = sdnfNoSpaces.find(")", pos);
        if (start == string::npos || end == string::npos) break;

        string term = sdnfNoSpaces.substr(start + 1, end - start - 1); // ��������� ����

        // ��������� ����� (��������, "!aANDbANDc")
        bool termResult = true;
        size_t andPos = 0;

        while (andPos < term.size()) {
            size_t nextAnd = term.find("AND", andPos); // ����� ��������� "AND"
            string literal = (nextAnd == string::npos) ? term.substr(andPos) : term.substr(andPos, nextAnd - andPos);

            // ��������� ������� ���������� ��� � ���������
            if (literal[0] == '!') {
                char var = literal[1];
                if (varValues.find(var) == varValues.end()) {
                    cerr << "������: ���������� " << var << " �� �������!" << endl;
                    return;
                }
                termResult &= (varValues[var] == 0); // ��������� ���������
            }
            else {
                char var = literal[0];
                if (varValues.find(var) == varValues.end()) {
                    cerr << "������: ���������� " << var << " �� �������!" << endl;
                    return;
                }
                termResult &= (varValues[var] == 1); // ��������� ������������� ��������
            }

            andPos = (nextAnd == string::npos) ? term.size() : nextAnd + 3; // ������� � ���������� "AND"
        }

        result |= termResult; // ���� ���� �� ���� ���� ��������, ��������� = true
        pos = end + 1; // ������� � ���������� �����
    }

    cout << "����� �� ����: " << result << endl;
    check(vars);
}


void Bin::check(string vars) {

    // ��������� ������� ��� ������� ���������� �� �������� vars
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        // ����������� ������ '1' ��� '0' � ��������������� ����� 1 ��� 0 � ��������� � ������
        index |= (vars[i] - '0') << (3 - i); // 3-i ��� ����� ������� �����
    }

    // �������� ��������� � ����������� �� �������� ������� � ������� f
    if (index >= 0 && index < 16) {  // ���������, ��� ������ � �������� 0-15
        if (f[index] == 1) {
            cout << "����� �� ������� (��������): 1" << endl;
        }
        else {
            cout << "����� �� ������� (��������): 0" << endl;
        }
    }
}

void Bin::evaluatePolynomial() {
    string vars;
    if (!checkBinaryInput(vars)) {
        return; // ���� ���� �����������, �� ������ �� ������
    }

    // ����������� ������ ����� � �������� ����������
    map<char, int> varValues;
    for (size_t i = 0; i < vars.size(); ++i) {
        char var = 'a' + i;
        varValues[var] = vars[i] == '1' ? 1 : 0; // ����������� ������� '1' � '0' � ��������������� ��������
    }

    // ���������� �������� �������� ���������
    int result = 0;
    size_t pos = 0;

    while (pos < polynomial.size()) {
        size_t termEnd = polynomial.find(" + ", pos); // ���� ����� �������� �����
        if (termEnd == string::npos) termEnd = polynomial.size();

        string term = polynomial.substr(pos, termEnd - pos); // ��������� ������� ����
        int termValue = 1;

        for (char c : term) {
            if (isalpha(c)) { // ���� ��� ����������
                termValue &= varValues[c];
            }
        }

        result ^= termValue; // XOR ����� � �����������
        pos = termEnd + 3; // ������� � ���������� ����� (��������� " + ")
    }

    cout << "����� �� �������� ���������: " << result << endl;
    check(vars);
}

bool Bin::checkBinaryInput(string& input) {
    while (true) {
        cout << "������� 4 ���� (��������, 1010): ";
        cin >> input;

        // �������� �� �����
        if (input.length() != 4) {
            cout << "������! ������� ����� 4 ����." << endl;
            continue;
        }

        // �������� �� ������������ ��������
        bool isValid = true;
        for (char c : input) {
            if (c != '0' && c != '1') {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            return true; // ���� ���������, ���������� true
        }
        else {
            cout << "������! ���� ������ ��������� ������ 0 � 1." << endl;
        }
    }
}




