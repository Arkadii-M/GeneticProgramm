#include "Tree.h"

Tree::Tree(uint min_depth, uint max_depth, Node* root):
	max_depth(max_depth),
	min_depth(min_depth),
	root(root),
	depth(0),
	total_nodes(0)
{
}

Tree::~Tree()
{
	if (this->root != nullptr)
	{
		delete root;
	}
}

void Tree::SetRoot(Node* root)
{
	this->root = root;
}

Node* Tree::GetRoot()
{
	return this->root;
}

void Tree::SetDepth(uint depth)
{
	this->depth = depth;
}

void Tree::NumerateNodes()
{
	this->total_nodes = this->NumeratePostOrder(this->root,1)-1;  // -1 because the last returns (num+1)
}

uint Tree::NumeratePostOrder(Node* node,uint num)
{
	if (node == nullptr) { return num; }
	num =NumeratePostOrder(node->GetLeftSon(),num);
	num = NumeratePostOrder(node->GetRightSon(),num);
	node->SetNum(num);
	return (num + 1);
}

uint Tree::GetMaxDepth()
{
	return this->max_depth;
}

uint Tree::GetMinDepth()
{
	return this->min_depth;
}

uint Tree::GetCurrentDepth()
{
	return this->depth;
}

uint Tree::GetTotalNodes()
{
	return this->total_nodes;
}
