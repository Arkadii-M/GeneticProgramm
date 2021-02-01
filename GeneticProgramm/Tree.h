#include "Node.h"

typedef unsigned int uint;
#pragma once
#ifndef TREE_H
#define TREE_H

class Tree
{
private:
	Node* root;
	uint max_depth;
	uint min_depth;
	uint depth;
	uint total_nodes;


public:
	Tree(uint min_depht, uint max_depth, Node * root = nullptr);
	~Tree();

	void SetRoot(Node* root);
	Node* GetRoot();
	void SetDepth(uint depth);
	void NumerateNodes();
private:
	uint NumeratePostOrder(Node* node,uint num); // numerate the nodes by post ordering

public:

	uint GetMaxDepth();
	uint GetMinDepth();
	uint GetCurrentDepth();
	uint GetTotalNodes();
};


#endif // !TREE_H
