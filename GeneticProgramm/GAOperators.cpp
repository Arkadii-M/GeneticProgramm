#include "GAOperators.h"
#include <iostream>

GAOperators::GAOperators(SubTreeGenerator* generator):
	generator(generator)
{
	random = Random();
}

GAOperators::~GAOperators()
{
	delete generator;
}

void GAOperators::Crossove(Chromosome* chr1, Chromosome* chr2)
{
	Tree* first = chr1->GetData();
	Tree* second = chr2->GetData();

	uint first_count = first->GetTotalNodes();
	uint second_count = second->GetTotalNodes();

	uint r1 = random.GenerateIntInRange(1, first_count - 1); // select random node(not root)
	Node* node1 = first->GetNodeAtPos(r1);

	//
	//There we find the second node. This code need for contlor the tree limits. (Tree depth must be between max_depth and min_depth)
	uint max_depth_find = first->GetMaxDepth() - node1->GetDepth(); // It's maximum size of sub tree which we can insert insted this node (node1 in first tree)

	uint find = this->CalculateSubTreeDepth(node1); // This need to find the second node.

	uint r2 = 0;
	Node* node2 = nullptr;
	while (true)
	{
		r2 = random.GenerateIntInRange(1, second_count - 1);// select random node(not root)
		node2 = second->GetNodeAtPos(r2);
		if ((second->GetMaxDepth()-node2->GetDepth() >= find ) &&    this->CalculateSubTreeDepth(node2) <= max_depth_find)
		{
			break;// the required node founded.
		}
	}

	first->SetNodeAtPos(node2, r1); // don't numerate there, because after swap links the second three is numerate wrong.
	second->SetNodeAtPos(node1, r2);

	first->NumerateNodes();
	second->NumerateNodes();
}

void GAOperators::Mutate(Chromosome* chr)
{
	Tree* tree = chr->GetData();

	uint count = tree->GetTotalNodes();
	

	uint r = random.GenerateIntInRange(1, count - 1);// select random node(not root)
	Node* node = tree->GetNodeAtPos(r);
	uint current_node_depth = node->GetDepth();

	Node* random = this->generator->GenerateSubTree(0, tree->GetMaxDepth() - current_node_depth); // Generate random subtree here

	tree->SetAndDeleteOldAtPos(random, r);
	tree->NumerateNodes();
}

uint GAOperators::CalculateSubTreeDepth(Node* subtree)
{
	return this->CalcDepth(subtree, 0);
}

uint GAOperators::CalcDepth(Node* node, uint depth)
{
	if (node == nullptr) { return depth - 1; }

	uint left = CalcDepth(node->GetLeftSon(), depth + 1);
	uint right = CalcDepth(node->GetRightSon(), depth + 1);

	return std::max(left, right);
}
