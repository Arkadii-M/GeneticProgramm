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

}

void GASelector::MakeSelection()
{
	this->CalculateFitness();
	this->CalculateProbabilities();
	this->ClearData();
	this->SelectParents();
	this->SelectToDie();

	this->CopyParents();
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
	//delete this->parents; // make clear func
	//this->parents = new std::vector<Chromosome*>();
	double r = 0.0;
	uint chosen = 0;
	while (chosen < this->chose_size)
	{
		for (int i = 0; i < this->data->size(); ++i)
		{
			r = (double)rand() / RAND_MAX; // rand == 0.0 ???????

			if (r < this->selection_prob[i] && !ParentsOrToDieHasChromosome(data->at(i)))
			{
				//this->parents->push_back(new Chromosome(data->at(i)->GetData()));
				this->parents->push_back(this->data->at(i));
				chosen++;
				if (chosen == this->chose_size)
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
		for (int i = 0; i < this->data->size(); ++i)
		{
			r = (double)rand() / RAND_MAX; // always r == 0.0 ??????? why?

			if (r < this->die_prob[i] && !ParentsOrToDieHasChromosome(data->at(i)))
			{
				this->to_die->push_back(this->data->at(i));
				chosen++;
				if (chosen == this->chose_size)
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

	//this->to_crossove = new  std::vector<std::pair<Chromosome*, Chromosome*>>();
	//this->to_mutate = new std::vector<Chromosome*>();


	auto to_cross =std::pair<Chromosome*, Chromosome*>();

	double r = 0.0;


	bool cross_added = false;
	while (iter < this->parents->end())
	{
		cross_added = false;
		r = (double)rand() / RAND_MAX;
		if (r < this->p_cross)
		{
			to_cross.first = *iter;
			iter++;
			while (iter < this->parents->end())
			{
				r = (double)rand() / RAND_MAX;
				if (r < this->p_cross)
				{
					to_cross.second = *iter;
					this->to_crossove->push_back(to_cross);
					cross_added = true;
					break;
				}
				else
				{
					this->to_mutate->push_back(*iter);
				}
				iter++;
			}
			if (!cross_added)
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

void GASelector::CalculateFitness()
{
	this->chrom_fitness.clear();
	double total_fitness = 0.0;
	double fitness = 0.0;
	auto iter = this->data->begin();
	while (iter < this->data->end())
	{
		fitness = this->evaluate->Eval(*iter);
		//fitness = this->Eval(*iter, this->y, this->calc);
		this->chrom_fitness.push_back(fitness);
		total_fitness += fitness;
		iter++;
	}

	this->CurrentTotalFitness = total_fitness;
}

void GASelector::CalculateProbabilities()
{
	auto iter = this->chrom_fitness.begin();

	while (iter < this->chrom_fitness.end())
	{
		this->selection_prob.push_back(*iter / this->CurrentTotalFitness);
		this->die_prob.push_back(1-(*iter / this->CurrentTotalFitness));
		iter++;
	}
}

void GASelector::ClearData()
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

void GASelector::CopyParents()
{
	auto copy = new std::vector<Chromosome*>();
	auto iter = this->parents->begin();
	while (iter < this->parents->end())
	{
		copy->push_back(new Chromosome(new Tree(*(*iter)->GetData())));
		iter++;
	}
	delete this->parents; // 
	this->parents = copy;

}

bool GASelector::ParentsOrToDieHasChromosome(Chromosome* chr)
{
	auto pIter = this->parents->begin();
	while (pIter < this->parents->end())
	{
		if (chr == (*pIter)) // something wrong
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



std::vector<Chromosome*>* GASelector::GetForMutation()
{
	return this->to_mutate;
}