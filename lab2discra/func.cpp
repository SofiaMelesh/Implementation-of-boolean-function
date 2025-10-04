#include <iostream>
#include <iomanip>
using namespace std;

void Start() {
    cout << endl << "*********************" << endl
        << "* ����� ����������! *" << endl <<
        "*********************" << endl;
};

void Menu() {
    cout << "      * ���� *" << endl <<
            "      ********" << endl;
}

int OperationsMenu() {

    cout << endl << "1) ������� ������� ����������" << endl
        << "2) ���� f" << endl
        << "3) ���� f" << endl
        << "4) ������� ��������� f" << endl << endl
        << "5) ��������� �� ���� �������� ������� �������" << endl
        << "6) ���������� �������� ������� ������� �� �������� ��������� " << endl
        << "7) ���������� �������� ������� ������� �� ���" << endl << endl;

    int op;
    bool validInput = false;
    while (!validInput) {
        cout << "����: ";
        cin >> op;
        if (cin.fail() || op < 0 || op > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������ �����! ������� ����� �� 0 �� 7 ������������!" << endl;
        }
        else if (op == 0) {
            return 0;
        }
        else return op;
    }
}
void Bye() {
    cout << endl << "********************" << endl
        << "* �� ����� ������! *" << endl <<
        "********************" << endl << endl;
}
