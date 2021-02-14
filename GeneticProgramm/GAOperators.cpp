#include "GAOperators.h"
#include <iostream>

GAOperators::GAOperators(SubTreeGenerator* generator):
	generator(generator)
{
}

GAOperators::~GAOperators()
{
	delete generator;
}

void GAOperators::Crossove(Chromosome* chr1, Chromosome* chr2) // some errors
{
	Tree* first = chr1->GetData();
	Tree* second = chr2->GetData();

	uint first_count = first->GetTotalNodes();
	uint second_count = second->GetTotalNodes();

	uint r1 = rand() % (first_count - 1) + 1; // Select first randomly
	Node* node1 = first->GetNodeAtPos(r1);

	uint max_depth_find = first->GetMaxDepth() - node1->GetDepth();

	uint find = this->CalculateSubTreeDepth(node1);

	uint r2 = 0;
	Node* node2 = nullptr;
	while (true)
	{
		r2 = rand() % (second_count - 1) + 1;
		node2 = second->GetNodeAtPos(r2);
		if ((second->GetMaxDepth()-node2->GetDepth() >= find ) &&    this->CalculateSubTreeDepth(node2) <= max_depth_find)
		{
			break;
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

	uint r = rand() % (count - 1) + 1;

	Node* node = tree->GetNodeAtPos(r);
	uint current_node_depth = node->GetDepth();

	Node* random = this->generator->GenerateSubTree(0, tree->GetMaxDepth() - current_node_depth); // Generate random subtree here

	tree->SetAndDeleteOldAtPos(random, r);
	tree->NumerateNodes();
	//
	tree->GetCurrentDepth();


	//
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
