#include "GAOperators.h"

GAOperators::GAOperators(SubTreeGenerator* generator):
	generator(generator)
{
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

	uint r1 = rand() % (first_count - 1) + 1;
	uint r2 = rand() % (second_count - 1) + 1;

	Node* node1 = first->GetNodeAtPos(r1);
	Node* node2 = second->GetNodeAtPos(r2);

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

	Node* random = this->generator->GenerateSubTree(1, 2); // Generate random subtree here

	tree->SetAndDeleteOldAtPos(random, r);
	tree->NumerateNodes();
}
