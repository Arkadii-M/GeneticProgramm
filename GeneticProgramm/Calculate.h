#pragma once
#include <vector>
#include <map>
#include <string>
#include "Tree.h"
#ifndef CALCULATE_H
#define CALCULATE_H

typedef double (*SFunc)(double);
typedef double (*DFunc)(double,double);

class Calcluate
{
private:
	std::vector<std::string> variables;
	std::map<std::string, double> var_map; // mapped vars to each value

	std::vector<std::string> constants;
	std::vector<std::string> functions;
	std::map<std::string, unsigned int> functions_operator_count;// for example: abs -1,* -2

	std::map<std::string, SFunc> single_functions_map; // functions with one parameter
	std::map<std::string, DFunc> double_functions_map; // functions with two parameters


public:
	Calcluate(std::vector<std::string> variables,
		std::vector<std::string> constants,
		std::vector<std::string> functions,
		std::map<std::string, unsigned int> func_op_count,
		std::map<std::string, SFunc> single_functions_map,
		std::map<std::string, DFunc> double_functions_map	);

	void SetVarsMap(std::map<std::string, double> var_map);

	void SetVarValue(std::string var,double value);

private:
	double Calc(std::string func,std::string op); // calculate the function
	double Calc(std::string func, std::string left,std::string right);

	std::string CalcString(std::string func, std::string op); // returns calculated value in string representation
	std::string CalcString(std::string func, std::string left, std::string right);


	double StringToDouble(std::string val);


public:
	double CalcTree(Tree * tree);
private:
	std::string PostOrderCalc(Node* node); // post order the tree and calculate the value
};


#endif