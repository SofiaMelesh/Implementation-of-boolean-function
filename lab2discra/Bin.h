#include <map>
#include <vector>
#include <iostream>
#include <variant>
using namespace std;

class Bin
{
	map<vector <int>, int> table;
    vector<int> f;
    string sdnf;
	string polynomial;
	string sknf;
public:
	Bin();
	vector<vector<int>> GreyCode();
	int Q(int i);
	vector<int> fillf();
	void printTable();
	void Operations(int op);
	void SDNF();
	void SKNF();
	void PZhegalkina();
	void check(string vars);
	void evaluateSDNF();
	void evaluatePolynomial();
	void evaluateBDRFromInput();
	bool checkBinaryInput(string& input);
  


};

