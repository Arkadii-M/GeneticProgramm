#include "Chromosome.h"

Chromosome::Chromosome(Tree* tree):
	data(tree)
{
}

Chromosome::~Chromosome()
{
	delete this->data;
}

Tree* Chromosome::GetData()
{
	return this->data;
}