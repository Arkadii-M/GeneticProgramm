
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>


#include "Calculate.h"
#include "RedefinedOperators.h"
#include "GAEvaluate.h"
#include "GAExecuter.h"
#include "GAOperators.h"
#include "GASelector.h"
#include "GAWorker.h"
#include "Random.h"
#include "TreeParser.h"
using namespace std;

# define M_PIl 3.141592653589793238462643383279502884L /* pi */

double y_func(double x)
{
	/*
	if (abs(x + 1) < DBL_EPSILON)
	{
		return (exp(DBL_EPSILON) +1) / DBL_EPSILON;
	}
	return (exp(x + 1)+1) / (x + 1);
	*/
	if (abs(x) < DBL_EPSILON)
	{
		x = DBL_EPSILON;
		return (sin(x) - x * cos(x)) / (x * x);
	}
	return (sin(x) - x * cos(x)) / (x * x);
}

double k_func(double x, double t)
{
	//return exp(x*t);
	return sin(x * t);
}


int main()
{
	//srand(time(nullptr));

	cout << "test" << endl;



	double crossove_prob = 0.73;
	double mutate_prob = 0.97;
	std::vector<std::string> vars = std::vector<std::string>(); // vars
	vars.push_back("x");

	std::vector<std::string> constants = std::vector<std::string>();// constants
	
	
	constants.push_back("1");
	constants.push_back("0");
	constants.push_back("-1");
	
	


	std::vector<std::string> funcs = std::vector<std::string>(); // functions
	funcs.push_back("*");
	funcs.push_back("+");
	funcs.push_back("/");
	funcs.push_back("-");
	funcs.push_back("abs");
	funcs.push_back("cos");
	funcs.push_back("sin");
	funcs.push_back("exp");
	//funcs.push_back("tg");
	//funcs.push_back("ctg");

	// find cos(x) ^ 3 + cos(x ^ 2)
	std::map<std::string, unsigned int> func_map = { {"+",2},{"-",2} ,{"*",2},{"abs",1},{"/",2},{"cos",1},{"sin",1},{"tg",1},{"ctg",1},{"pow",2},{"exp",1} }; // parameters count of function

	std::map<std::string, double> var_map = { {"x",0},}; // set value of vars

	std::map<std::string, SFunc> single_functions_map = { {"abs",RedefOp::myabs},{"cos",RedefOp::cosinus},{"sin",RedefOp::sinus},{"tg",RedefOp::tangens},{"ctg",RedefOp::cotangens},{"exp",RedefOp::myexp} }; // functions with single parameter

	std::map<std::string, DFunc> double_functions_map = { {"+",RedefOp::myplus},{"-",RedefOp::myminus},{"*",RedefOp::mymult},{"/",RedefOp::mydiv},{"pow",RedefOp::power} };// functions with two parameters

	// setup calculator
	Calcluate* calc = new Calcluate(vars, constants, funcs, func_map, single_functions_map, double_functions_map); // this calculate tree fitness
	calc->SetVarsMap(var_map);

	//Setup GAEvaulate
	GAEvaluate* eval = new GAEvaluate(calc); //Evaluate

	double x_a = -5;
	double x_b = 5;
	int x_steps = 100;

	double int_a = 0;
	double int_b = 2;
	int int_steps = 300;
	eval->SetKFunc(k_func);
	eval->SetYFunc(y_func);
	eval->SetXInterval(x_a,x_b,x_steps);
	eval->SetIntegralLimits(int_a,int_b,int_steps);



	// setup tree generator
	SubTreeGenerator* generator = new SubTreeGenerator(vars, constants, funcs, func_map); // tree/sub tree generator


	//Setup GaOperators
	GAOperators* operators = new GAOperators(generator);// opreators: mutation,crossover


	// setup GAExecuter
	GAExecuter* executer = new GAExecuter(operators); // executer

	//
	TreeParser parser = TreeParser(vars,constants,funcs);
	parser.SetCalculator(calc);
	//
	//create population
	std::vector<Chromosome*>* data = new std::vector<Chromosome*>(); // vector of first population
	const uint to_gen =1000;
	const uint min_dep =0;
	const uint max_dep = 8;
	for (uint i = 0; i < to_gen; ++i)
	{
		data->push_back(new Chromosome(generator->GenerateNewTree(min_dep, max_dep))); // generate random three

	}
	// setup GASelector
	GASelector* selector = new GASelector(data, eval); // selector
	selector->SetChoseSize(400); // It must be <= pop_size/2; Because we select (for example 10) parents, and 10 induviduals to delete from the population; 
	selector->SetCrossoverProbability(crossove_prob); // set crossover probability
	selector->SetMutateProbability(mutate_prob);

	//setup GAWorker
	GAWorker* worker = new GAWorker(data,crossove_prob); // some logic of alghorithm.
	worker->SetExecuter(executer);
	worker->SetSelector(selector);
	/*
	auto iter_b = data->begin();
	while (iter_b < data->end()) // write fitness of each induvidual
	{
		cout << "Eval: " << eval->Eval(*iter_b) << endl;
		iter_b++;
	}
	*/
	double avg = 0.0;
	bool find_bigger = false;
	Tree* tr = nullptr;
	for (int i = 0; i < 1000; ++i) // execute 1000 times
	{
		worker->ExecuteOne();
		//cout << *worker << endl;
		
		auto dat = worker->GetData();
		auto iter = dat->begin();
		double max = -999999999999999999;
		avg = 0.0;
		while (iter < dat->end()) // find avg fitness for each iteration
		{
			auto ev = (*iter)->GetFitness();
			avg += ev;
			if (ev > max)
			{
				max = ev;
				find_bigger = true;
				tr = (*iter)->GetData();
			}
			iter++;
		}
		cout << "Iteration: " << i << endl;
		cout << "max fitness: " << max << endl;
		cout << "Total fitness: " << avg << endl;
		cout << "Avg: " << (avg/ to_gen) << endl;
		if (find_bigger)
		{
			cout << parser.Parse(tr) << endl;
			find_bigger = false;
		}
		cout << "----------------------------------------------------------------------------" << endl;
	}
	//worker->ExecuteMany(100);
	//cout << *worker << endl;

	auto dat = worker->GetData();

	auto iter = dat->begin();
	while (iter < dat->end()) // write fitness of each induvidual after
	{
		cout << "Eval: " << (*iter)->GetFitness() << endl;
		parser.Simplify((*iter)->GetData());
		cout << parser.Parse((*iter)->GetData()) << endl;
		iter++;
	}
	//cout << *worker;
	
	delete worker;
	
	system("pause");

	return 0;
}


