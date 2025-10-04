#include <iostream>
#include "func.h"
#include "Bin.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");

	Start(); //приветственное окно
	Bin bin;
	int tmp = 1;
	Menu();

	while (tmp) {
		tmp = OperationsMenu();
		bin.Operations(tmp); //меню операций
		if (tmp == 0) break;
	};
	Bye();
	return 0;
}