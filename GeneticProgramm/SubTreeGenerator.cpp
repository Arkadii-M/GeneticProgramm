#include "SubTreeGenerator.h"
#include <time.h>


SubTreeGenerator::SubTreeGenerator(
	std::vector<std::string> variables,
	std::vector<std::string> constants,
	std::vector<std::string> functions,
	std::map<std::string, unsigned int> func_op_count,
	Tree* tree) :
	tree(tree),
	variables(variables),
	constants(constants),
	functions(functions),
	functions_operator_count(func_op_count),
	depth(0)
{
	if (tree != nullptr)
	{
		this->max_depth = tree->GetMaxDepth();
		this->min_depth = tree->GetMinDepth();
	}
	else
	{
		this->max_depth = 0;
		this->min_depth = 0;
	}
}

SubTreeGenerator::~SubTreeGenerator()
{
	this->tree = nullptr;
}


Tree* SubTreeGenerator::GenerateNewTree(uint min_depth, uint max_depth)
{
	this->max_depth = max_depth;
	this->min_depth = min_depth;

	this->tree = new Tree(min_depth, max_depth);

	this->tree->SetRoot(this->GenerateTree());
	this->tree->SetDepth(this->depth);


	return this->tree;
}

Node* SubTreeGenerator::GenerateSubTree(uint depth)
{
	return this->RandTree(depth);
}

Node* SubTreeGenerator::GenerateSubTree(uint min_depth, uint max_depth)
{
	Node* subtree = nullptr;
	uint depth = this->min_depth + (int)(rand() % (this->max_depth - this->min_depth + 1)); // rand between min_depth and max_depth

	uint ltc = depth;

	subtree = this->RandTree(ltc);

	return subtree;
}

Node* SubTreeGenerator::GenerateTree()
{
	Node* subtree = nullptr;
	this->depth = this->min_depth +  (int) ( rand() % (this->max_depth - this->min_depth +1) ); // rand between min_depth and max_depth

	uint ltc = this->depth;

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
		double r = ((double)rand() / (RAND_MAX));
		if (r < 1)// in sheets there is r == 1
		{
			//create functional node
			return CreateFunctionalNode(ltc);
		}
		else
		{

			uint k = this->constants.size() + this->functions.size() + this->variables.size();
			uint ran = (rand() %(k)) + 1;
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
	uint r = (rand() % (this->variables.size() + this->constants.size())) + 1; // generate random value from 1 to var_count + const_count
	std::string val = std::string();

	if (r <= this->variables.size()) // if generated is not in vars range then select from the const
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
	uint r = (rand() %(this->functions.size())) + 1;
	r = r - 1;
	std::string func = this->functions.at(r);
	node = new Node(false,func);

	node->SetLeftSon(this->RandTree(ltc - 1));

	if (this->functions_operator_count.at(func) == 2) // if current function takes two parametres
	{
		node->SetRightSon(this->RandTree(ltc - 1));
	}

	return node;
}
