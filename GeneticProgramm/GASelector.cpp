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
	chose_size(0),
	CurrentMaxFitness(0)


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
	/*
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
	*/
	uint chosen = 0;
	uint r = 0;
	auto to_select = std::vector<Chromosome*>();
	while (chosen < this->chose_size) // we need to find exactly chose_size induviduals
	{
		to_select.clear();
		for (int i = 0; i < 4; i++)
		{
			r = random.GenerateIntInRange(0, this->data->size() - 1);
			auto temp = this->data->at(r);
			if (!this->InParents(temp))
			{
				to_select.push_back(temp);
			}
			else
			{
				i--;
			}
		}
		int min_index = 0;
		double min_fit = to_select.at(0)->GetFitness();
		for (int i = 1; i < to_select.size(); i++)
		{
			double temp_fit = to_select.at(i)->GetFitness();
			if (temp_fit > min_fit)
			{
				min_index = i;
				min_fit = temp_fit;
			}
		}
		this->parents->push_back(to_select.at(min_index));
		chosen++;
	}

}

void GASelector::SelectToDie()
{
	/*
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
	*/
	uint chosen = 0;
	uint r = 0;
	auto to_die_select = std::vector<Chromosome*>();
	while (chosen < this->chose_size)
	{
		to_die_select.clear();
		for (int i = 0; i < 4; i++)
		{
			r = random.GenerateIntInRange(0, this->data->size() - 1);
			auto temp = this->data->at(r);
			if (!this->InDie(temp))
			{
				to_die_select.push_back(temp);
			}
			else
			{
				i--;
			}
		}
		int max_index = 0;
		double max_fit = to_die_select.at(0)->GetFitness();
		for (int i = 1; i < to_die_select.size(); i++)
		{
			double temp_fit = to_die_select.at(i)->GetFitness();
			if (temp_fit < max_fit)
			{
				max_index = i;
				max_fit = temp_fit;
			}
		}
		this->to_die->push_back(to_die_select.at(max_index));
		chosen++;
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

	/*
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
	*/
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
				else  // if we don't select this induvidual to crossover we add this to mutation
				{
					r = random.GenerateDouble();
					if (r < this->p_mut)
					{
						this->to_mutate->push_back(*iter);
					}
				}
				iter++;
			}
			if (!cross_added) // if we can't find pair we add selected induvidual to mutation.
			{
				r = random.GenerateDouble();
				if (r < this->p_mut)
				{
					this->to_mutate->push_back(to_cross.first);
				}
				
			}

		}
		else
		{
			r = random.GenerateDouble();
			if (r < this->p_mut)
			{
				this->to_mutate->push_back(*iter);
			}
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

void GASelector::SetMutateProbability(double prob)
{
	this->p_mut = prob;
}

void GASelector::SetData(std::vector<Chromosome*>* data)
{
	this->data = data;
}

void GASelector::CalculateFitness() // calculate fitness fo each induvidual and total fitness
{
	this->chrom_fitness.clear();
	double total_fitness = 0.0;
	double max_fitness = -999999999999999999999.999;
	double fitness = 0.0;
	auto iter = this->data->begin();
	while (iter < this->data->end())
	{
		if (!(*iter)->IsCalculated())
		{
			fitness = this->evaluate->Eval(*iter);
			(*iter)->SetFitness(fitness);
			(*iter)->SetCalculated(true);
		}
		else
		{
			fitness = (*iter)->GetFitness();
		}
		total_fitness += fitness;
		if (fitness > max_fitness)
		{
			max_fitness = fitness;
		}
		iter++;
	}
	this->CurrentMaxFitness = max_fitness;
	this->CurrentTotalFitness = total_fitness;
}

void GASelector::CalculateProbabilities() // calculate proportional probabilities
{
	auto iter = this->data->begin();
	double val;
	while (iter < this->data->end())
	{
		//We try to find the minimum.
		// for example total_prob = -100,induvidual_prob = -3
		// then selection probability is 1 - (-3)/(-100) =1 - 0.03 = 0.97
		//and die probability is (-3)/(-100) = 0.03
		val = abs((*iter)->GetFitness() - this->CurrentMaxFitness) / abs((*iter)->GetFitness());
		this->selection_prob.push_back(1.0 - val); 
		this->die_prob.push_back(val);
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