
#include <iostream>
#include "Tree.h"
#include "SubTreeGenerator.h"
#include <string>
#include <vector>
#include <map>
#include "Calculate.h"
#include "Chromosome.h"
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



void Crossove(Chromosome* chr1, Chromosome* chr2)
{
	Tree* first = chr1->GetData();
	Tree* second = chr2->GetData();

	uint first_count = first->GetTotalNodes();
	uint second_count = second->GetTotalNodes();

	uint r1 = rand() % (first_count-1) + 1;
	uint r2 = rand() % (second_count- 1) + 1;

	Node* node1 = first->GetNodeAtPos(r1);
	Node* node2 = second->GetNodeAtPos(r2);

	first->SetNodeAtPos(node2, r1); // don't numerate there, because after swap links the second three is numerate wrong.
	second->SetNodeAtPos(node1, r2);

	first->NumerateNodes();
	second->NumerateNodes();
}


void Mutate(Chromosome* chr,SubTreeGenerator * gen)
{
	Tree* tree = chr->GetData();

	uint count = tree->GetTotalNodes();

	uint r = rand() % (count - 1) + 1;

	Node* node = tree->GetNodeAtPos(r);

	Node* random = gen->GenerateSubTree(tree->GetMinDepth(),tree->GetMaxDepth()); // Generate random subtree here

	tree->SetAndDeleteOldAtPos(random, r);
	tree->NumerateNodes();
}


double Eval(std::vector<Chromosome*> * data,std::vector<double> y,Calcluate * calc)
{
	double res= 0.0;
	for (uint i = 0; i < data->size(); ++i)
	{
		res += abs(   calc->CalcTree((*data)[i]->GetData())   - y[i]    );
	}
	return res;

}
int main()
{/*
	srand(time(NULL));

	cout << "test" << endl;

	std::vector<std::string> vars = std::vector<std::string>();
	vars.push_back("x");
	vars.push_back("y");
	vars.push_back("z");

	std::vector<std::string> constants = std::vector<std::string>();
	constants.push_back("1.1");
	constants.push_back("-2.2");
	constants.push_back("3.45");


	std::vector<std::string> funcs = std::vector<std::string>();
	funcs.push_back("+");
	funcs.push_back("-");
	funcs.push_back("*");
	funcs.push_back("abs");


	std::map<std::string, unsigned int> func_map = { {"+",2},{"-",2} ,{"*",2},{"abs",1} };

	std::map<std::string, double> var_map = { {"x",-1.3},{"y",-2.8},{"z",4.7} };

	std::map<std::string, SFunc> single_functions_map = { {"abs",myabs} };

	std::map<std::string, DFunc> double_functions_map = { {"+",myplus},{"-",myminus},{"*",mymult} };

	Calcluate calc = Calcluate(vars, constants, funcs, func_map, single_functions_map, double_functions_map);
	calc.SetVarsMap(var_map);




	SubTreeGenerator generator = SubTreeGenerator(vars, constants, funcs, func_map);
	Tree* tree = generator.GenerateNewTree(2, 2);
	Chromosome* chr1 = new Chromosome(tree);

	delete tree;
	*/

	std::vector<int> data = { 1,2,3,4,5 };
	auto iter = data.begin();

	while (iter < data.end())
	{
		if ((*iter) == 1)
		{
			iter =data.erase(iter);
			continue;
		}
		cout << *iter << endl;
		iter++;
	}
	system("pause");

	return 0;
}