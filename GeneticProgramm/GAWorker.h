#include <vector>
#include "Chromosome.h"
#include "GASelector.h"
#include "GAExecuter.h"
#include "Calculate.h"
#pragma once
#ifndef GAWORKER_H
#define GAWORKER_H

typedef double (*pEval)(Chromosome* chr, std::vector<double>* y, Calcluate* calc);
typedef unsigned int uint;
class GAWorker
{
private:
	uint pop_size;

	double p_mut; // probability of mutation
	double p_cross;// probability of crossover

	double avg_fitness;
	std::vector<Chromosome*> *data;
	std::vector<double>* y;

	GAExecuter *executer;
	GASelector *selector;

	Calcluate* calc;
	pEval Eval;

	
public:
	GAWorker(std::vector<Chromosome*>* data,double p_mut,double p_cross);

	void SetExecuter(GAExecuter* executer);
	void SetSelector(GASelector* selector);
	void SetCalculator(Calcluate* calc);
	void SetEval(pEval eval);
	void SetYVector(std::vector<double>* y);



	void InsertOne(Chromosome* chr);
	void InsertMany(std::vector<Chromosome*> * chr);

	void ExecuteOne();
	void ExecuteMany(uint times);

	std::vector<Chromosome*>* GetData();
	Chromosome* GetBest();

private:
	void Execute();

	void FindAvgFit();

	uint GetPopSize();

	void Init();

	void DeleteFromPopulation(std::vector<Chromosome*>* to_die);
	void AddToPopulation(std::vector<Chromosome*>* to_add);
};


#endif // !GAWORKER_H
