#include "GAWorker.h"

GAWorker::GAWorker(std::vector<Chromosome*>* data, double p_mut, double p_cross):
	data(data),
	p_mut(p_mut),
	p_cross(p_cross),
	executer(nullptr),
	selector(nullptr),
	calc(nullptr),
	Eval(nullptr),
	avg_fitness(0),
	y(nullptr)
	
{
	this->pop_size = this->data->size();
}

void GAWorker::SetExecuter(GAExecuter* executer)
{
	this->executer = executer;
}

void GAWorker::SetSelector(GASelector* selector)
{
	this->selector = selector;
}

void GAWorker::SetCalculator(Calcluate* calc)
{
	this->calc = calc;
}

void GAWorker::SetEval(pEval eval)
{
	this->Eval = eval;
}

void GAWorker::SetYVector(std::vector<double>* y)
{
	this->y = y;
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

void GAWorker::FindAvgFit()
{

	double temp =0.0;

	auto iter = this->data->begin();
	while (iter < this->data->end())
	{
		temp += this->Eval(*iter, this->y, this->calc);
		iter++;
	}
	this->avg_fitness = temp / this->GetPopSize();

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
	auto iter = this->data->begin();
	auto dIter = to_die->begin();
	while (iter < this->data->end())
	{
		dIter = to_die->begin();
		while (dIter < to_die->end())
		{
			if ((*iter)->GetData() == (*dIter)->GetData())
			{
				iter = this->data->erase(iter);
				break;
			}
			dIter++;
		}
		iter++;
	}
}

void GAWorker::AddToPopulation(std::vector<Chromosome*>* to_add)
{
	this->data->insert(this->data->begin(),to_add->begin(), to_add->end());
}