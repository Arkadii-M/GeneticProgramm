#include "Tree.h"


Tree::Tree(uint min_depth, uint max_depth, Node* root):
	max_depth(max_depth),
	min_depth(min_depth),
	root(root),
	depth(0),
	total_nodes(0)
{
}

Tree::Tree(const Tree& tree):
	min_depth(tree.min_depth),
	max_depth(tree.max_depth),
	depth(tree.depth),
	total_nodes(tree.total_nodes)
{
	this->root =new Node(*tree.root);
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
	this->total_nodes = this->NumeratePostOrder(this->root,1,0)-1;  // -1 because the last returns (num+1)
}

void Tree::SetNodeAtPos(Node* node, uint pos)
{
	this->SetNodePostOrder(this->root, node, pos);
	//this->NumerateNodes();

}
void Tree::SetAndDeleteOldAtPos(Node* node, uint pos)
{
	this->SetAndDeleteOldPostOrder(this->root, node, pos);
	//this->NumerateNodes();
}
bool Tree::SetNodePostOrder(Node* current, Node* to_set, uint pos)
{
	if (current == nullptr) { return false; }
	if (current->GetNum() == pos)
	{
		return true;
	}

	if (SetNodePostOrder(current->GetLeftSon(), to_set, pos))
	{
		current->SetLeftSon(to_set);
		return false;
	}

	if (SetNodePostOrder(current->GetRightSon(), to_set, pos))
	{
		current->SetRightSon(to_set);
		return false;
	}

	return false;
}

bool Tree::SetAndDeleteOldPostOrder(Node* current, Node* to_set, uint pos)
{
	if (current == nullptr) { return false; }
	if (current->GetNum() == pos)
	{
		delete current;
		return true;
	}

	if (SetAndDeleteOldPostOrder(current->GetLeftSon(), to_set, pos))
	{
		current->SetLeftSon(to_set);
		return false;
	}

	if (SetAndDeleteOldPostOrder(current->GetRightSon(), to_set, pos))
	{
		current->SetRightSon(to_set);
		return false;
	}

	return false;
}

Node* Tree::GetNodeAtPos(uint pos)
{
	return this->GetNodePostOrder(this->root,pos);
}

uint Tree::NumeratePostOrder(Node* node,uint num, uint depth)
{
	if (node == nullptr) { return num; }

	num =NumeratePostOrder(node->GetLeftSon(),num,depth+1);
	num = NumeratePostOrder(node->GetRightSon(),num,depth+1);

	node->SetNum(num);
	node->SetDepth(depth);
	return (num + 1);
}

Node* Tree::GetNodePostOrder(Node* node,uint pos)
{
	if (node == nullptr) { return nullptr; }

	if (node->GetNum() == pos)
	{
		return node;
	}

	Node* left = GetNodePostOrder(node->GetLeftSon(), pos);
	if ( left!= nullptr)
	{
		return left;
	}
	Node* right = GetNodePostOrder(node->GetRightSon(), pos);
	if (right!= nullptr)
	{
		return right;
	}

	return nullptr;
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
	this->depth = this->CalculateDepth(this->root, 0);
	return this->depth;
}

uint Tree::GetTotalNodes()
{
	this->NumerateNodes();
	return this->total_nodes;
}

uint Tree::CalculateDepth(Node * node, uint depth)
{
	if (node == nullptr) { return depth-1; }

	uint left = CalculateDepth(node->GetLeftSon(), depth+1);
	uint right = CalculateDepth(node->GetRightSon(), depth+1);

	return std::max(left, right);
}