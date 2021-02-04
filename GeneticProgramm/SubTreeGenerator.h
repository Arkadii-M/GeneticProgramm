#include "Tree.h"
#include "Node.h"
#include <vector>
#include <random>
#include <string>
#include <map>

typedef unsigned int uint;
#pragma once
#ifndef SUBTREEGENERATOR_H
#define SUBTREEGENERATOR_H

class SubTreeGenerator
{
private:
	uint max_depth;
	uint min_depth;
	uint depth;

	Tree* tree;


	std::vector<std::string> variables;
	std::vector<std::string> constants;
	std::vector<std::string> functions;
	std::map<std::string, unsigned int> functions_operator_count; // for example: abs -1, * - 2

public:
	SubTreeGenerator(std::vector<std::string> variables,
		std::vector<std::string> constants,
		std::vector<std::string> functions,
		std::map<std::string, unsigned int> func_op_count,
		Tree* tree = nullptr);
	~SubTreeGenerator();

	Tree* GenerateNewTree(uint min_depth, uint max_depth);
	Node* GenerateSubTree(uint depth);
	Node* GenerateSubTree(uint min_depth,uint max_depth);
private:
	Node* RandTree(uint ltc);
	Node* CreateTerminalNode(uint ltc);
	Node* CreateFunctionalNode(uint ltc);
	Node* GenerateTree();
};

#endif // !SUBTREEGENERATOR_H
