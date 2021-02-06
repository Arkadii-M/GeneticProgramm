#include "GAExecuter.h"

GAExecuter::GAExecuter(GAOperators* operators):
	to_mutation(nullptr),
	to_crossover(nullptr),
	operators(operators)

{
}

void GAExecuter::SetForMutation(std::vector<Chromosome*>* to_mutation)
{
	this->to_mutation = to_mutation;
}

void GAExecuter::SetForCrossover(std::vector<std::pair<Chromosome*, Chromosome*>>* to_crossover)
{
	this->to_crossover = to_crossover;
}

void GAExecuter::Execute()
{
	auto cross_it = this->to_crossover->begin();

	while (cross_it < this->to_crossover->end())
	{
		this->operators->Crossove((*cross_it).first, (*cross_it).second);
		cross_it++;
	}


	auto mut_it = this->to_mutation->begin();
	while (mut_it < this->to_mutation->end())
	{
		this->operators->Mutate(*mut_it);
		mut_it++;
	}

}
