#include "Node.h"

Node::Node(bool terminate, std::string val, Node* left, Node* right):
	is_terminate(terminate),
	value(val),
	left_son(left),
	right_son(right),
	order_number(0)
{
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
