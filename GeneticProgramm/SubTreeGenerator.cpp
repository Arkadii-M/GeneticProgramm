#include "SubTreeGenerator.h"
#include <time.h>


SubTreeGenerator::SubTreeGenerator(
	std::vector<std::string> variables,
	std::vector<std::string> constants,
	std::vector<std::string> functions,
	std::map<std::string, unsigned int> func_op_count) :
	variables(variables),
	constants(constants),
	functions(functions),
	functions_operator_count(func_op_count),
	min_depth(0),
	max_depth(0)
{
	random = Random();
}

SubTreeGenerator::~SubTreeGenerator()
{
}


Tree* SubTreeGenerator::GenerateNewTree(uint min_depth, uint max_depth)
{
	Tree* tree = new Tree(min_depth, max_depth);

	tree->SetRoot(GenerateSubTree(min_depth,max_depth));
	tree->GetCurrentDepth(); // calc tree depth

	return tree;
}

Node* SubTreeGenerator::GenerateSubTree(uint depth)
{
	return this->RandTree(depth);
}

Node* SubTreeGenerator::GenerateSubTree(uint min_depth, uint max_depth)
{
	Node* subtree = nullptr;
	uint depth = random.GenerateIntInRange(min_depth, max_depth);// rand between min_depth and max_depth
	uint ltc = depth;

	this->min_depth = min_depth;
	this->max_depth = max_depth;
	subtree = this->RandTree(ltc);

	return subtree;
}

Node* SubTreeGenerator::RandTree(uint ltc)
{
	if (ltc == 0)
	{
		// create terminal node
		return CreateTerminalNode(ltc);

	}
	if (ltc >= this->min_depth)
	{
		//create functional node
		return CreateFunctionalNode(ltc);
	}
	else
	{
		double r = random.GenerateDouble();
		if (r < 1)// in sheets there is r == 1. If there r < 1 it's works fine.
		{
			//create functional node
			return CreateFunctionalNode(ltc);
		}
		else
		{

			uint k = this->constants.size() + this->functions.size() + this->variables.size();
			uint ran = random.GenerateIntInRange(1, k);

			if (ran < this->functions.size())
			{
				//create functional node
				return CreateFunctionalNode(ltc);
			}
			else
			{
				// create terminal node
				return CreateTerminalNode(ltc);
			}
		}
	}

}

Node* SubTreeGenerator::CreateTerminalNode(uint ltc)
{
	Node* node = nullptr;
	uint r = random.GenerateIntInRange(1, this->variables.size() + this->constants.size());// generate random value from 1 to var_count + const_count
	std::string val = std::string();

	if (r <= this->variables.size()) // if generated number is not in vars range then select it from the constants
	{
		r = r - 1;
		val = this->variables.at(r);
	}
	else
	{

		r = r - this->variables.size()-1;
		val = this->constants.at(r);
	}

	node=  new Node(true, val);
	return node;
}

Node* SubTreeGenerator::CreateFunctionalNode(uint ltc)
{
	Node* node = nullptr;

	uint r = random.GenerateIntInRange(1, this->functions.size());
	r = r - 1; // because the range between 0...size-1
	std::string func = this->functions.at(r);
	node = new Node(false,func);

	node->SetLeftSon(this->RandTree(ltc - 1));

	if (this->functions_operator_count.at(func) == 2) // if current function takes two parametres
	{
		node->SetRightSon(this->RandTree(ltc - 1));
	}

	return node;
}
