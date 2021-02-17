#include "GASelector.h"

GASelector::GASelector(std::vector<Chromosome*>* data, GAEvaluate* evaluate):
	data(data),
	parents(nullptr),
	to_die(nullptr),
	to_crossove(nullptr),
	to_mutate(nullptr),
	p_mut(0),
	p_cross(0),
	CurrentTotalFitness(0),
	evaluate(evaluate),
	chose_size(0)


{
	random = Random();
}

void GASelector::MakeSelection()
{
	this->CalculateFitness();
	this->CalculateProbabilities();
	this->ClearData();
	this->SelectParents();
	this->SelectToDie();

	this->CopyParents(); // copy data,pointers used.
	this->SelectForMutationAndCrossover();

}


uint GASelector::GetPopSize()
{
	return this->data->size();
}

void GASelector::SetChoseSize(uint size)
{
	this->chose_size = size;
}

void GASelector::SelectParents()
{
	auto iter = this->data->begin();

	double r = 0.0;
	uint chosen = 0;
	while (chosen < this->chose_size) // we need to find exactly chose_size induviduals
	{
		for (int i = 0; i < this->data->size(); ++i)
		{
			r = random.GenerateDouble();
			//if (r < this->selection_prob[i] && !ParentsOrToDieHasChromosome(data->at(i))) //
			if (r < this->selection_prob[i] && !InParents(data->at(i))) //
			{
				this->parents->push_back(this->data->at(i));
				chosen++;
				if (chosen == this->chose_size) // find enough induviduals
				{
					break;
				}
			}

		}

	}

}

void GASelector::SelectToDie()
{
	auto iter = this->data->begin();
	double r = 0.0;
	uint chosen = 0;
	while (chosen < this->chose_size)
	{
		for (int i = 0; i < this->data->size(); ++i)// we need to find exactly chose_size induviduals
		{
			r = random.GenerateDouble();
			//if (r < this->die_prob[i] && !ParentsOrToDieHasChromosome(data->at(i)))
			if (r < this->die_prob[i] && !this->InDie(data->at(i)))
			{
				this->to_die->push_back(this->data->at(i));
				chosen++;
				if (chosen == this->chose_size)// find enough induviduals
				{
					break;
				}
			}

		}

	}
}

std::vector<std::pair<Chromosome*, Chromosome*>>* GASelector::GetForCrossover()
{
	return this->to_crossove;
}

std::vector<Chromosome*>* GASelector::GetToDie()
{
	return this->to_die;
}

std::vector<Chromosome*>* GASelector::GetParents()
{
	return this->parents;
}

void GASelector::SelectForMutationAndCrossover()
{

	auto iter = this->parents->begin();

	auto to_cross =std::pair<Chromosome*, Chromosome*>();

	double r = 0.0;


	bool cross_added = false;
	while (iter < this->parents->end())
	{
		cross_added = false;
		r = random.GenerateDouble();
		if (r < this->p_cross)
		{
			to_cross.first = *iter; // we find first induvidual for crossover
			iter++;

			while (iter < this->parents->end()) // there we try to find the pair to crossover
			{
				r = random.GenerateDouble();
				if (r < this->p_cross)
				{
					to_cross.second = *iter;
					this->to_crossove->push_back(to_cross); // found second induvidual for crossover
					cross_added = true;
					break;
				}
				else // if we don't select this induvidual to crossover we add this to mutation
				{
					this->to_mutate->push_back(*iter);
				}
				iter++;
			}
			if (!cross_added) // if we can't find pair we add selected induvidual to mutation.
			{
				this->to_mutate->push_back(to_cross.first);
			}

		}
		else
		{
			this->to_mutate->push_back(*iter);
		}
		if (iter == this->parents->end())
		{
			break;
		}
		iter++;
	}

}



void GASelector::SetCrossoverProbability(double prob)
{
	this->p_cross = prob;
}

void GASelector::SetData(std::vector<Chromosome*>* data)
{
	this->data = data;
}

void GASelector::CalculateFitness() // calculate fitness fo each induvidual and total fitness
{
	this->chrom_fitness.clear();
	double total_fitness = 0.0;
	double fitness = 0.0;
	auto iter = this->data->begin();
	while (iter < this->data->end())
	{
		fitness = this->evaluate->Eval(*iter);
		this->chrom_fitness.push_back(fitness);
		total_fitness += fitness;
		iter++;
	}

	this->CurrentTotalFitness = total_fitness;
}

void GASelector::CalculateProbabilities() // calculate proportional probabilities
{
	auto iter = this->chrom_fitness.begin();

	while (iter < this->chrom_fitness.end())
	{
		//We try to find the minimum.
		// for example total_prob = -100,induvidual_prob = -3
		// then selection probability is 1 - (-3)/(-100) =1 - 0.03 = 0.97
		//and die probability is (-3)/(-100) = 0.03

		this->selection_prob.push_back(1.0 - (*iter / this->CurrentTotalFitness)); 
		this->die_prob.push_back((*iter / this->CurrentTotalFitness));
		iter++;
	}
}

void GASelector::ClearData() // delete an old data
{
	if (this->parents != nullptr)
	{
		delete this->parents;
	}
	if (this->to_die != nullptr)
	{
		delete this->to_die;
	}
	if (this->to_crossove != nullptr)
	{
		delete this->to_crossove;
	}
	if (this->to_mutate != nullptr)
	{
		delete this->to_mutate;
	}
	this->parents = new std::vector<Chromosome*>();
	this->to_die = new std::vector<Chromosome*>();

	this->to_crossove = new  std::vector<std::pair<Chromosome*, Chromosome*>>();
	this->to_mutate = new std::vector<Chromosome*>();

}

void GASelector::CopyParents() // make copy
{
	auto copy = new std::vector<Chromosome*>();
	auto iter = this->parents->begin();
	while (iter < this->parents->end())
	{
		copy->push_back(new Chromosome(new Tree(*(*iter)->GetData())));
		iter++;
	}
	delete this->parents;
	this->parents = copy;

}
/*
bool GASelector::ParentsOrToDieHasChromosome(Chromosome* chr) // find if induvidual already selected for parents or for die
{
	auto pIter = this->parents->begin();
	while (pIter < this->parents->end())
	{
		if (chr == (*pIter))
		{
			return true;
		}
		pIter++;
	}

	auto dIter = this->to_die->begin();
	while (dIter < this->to_die->end())
	{
		if (chr == (*dIter))
		{
			return true;
		}
		dIter++;
	}
	return false;
}
*/

bool GASelector::InParents(Chromosome* chr)
{
	auto pIter = this->parents->begin();
	while (pIter < this->parents->end())
	{
		if (chr == (*pIter))
		{
			return true;
		}
		pIter++;
	}
	return false;
}

bool GASelector::InDie(Chromosome* chr)
{
	auto dIter = this->to_die->begin();
	while (dIter < this->to_die->end())
	{
		if (chr == (*dIter))
		{
			return true;
		}
		dIter++;
	}
	return false;
}



std::vector<Chromosome*>* GASelector::GetForMutation()
{
	return this->to_mutate;
}