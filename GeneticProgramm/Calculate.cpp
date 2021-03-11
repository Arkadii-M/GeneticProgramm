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

void Calcluate::SetVarValue(std::string var, double value) // set value for variable
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

void Calcluate::SetVarInterval(std::string var, std::vector<double> values)
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

	auto found = this->var_map_many.find(var);
	if (found == this->var_map_many.end())
	{
		this->var_map_many.insert(std::pair<std::string, std::vector<double>>(var, values));
		return;
	}
	(*found).second = values;
}

double Calcluate::Calc(std::string op)
{
	double res = 0.0;
	double param = 0.0;

	bool found = false;
	auto it = this->variables.begin();

	while (it < this->variables.end()) // if op is a variable it finds the mapped value 
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

	res = param;
	return res;
}

std::vector<double> Calcluate::CalcMany(std::string op,int size)
{
	std::vector<double> res;
	std::vector<double> param;

	bool found = false;
	auto it = this->variables.begin();

	while (it < this->variables.end()) // if op is a variable it finds the mapped value 
	{
		if (*it == op)
		{
			param = this->var_map_many.at(op);
			found = true;
			break;
		}

		it++;
	}

	if (!found)// if op is not a variable it's a value.
	{
		// convert string to double
		param = std::vector<double>(size, StringToDouble(op));
	}

	res = param;
	return res;
}

