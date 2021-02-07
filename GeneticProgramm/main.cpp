
#include <iostream>
#include <vector>
#include <string>
#include <map>


#include "Calculate.h"
#include "RedefinedOperators.h"
#include "GAEvaluate.h"
#include "GAExecuter.h"
#include "GAOperators.h"
#include "GASelector.h"
#include "GAWorker.h"
using namespace std;
int main()
{



	srand(time(0));

	cout << "test" << endl;
	double crossove_prob = 0.68;
	std::vector<std::string> vars = std::vector<std::string>();
	vars.push_back("x");

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

	std::map<std::string, double> var_map = { {"x",-1.3},};

	std::map<std::string, SFunc> single_functions_map = { {"abs",RedefOp::myabs} };

	std::map<std::string, DFunc> double_functions_map = { {"+",RedefOp::myplus},{"-",RedefOp::myminus},{"*",RedefOp::mymult} };

	// setup calculator
	Calcluate* calc = new Calcluate(vars, constants, funcs, func_map, single_functions_map, double_functions_map);
	calc->SetVarsMap(var_map);

	//setup input data
	std::vector<double> x = {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};
	std::vector<double> y = {1.2,2.3,3.4,4.5,5.6,6.7,7.8,8.8,10};
	//Setup GAEvaulate
	GAEvaluate* eval = new GAEvaluate(calc);
	eval->SetX(x);
	eval->SetY(y);

	// setup tree generator
	SubTreeGenerator* generator = new SubTreeGenerator(vars, constants, funcs, func_map);


	//Setup GaOperators
	GAOperators* operators = new GAOperators(generator);


	// setup GAExecuter
	GAExecuter* executer = new GAExecuter(operators);


	//create population
	std::vector<Chromosome*>* data = new std::vector<Chromosome*>();
	const uint to_gen = 20;
	const uint min_dep = 2;
	const uint max_dep = 5;
	for (uint i = 0; i < to_gen; ++i)
	{
		data->push_back(new Chromosome(generator->GenerateNewTree(min_dep, max_dep)));
	}

	// setup GASelector
	GASelector* selector = new GASelector(data, eval);
	selector->SetChoseSize(2);
	selector->SetCrossoverProbability(crossove_prob);

	//setup GAWorker
	GAWorker* worker = new GAWorker(data,0.0,0.63);


	worker->SetExecuter(executer);
	worker->SetSelector(selector);

	cout << *worker << endl;
	auto iter_b = data->begin();
	while (iter_b < data->end())
	{
		cout << "Eval: " << eval->Eval(*iter_b) << endl;
		iter_b++;
	}


	worker->ExecuteMany(100);
	cout << *worker << endl;

	auto dat = worker->GetData();

	auto iter = dat->begin();
	while (iter < dat->end())
	{
		cout << "Eval: " << eval->Eval(*iter) << endl;
		iter++;
	}

	delete worker;

	system("pause");

	return 0;
}


