#include "GAWorker.h"
#include <iostream>

GAWorker::GAWorker(std::vector<Chromosome*>* data, double p_mut, double p_cross):
	data(data),
	p_mut(p_mut),
	p_cross(p_cross),
	executer(nullptr),
	selector(nullptr),
	avg_fitness(0)
	
{
	this->pop_size = this->data->size();
}

GAWorker::~GAWorker()
{
	delete data;
	delete selector;
	delete executer;
}

void GAWorker::SetExecuter(GAExecuter* executer)
{
	this->executer = executer;
}

void GAWorker::SetSelector(GASelector* selector)
{
	this->selector = selector;
}


void GAWorker::InsertOne(Chromosome* chr)
{
	this->data->push_back(chr);
	this->pop_size = this->data->size();
}

void GAWorker::InsertMany(std::vector<Chromosome*>* chr)
{
	this->data->insert(this->data->end(),chr->begin(), chr->end());
	this->pop_size = this->data->size();
}

void GAWorker::ExecuteOne()
{
	this->Execute();
}

void GAWorker::ExecuteMany(uint times)
{
	for (uint i = 1; i <= times; ++i)
	{
		this->Execute();
		//auto rng = std::default_random_engine{};
		//std::shuffle(this->data->begin(), this->data->end(),rng);
	}
}

std::vector<Chromosome*>* GAWorker::GetData()
{
	return this->data;
}

void GAWorker::Execute()
{
	this->selector->MakeSelection();
	auto to_add = this->selector->GetParents();
	auto to_crossove = this->selector->GetForCrossover();
	auto to_mutate = this->selector->GetForMutation();
	auto to_die = this->selector->GetToDie();

	this->DeleteFromPopulation(to_die);

	this->executer->SetForMutation(to_mutate);
	this->executer->SetForCrossover(to_crossove);

	this->executer->Execute();

	this->AddToPopulation(to_add);
}

uint GAWorker::GetPopSize()
{
	return this->data->size();
}

void GAWorker::Init()
{
}

void GAWorker::DeleteFromPopulation(std::vector<Chromosome*>* to_die)
{
	/*
	auto iter = this->data->begin();
	auto dIter = to_die->begin();
	while (iter < this->data->end())
	{
		dIter = to_die->begin();
		while (dIter < to_die->end())
		{
			if ((*iter) == (*dIter))
			{
				iter = this->data->erase(iter);
				dIter = to_die->begin();
				continue;
			}
			dIter++;
		}
		iter++;
	}
	*/
	auto iter = this->data->begin();
	auto diter = to_die->begin();
	bool erase = false;
	while (iter < this->data->end())
	{
		diter = to_die->begin();
		while (diter < to_die->end())
		{
			if ((*iter) == (*diter))
			{
				erase = true;
				to_die->erase(diter);
				break;
			}
			diter++;
		}

		if (erase)
		{
			iter = this->data->erase(iter);
			erase = false;
			continue;
		}
		iter++;
	}

}

void GAWorker::AddToPopulation(std::vector<Chromosome*>* to_add)
{
	this->data->insert(this->data->begin(),to_add->begin(), to_add->end());
}

std::ostream& operator<<(std::ostream& os, const GAWorker& dt)
{
	// TODO: вставьте здесь оператор return
	auto iter = dt.data->begin();
	std::cout << "Data size: " << dt.data->size() << std::endl;
	std::cout << "Adresses: " << std::endl;
	while (iter < dt.data->end())
	{
		std::cout << "Chromosome adress: " << *iter << "Data adress: " << (*iter)->GetData() << "Data depth:" <<(*iter)->GetData()->GetCurrentDepth() << std::endl;
		iter++;
	}

	return os;
}
