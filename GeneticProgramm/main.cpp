
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



	srand(time(NULL));

	cout << "test" << endl;
	
	double crossove_prob = 0.38;
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


	Chromosome* chr1 = new Chromosome(generator->GenerateNewTree(2, 2));
	Chromosome* chr2 = new Chromosome(generator->GenerateNewTree(2, 2));
	Chromosome* chr3 = new Chromosome(generator->GenerateNewTree(2, 2));
	Chromosome* chr4 = new Chromosome(generator->GenerateNewTree(2, 2));
	Chromosome* chr5 = new Chromosome(generator->GenerateNewTree(2, 2));

	data->push_back(chr1);
	data->push_back(chr2);
	data->push_back(chr3);
	data->push_back(chr4);
	data->push_back(chr5);

	// setup GASelector
	GASelector* selector = new GASelector(data, eval);

	//setup GAWorker
	GAWorker* worker = new GAWorker(data,0.0,0.63);


	worker->SetExecuter(executer);
	worker->SetSelector(selector);



	delete worker;

	system("pause");

	return 0;
}