double Calcluate::Calc(std::string func, std::string op)
{
	double res = 0.0;
	double param = 0.0;
	SFunc pFunc = this->single_functions_map.at(func);

	bool found = false;
	auto it = this->variables.begin();

	while (it < this->variables.end()) // if op is a variable it finds the mapped value 
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

std::vector<double> Calcluate::CalcMany(std::string func, std::vector<std::string> op)
{
	std::vector<double> res = std::vector<double>();
	std::vector<double> param;
	SFunc pFunc = this->single_functions_map.at(func);

	bool found = false;
	auto it = this->variables.begin();

	while (it < this->variables.end()) // if op is a variable it finds the mapped value 
	{
		if (*it == op.at(0))
		{
			param = this->var_map_many.at(op.at(0));
			found = true;
			break;
		}

		it++;
	}

	if (!found)// if op is not a variable it's a value.
	{
		// convert string to double
		param = StringToDoubleMany(op);
	}

	auto iter = param.begin();

	while (iter < param.end())
	{
		res.push_back(pFunc(*iter));
		iter++;
	}
	return res;
}
std::vector<double> Calcluate::CalcMany(std::string func, std::vector<double> op)
{
	std::vector<double> res = std::vector<double>();
	std::vector<double> param;
	SFunc pFunc = this->single_functions_map.at(func);

	param = op;

	auto iter = param.begin();

	while (iter < param.end())
	{
		res.push_back(pFunc(*iter));
		iter++;
	}
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

std::vector<double> Calcluate::CalcMany(std::string func, std::vector<std::string> left, std::vector<std::string> right)
{
	std::vector<double> res = std::vector<double>();
	std::vector<double> param1;
	std::vector<double> param2;
	DFunc pFunc = this->double_functions_map.at(func);

	bool found1 = false;
	bool found2 = false;
	auto it = this->variables.begin();

	while (it < this->variables.end())
	{
		if (*it == left.at(0))
		{
			param1 = this->var_map_many.at(left.at(0));
			found1 = true;
		}
		if (*it == right.at(0))
		{
			param2 = this->var_map_many.at(right.at(0));
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
		param1 = StringToDoubleMany(left);
	}
	if (!found2)
	{
		// convert string to double
		param2 = StringToDoubleMany(right);
	}
	auto iter1 = param1.begin();
	auto iter2 = param2.begin();

	while (iter1 < param1.end())
	{
		res.push_back(pFunc(*iter1,*iter2));
		iter1++;
		iter2++;
	}
	return res;
}

std::vector<double> Calcluate::CalcMany(std::string func, std::vector<double> left, std::vector<double> right)
{
	std::vector<double> res = std::vector<double>();
	std::vector<double> param1;
	std::vector<double> param2;
	DFunc pFunc = this->double_functions_map.at(func);

	param1 = left;
	param2 = right;
	auto iter1 = param1.begin();
	auto iter2 = param2.begin();

	while (iter1 < param1.end())
	{
		res.push_back(pFunc(*iter1, *iter2));
		iter1++;
		iter2++;
	}
	return res;
}
std::string Calcluate::CalcString(std::string op)
{
	return std::to_string(this->Calc(op));
}

std::vector<std::string> Calcluate::CalcStringMany(std::string op, int size)
{
	std::vector<std::string> to_ret = std::vector<std::string>();
	auto res = this->CalcMany(op, size);

	auto iter = res.begin();
	while (iter < res.end())
	{
		to_ret.push_back(std::to_string(*iter));
		iter++;
	}
	return to_ret;
}

std::string Calcluate::CalcString(std::string func, std::string op)
{
	
	return std::to_string(this->Calc(func, op));
}

std::vector<std::string> Calcluate::CalcStringMany(std::string func, std::vector<std::string> op)
{
	std::vector<std::string> to_ret = std::vector<std::string>();
	auto res = this->CalcMany(func,op);

	auto iter = res.begin();
	while (iter < res.end())
	{
		to_ret.push_back(std::to_string(*iter));
		iter++;
	}
	return to_ret;
}

std::string Calcluate::CalcString(std::string func, std::string left, std::string right)
{
	return std::to_string(Calc(func,left,right));
}

std::vector<std::string> Calcluate::CalcStringMany(std::string func, std::vector<std::string> left, std::vector<std::string> right)
{
	std::vector<std::string> to_ret = std::vector<std::string>();
	auto res = this->CalcMany(func, left,right);

	auto iter = res.begin();
	while (iter < res.end())
	{
		to_ret.push_back(std::to_string(*iter));
		iter++;
	}
	return to_ret;
}

double Calcluate::StringToDouble(std::string val)
{
	return std::stod(val);
}

std::vector<double> Calcluate::StringToDoubleMany(std::vector<std::string> vals)
{
	std::vector<double> to_ret = std::vector<double>();
	auto iter = vals.begin();
	while (iter < vals.end())
	{
		to_ret.push_back(std::stod(*iter));
		iter++;
	}
	return to_ret;
}

double Calcluate::CalcTree(Tree* tree)
{
	return this->StringToDouble(this->PostOrderCalc(tree->GetRoot()));
}

std::vector<double> Calcluate::CalcTreeMany(Tree* tree,int size)
{
	return this->PostOrderCalcDoubleMany(tree->GetRoot(), size);
	//return this->StringToDoubleMany(this->PostOrderCalcMany(tree->GetRoot(),size));
}

double Calcluate::CalcNode(Node* node)
{
	return this->StringToDouble(this->PostOrderCalc(node));
}

std::string Calcluate::PostOrderCalc(Node* node)
{
	if (node->IsTerminate()) 
	{
		return CalcString(node->GetValue());
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

std::vector<std::string> Calcluate::PostOrderCalcMany(Node* node, int size)
{
	if (node->IsTerminate())
	{
		return CalcStringMany(node->GetValue(),size);
	}
	if (node->GetRightSon() == nullptr) // if it's a operator for one parameter
	{
		return CalcStringMany(node->GetValue(), PostOrderCalcMany(node->GetLeftSon(),size));
	}


	return CalcStringMany(
		node->GetValue(),
		PostOrderCalcMany(node->GetLeftSon(),size)
		, PostOrderCalcMany(node->GetRightSon(),size)
	);
}

std::vector<double> Calcluate::PostOrderCalcDoubleMany(Node* node, int size)
{
	if (node->IsTerminate())
	{
		return CalcMany(node->GetValue(), size);
	}
	if (node->GetRightSon() == nullptr) // if it's a operator for one parameter
	{
		return CalcMany(node->GetValue(), PostOrderCalcDoubleMany(node->GetLeftSon(), size));
	}


	return CalcMany(
		node->GetValue(),
		PostOrderCalcDoubleMany(node->GetLeftSon(), size)
		, PostOrderCalcDoubleMany(node->GetRightSon(), size)
	);
}
