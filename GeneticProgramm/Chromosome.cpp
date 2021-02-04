#include "Chromosome.h"

Chromosome::Chromosome(Tree* tree):
	data(tree)
{
}

Tree* Chromosome::GetData()
{
	return this->data;
}