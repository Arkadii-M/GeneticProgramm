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

	std::map<std::string, std::vector<double>> var_map_many;
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

	void SetVarInterval(std::string var, std::vector<double> values);

private:
	double Calc(std::string op);
	std::vector<double> CalcMany(std::string op,int size);

	double Calc(std::string func,std::string op); // calculate the function
	std::vector<double> CalcMany(std::string func, std::vector<std::string> op);
	std::vector<double> CalcMany(std::string func, std::vector<double> op);

	double Calc(std::string func, std::string left,std::string right);
	std::vector<double> CalcMany(std::string func, std::vector<std::string> left, std::vector<std::string> right);
	std::vector<double> CalcMany(std::string func, std::vector<double> left, std::vector<double> right);


	std::string CalcString(std::string op);
	std::vector<std::string> CalcStringMany(std::string op,int size);

	std::string CalcString(std::string func, std::string op); // returns calculated value in string representation
	std::vector<std::string> CalcStringMany(std::string func, std::vector<std::string> op);

	std::string CalcString(std::string func, std::string left, std::string right);
	std::vector<std::string> CalcStringMany(std::string func, std::vector<std::string> left, std::vector<std::string> right);


	double StringToDouble(std::string val);
	std::vector<double> StringToDoubleMany(std::vector<std::string> vals);

public:
	double CalcTree(Tree * tree);
	std::vector<double> CalcTreeMany(Tree* tree, int size);
	double CalcNode(Node* node);
private:
	std::string PostOrderCalc(Node* node); // post order the tree and calculate the value

	std::vector<std::string> PostOrderCalcMany(Node * node, int size);

	std::vector<double> PostOrderCalcDoubleMany(Node* node, int size);
};


#endif