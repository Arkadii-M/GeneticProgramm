#include "Calculate.h"

Calcluate::Calcluate(std::vector<std::string> variables,
	std::vector<std::string> constants,
	std::vector<std::string> functions,
	std::map<std::string, unsigned int> func_op_count,
	std::map<std::string, SFunc> single_functions_map,
	std::map<std::string, DFunc> double_functions_map):
	variables(variables),
	constants(constants),
	functions(functions),
	functions_operator_count(func_op_count),
	var_map(var_map),
	single_functions_map(single_functions_map),
	double_functions_map(double_functions_map)
{

}

void Calcluate::SetVarsMap(std::map<std::string, double> var_map)
{
	this->var_map = var_map;
}

void Calcluate::SetVarValue(std::string var, double value)
{
	bool has_in_vars = false;
	auto iter = this->variables.begin();
	while (iter < this->variables.end())
	{
		if (*iter == var)
		{
			has_in_vars = true;
			break;
		}
		iter++;
	}

	if (!has_in_vars)
	{
		this->variables.push_back(var);
	}

	auto found = this->var_map.find(var);
	if (found == this->var_map.end())
	{
		this->var_map.insert(std::pair<std::string, double>(var, value));
		return;
	}
	(*found).second = value;
}

double Calcluate::Calc(std::string func, std::string op)
{
	double res = 0.0;
	double param = 0.0;
	SFunc pFunc = this->single_functions_map.at(func);

	bool found = false;
	auto it = this->variables.begin();

	while (it < this->variables.end()) // if op is variable it finds the mapped value 
	{
		if (*it == op)
		{
			param = this->var_map.at(op);
			found = true;
			break;
		}

		it++;
	}

	if (!found)// if op is not a variable it's a value.
	{
		// convert string to double
		param = StringToDouble(op);
	}

	res = pFunc(param); // calculate the function
	return res;
}

double Calcluate::Calc(std::string func, std::string left, std::string right)
{
	double res = 0.0;
	double param1 = 0.0;
	double param2 = 0.0;
	DFunc pFunc = this->double_functions_map.at(func);

	bool found1 = false;
	bool found2 = false;
	auto it = this->variables.begin();

	while (it < this->variables.end())
	{
		if (*it == left)
		{
			param1 = this->var_map.at(left);
			found1 = true;
		}
		if (*it == right)
		{
			param2 = this->var_map.at(right);
			found2 = true;
		}
		if (found1 && found2)
		{
			break;
		}

		it++;
	}

	if (!found1)
	{
		// convert string to double
		param1 = StringToDouble(left);
	}
	if (!found2)
	{
		// convert string to double
		param2 = StringToDouble(right);
	}

	res = pFunc(param1,param2);

	return res;
}

std::string Calcluate::CalcString(std::string func, std::string op)
{
	
	return std::to_string(this->Calc(func, op));
}

std::string Calcluate::CalcString(std::string func, std::string left, std::string right)
{
	return std::to_string(Calc(func,left,right));
}

double Calcluate::StringToDouble(std::string val)
{
	return std::stod(val);
}

double Calcluate::CalcTree(Tree* tree)
{
	return this->StringToDouble(this->PostOrderCalc(tree->GetRoot()));
}

std::string Calcluate::PostOrderCalc(Node* node)
{
	if (node->IsTerminate()) 
	{
		return node->GetValue();
	}
	if (node->GetRightSon() == nullptr) // if it's a operator for one parameter
	{
		return CalcString(node->GetValue(), PostOrderCalc(node->GetLeftSon()));
	}


	return CalcString(
		node->GetValue(),
		PostOrderCalc(node->GetLeftSon())
		,PostOrderCalc(node->GetRightSon())
	);
}
