#include <string>
#include "Tree.h"
#include "Node.h"
#include "Calculate.h"

#pragma once
#ifndef TREE_PARSER_H
#define TREE_PARSER_H


class TreeParser
{
private:
	Calcluate* calc;

	std::vector<std::string> variables;
	std::vector<std::string> constants;
	std::vector<std::string> functions;

public:
	TreeParser(std::vector<std::string> variables, std::vector<std::string> constants, std::vector<std::string> functions);
	void SetCalculator(Calcluate* calc);
	std::string Parse(Tree * tree);
	void Simplify(Tree* tree);


private:

	std::string ParseNode(Node* node);
	bool SimplifyNode(Node* node);

	bool IsInVars(std::string val);
};

#endif // !TREE_PARSER_H

