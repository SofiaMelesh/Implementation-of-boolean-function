#include <iostream>
#include <iomanip>
using namespace std;

void Start() {
    cout << endl << "*********************" << endl
        << "* ДОБРО ПОЖАЛОВАТЬ! *" << endl <<
        "*********************" << endl;
};

void Menu() {
    cout << "      * МЕНЮ *" << endl <<
            "      ********" << endl;
}

int OperationsMenu() {

    cout << endl << "1) Вывести таблицу истинности" << endl
        << "2) СДНФ f" << endl
        << "3) СКНФ f" << endl
        << "4) Полином Жегалкина f" << endl << endl
        << "5) Вычислить по СДНФ значение булевой функции" << endl
        << "6) Вычисление значения булевой функции по полиному Жегалкина " << endl
        << "7) Вычисление значения булевой функции по БДР" << endl << endl;

    int op;
    bool validInput = false;
    while (!validInput) {
        cout << "Ввод: ";
        cin >> op;
        if (cin.fail() || op < 0 || op > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Введите число от 0 до 7 включительно!" << endl;
        }
        else if (op == 0) {
            return 0;
        }
        else return op;
    }
}
void Bye() {
    cout << endl << "********************" << endl
        << "* ДО НОВЫХ ВСТРЕЧ! *" << endl <<
        "********************" << endl << endl;
}
