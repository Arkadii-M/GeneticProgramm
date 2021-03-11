#include "Node.h"

Node::Node(bool terminate, std::string val, Node* left, Node* right):
	is_terminate(terminate), //error
	value(val),
	left_son(left),
	right_son(right),
	order_number(0),
	depth(0)
{
}

Node::Node(const Node& node):
	is_terminate(node.is_terminate),
	value(node.value),
	order_number(node.order_number),
	depth(node.depth)
{
	if (node.left_son != nullptr)
	{
		this->left_son = new Node(*node.left_son);
	}
	else
	{
		this->left_son = nullptr;
	}

	if (node.right_son != nullptr)
	{
		this->right_son = new Node(*node.right_son);
	}
	else
	{
		this->right_son = nullptr;
	}

}

Node::~Node()
{
	if (left_son != nullptr)
	{
		delete left_son;
	}
	if (left_son != nullptr)
	{
		delete right_son;
	}
}

bool Node::IsTerminate()  
{
	return  this->is_terminate;
}

void Node::SetTerminate(bool param)
{
	this->is_terminate = param;
}

Node* Node::GetLeftSon()  
{
	return this->left_son;
}

Node* Node::GetRightSon()  
{
	return this->right_son;
}

void Node::SetLeftSon(Node* rhs)
{
	this->left_son = rhs;
}

void Node::SetRightSon(Node* rhs)
{
	this->right_son = rhs;
}

std::string Node::GetValue()  
{
	return this->value;
}

void Node::SetValue(std::string val)
{
	this->value = val;
}

uint Node::GetNum()  
{
	return this->order_number;
}

void Node::SetNum(uint num)
{
	this->order_number = num;
}

uint Node::GetDepth()
{
	return this->depth;
}

void Node::SetDepth(uint depth)
{
	this->depth = depth;
}
