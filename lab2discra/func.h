#pragma once
void Start();
void Menu();
int OperationsMenu();
void Bye();

struct BDRNode {
	std::string variable;  // Имя переменной
	std::shared_ptr<BDRNode> zero; // Узел для "0"
	std::shared_ptr<BDRNode> one;  // Узел для "1"
	int value = -1;                // Лист (0 или 1)
};

std::shared_ptr<BDRNode> inline createBDR() {
    // Листовые узлы
    auto leaf1 = std::make_shared<BDRNode>();
    leaf1->value = 1;

    auto leaf0 = std::make_shared<BDRNode>();
    leaf0->value = 0;

    // Узлы уровня d
    auto node_d1 = std::make_shared<BDRNode>();
    node_d1->variable = "d";
    node_d1->zero = leaf1; 
    node_d1->one = leaf0;  

    auto node_d2 = std::make_shared<BDRNode>();
    node_d2->variable = "d";
    node_d2->zero = leaf0;
    node_d2->one = leaf1;

    // Узлы уровня c
    auto node_c1 = std::make_shared<BDRNode>();
    node_c1->variable = "c";
    node_c1->zero = node_d1;
    node_c1->one = leaf1;

    auto node_c2 = std::make_shared<BDRNode>();
    node_c2->variable = "c";
    node_c2->zero = leaf1;
    node_c2->one = node_d2;

    // Узлы уровня b
    auto node_b1 = std::make_shared<BDRNode>();
    node_b1->variable = "b";
    node_b1->zero = node_d1;
    node_b1->one = node_c2;

    // Узлы уровня a
    auto root = std::make_shared<BDRNode>();
    root->variable = "a";
    root->zero = node_c1;
    root->one = node_b1;

    return root;
}

int inline evaluateBDR(const std::shared_ptr<BDRNode>& node, bool a, bool b, bool c, bool d) {
	if (node->value != -1) {
		return node->value; // Если это лист, возвращаем его значение
	}

	// Определяем, какой узел использовать в зависимости от значения переменной
	if (node->variable == "a") {
		return evaluateBDR(a ? node->one : node->zero, a, b, c, d);
	}
	else if (node->variable == "b") {
		return evaluateBDR(b ? node->one : node->zero, a, b, c, d);
	}
	else if (node->variable == "c") {
		return evaluateBDR(c ? node->one : node->zero, a, b, c, d);
	}
	else if (node->variable == "d") {
		return evaluateBDR(d ? node->one : node->zero, a, b, c, d);
	}
}