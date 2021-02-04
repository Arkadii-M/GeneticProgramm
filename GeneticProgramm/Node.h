#include <string>
typedef unsigned int uint;
#pragma once
#ifndef NODE_H
#define NODE_H


class Node
{
private:
	std::string value;

	bool is_terminate;

	Node* left_son;
	Node* right_son;

	uint order_number; // node id after ordering a tree

public:
	Node(bool terminate, std::string val, Node* left = nullptr, Node* right = nullptr);

	Node(const Node& node);

	~Node();

	bool IsTerminate();

	Node* GetLeftSon();
	Node* GetRightSon();

	void SetLeftSon(Node* rhs);
	void SetRightSon(Node* rhs);


	std::string GetValue();
	void SetValue(std::string val);

	uint GetNum();
	void SetNum(uint num);



};


#endif