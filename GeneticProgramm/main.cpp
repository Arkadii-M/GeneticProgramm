
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
#include "Random.h"
using namespace std;
int main()
{
	//srand(time(nullptr));

	cout << "test" << endl;
	double crossove_prob = 0.45;
	std::vector<std::string> vars = std::vector<std::string>(); // vars
	vars.push_back("x");

	std::vector<std::string> constants = std::vector<std::string>();// constants
	constants.push_back("1");
	constants.push_back("1.1");
	constants.push_back("1.2");
	constants.push_back("1.5");
	constants.push_back("-1");
	constants.push_back("-1.1");
	constants.push_back("-1.2");
	constants.push_back("-1.3");
	constants.push_back("-2.48");



	std::vector<std::string> funcs = std::vector<std::string>(); // functions
	funcs.push_back("*");
	funcs.push_back("+");
	funcs.push_back("-");
	funcs.push_back("/");


	std::map<std::string, unsigned int> func_map = { {"+",2},{"-",2} ,{"*",2},{"abs",1},{"/",2} }; // parameters count of function

	std::map<std::string, double> var_map = { {"x",0},}; // set value of vars

	std::map<std::string, SFunc> single_functions_map = { {"abs",RedefOp::myabs} }; // functions with single parameter

	std::map<std::string, DFunc> double_functions_map = { {"+",RedefOp::myplus},{"-",RedefOp::myminus},{"*",RedefOp::mymult},{"/",RedefOp::mydiv} };// functions with two parameters

	// setup calculator
	Calcluate* calc = new Calcluate(vars, constants, funcs, func_map, single_functions_map, double_functions_map); // this calculate tree fitness
	calc->SetVarsMap(var_map);

	//setup input data
	std::vector<double> x = {1,2,3,4,5,6,7,8,9,10};
	std::vector<double> y = {2,5,10,17,26,37,50,65,82,101};
	//Setup GAEvaulate
	GAEvaluate* eval = new GAEvaluate(calc); //Evaluate
	eval->SetX(x);
	eval->SetY(y);

	// setup tree generator
	SubTreeGenerator* generator = new SubTreeGenerator(vars, constants, funcs, func_map); // tree/sub tree generator


	//Setup GaOperators
	GAOperators* operators = new GAOperators(generator);// opreators: mutation,crossover


	// setup GAExecuter
	GAExecuter* executer = new GAExecuter(operators); // executer


	//create population
	std::vector<Chromosome*>* data = new std::vector<Chromosome*>(); // vector of first population
	const uint to_gen = 250;
	const uint min_dep = 2;
	const uint max_dep = 4;
	for (uint i = 0; i < to_gen; ++i)
	{
		data->push_back(new Chromosome(generator->GenerateNewTree(min_dep, max_dep))); // generate random three
	}

	// setup GASelector
	GASelector* selector = new GASelector(data, eval); // selector
	selector->SetChoseSize(8); // It must be <= pop_size/2; Because we select (for example 10) parents, and 10 induviduals to delete from the population; 
	selector->SetCrossoverProbability(crossove_prob); // set crossover probability

	//setup GAWorker
	GAWorker* worker = new GAWorker(data,crossove_prob); // some logic of alghorithm.


	worker->SetExecuter(executer);
	worker->SetSelector(selector);

	auto iter_b = data->begin();
	while (iter_b < data->end()) // write fitness of each induvidual
	{
		cout << "Eval: " << eval->Eval(*iter_b) << endl;
		iter_b++;
	}

	for (int i = 0; i < 1000; ++i) // execute 1000 times
	{
		worker->ExecuteOne();
		//cout << *worker << endl;
		
		auto dat = worker->GetData();
		auto iter = dat->begin();
		double avg = 0;
		while (iter < dat->end()) // find avg fitness for each iteration
		{
			avg += eval->Eval(*iter);
			iter++;
		}
		avg /= 100;
		cout << "avg fitness: " << avg << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}
	//worker->ExecuteMany(100);
	//cout << *worker << endl;

	auto dat = worker->GetData();

	auto iter = dat->begin();
	while (iter < dat->end()) // write fitness of each induvidual after
	{
		cout << "Eval: " << eval->Eval(*iter) << endl;
		iter++;
	}
	//cout << *worker;
	delete worker;

	system("pause");

	return 0;
}


