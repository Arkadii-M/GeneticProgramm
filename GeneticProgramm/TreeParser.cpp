#include "TreeParser.h"

TreeParser::TreeParser(std::vector<std::string> variables, std::vector<std::string> constants, std::vector<std::string> functions):
	variables(variables),
	constants(constants),
	functions(functions),
	calc(nullptr)
{
}

void TreeParser::SetCalculator(Calcluate* calc)
{
	this->calc = calc;
}

std::string TreeParser::Parse(Tree* tree)
{
	return this->ParseNode(tree->GetRoot());
}

void TreeParser::Simplify(Tree* tree)
{
	this->SimplifyNode(tree->GetRoot());
}

std::string TreeParser::ParseNode(Node* node)
{
	if (node->IsTerminate())
	{
		return node->GetValue();
	}

	if (node->GetRightSon() == nullptr)
	{
		return node->GetValue() +"("+ParseNode(node->GetLeftSon())+")";
	}

	return ParseNode(node->GetLeftSon())+ " " + node->GetValue() + " " + ParseNode(node->GetRightSon());
}

bool TreeParser::SimplifyNode(Node* node)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->IsTerminate())
	{
		if (!IsInVars(node->GetValue()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool simp_left = SimplifyNode(node->GetLeftSon());
	if (node->GetRightSon() == nullptr)
	{
		if (simp_left)
		{
			node->SetValue(std::to_string(this->calc->CalcNode(node)));
			node->SetTerminate(true);
			delete node->GetLeftSon();
			node->SetLeftSon(nullptr);
			return true;
		}
	}
	bool simp_right = SimplifyNode(node->GetRightSon());
	if ( simp_left && simp_right)
	{
		node->SetValue(std::to_string(this->calc->CalcNode(node)));
		node->SetTerminate(true);

		delete node->GetLeftSon();
		node->SetLeftSon(nullptr);

		delete node->GetRightSon();
		node->SetRightSon(nullptr);
		return true;
	}


	return false;
}

bool TreeParser::IsInVars(std::string val)
{
	auto iter = this->variables.begin();
	while (iter < this->variables.end())
	{
		if (*iter == val)
		{
			return true;
		}
		iter++;
	}
	return false;
}

/*

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
		, PostOrderCalc(node->GetRightSon())
	);
}
*/