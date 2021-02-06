#include "SubTreeGenerator.h"
#include "Chromosome.h"
#pragma once
#ifndef GA_OPERATORS
#define GA_OPERATORS

class GAOperators
{
private:

	SubTreeGenerator* generator;


public:
	GAOperators(SubTreeGenerator* generator);
	~GAOperators();


	void Crossove(Chromosome* chr1, Chromosome* chr2);
	void Mutate(Chromosome* chr);
};

#endif GA_OPERATORS