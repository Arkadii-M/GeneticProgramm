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
	Tree(const Tree& tree);
	~Tree();

	void SetRoot(Node* root);
	Node* GetRoot();
	void SetDepth(uint depth);
	void NumerateNodes();

	void SetNodeAtPos(Node* node, uint pos); // Attention! This function don't delete an old node!

	void SetAndDeleteOldAtPos(Node* node, uint pos); // Attention! This function delete an old node!

	Node* GetNodeAtPos(uint pos);
private:
	uint NumeratePostOrder(Node* node,uint num,uint depth); // numerate the nodes by post ordering

	Node* GetNodePostOrder(Node* node,uint pos);


	bool SetNodePostOrder(Node* current,Node* to_set, uint pos);
	bool SetAndDeleteOldPostOrder(Node* current, Node* to_set, uint pos);
public:

	uint GetMaxDepth();
	uint GetMinDepth();
	uint GetCurrentDepth();
	uint GetTotalNodes();
private:
	uint CalculateDepth(Node * node,uint depth);
};


#endif // !TREE_H
