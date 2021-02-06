#pragma once
#include <vector>
#include "Chromosome.h"
#include "SubTreeGenerator.h"
#include "GAOperators.h"
#ifndef GA_EXECUTER
#define GA_EXECUTER
typedef unsigned int uint;
typedef void (*MutateFunc)(Chromosome*, SubTreeGenerator*);
typedef void (*CrossoveFunc)(Chromosome*, Chromosome*);
class GAExecuter
{
private:
	std::vector<Chromosome*>* to_mutation;
	std::vector<std::pair<Chromosome*, Chromosome*>>* to_crossover;

	GAOperators* operators;

public:
	GAExecuter(GAOperators* operators);

	void SetForMutation(std::vector<Chromosome*>* to_mutation);

	void SetForCrossover(std::vector<std::pair<Chromosome*, Chromosome*>>* to_crossover);

	void Execute();

};

#endif