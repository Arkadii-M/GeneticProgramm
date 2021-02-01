
#include <iostream>
#include "Tree.h"
#include "SubTreeGenerator.h"
#include <string>
#include <vector>
#include <map>
#include "Calculate.h"
using namespace std;


double myplus(double p1, double p2)
{
	return p1 + p2;
}

double myminus(double p1, double p2)
{
	return p1 - p2;
}
double mymult(double p1, double p2)
{
	return p1 * p2;
}

double myabs(double p)
{
	return abs(p);
}


int main()
{
	cout << "test" << endl;

	std::vector<std::string> vars = std::vector<std::string>();
	vars.push_back("x");
	vars.push_back("y");
	vars.push_back("z");

	std::vector<std::string> constants = std::vector<std::string>();
	constants.push_back("1");
	constants.push_back("2");
	constants.push_back("3");


	std::vector<std::string> funcs = std::vector<std::string>();
	funcs.push_back("+");
	funcs.push_back("-");
	funcs.push_back("*");
	funcs.push_back("abs");


	std::map<std::string, unsigned int> func_map = { {"+",2},{"-",2} ,{"*",2},{"abs",1} };

	std::map<std::string, double> var_map = { {"x",-100},{"y",-200},{"z",450} };

	std::map<std::string, SFunc> single_functions_map = { {"abs",myabs} };

	std::map<std::string, DFunc> double_functions_map = { {"+",myplus},{"-",myminus},{"*",mymult} };

	Calcluate calc = Calcluate(vars, constants, funcs, func_map, single_functions_map, double_functions_map);
	calc.SetVarsMap(var_map);




	SubTreeGenerator generator = SubTreeGenerator(vars, constants, funcs, func_map);

	Tree* tree = generator.GenerateNewTree(2, 10);

	tree->NumerateNodes();
	cout << "Depth: " << tree->GetCurrentDepth() << endl;
	cout << "Total nodes: " << tree->GetTotalNodes() << endl;


	cout << "Calculate tree..." << endl;


	cout << calc.CalcTree(tree) << endl;

	delete tree;

	system("pause");

	return 0;
}