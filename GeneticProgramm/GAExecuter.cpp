#include "GAExecuter.h"

GAExecuter::GAExecuter(MutateFunc mut, CrossoveFunc cross, SubTreeGenerator* gen):
	Mutate(mut),
	Crossove(cross),
	to_mutation(nullptr),
	to_crossover(nullptr),
	gen(gen)

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
		this->Crossove((*cross_it).first, (*cross_it).second);
		cross_it++;
	}


	auto mut_it = this->to_mutation->begin();
	while (mut_it < this->to_mutation->end())
	{
		this->Mutate(*mut_it,this->gen);
		mut_it++;
	}

}
