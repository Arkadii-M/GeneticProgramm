#include "Chromosome.h"

Chromosome::Chromosome(Tree* tree):
	data(tree),
	is_calculated(false),
	fitness(0.0)
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

bool Chromosome::IsCalculated()
{
	return this->is_calculated;
}

bool Chromosome::SetCalculated(bool calc)
{
	return this->is_calculated = calc;
}

void Chromosome::SetFitness(double fitness)
{
	this->fitness = fitness;
}

double Chromosome::GetFitness()
{
	return this->fitness;
}
