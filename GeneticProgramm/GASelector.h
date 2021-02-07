#pragma once
#include <vector>
#include "Chromosome.h"
#include "Calculate.h"
#include "GAEvaluate.h"
#ifndef GASELECTOR_H
#define GASELECTOR_H
typedef unsigned int uint;
typedef double (*pEval)(Chromosome* chr, std::vector<double>* y, Calcluate* calc);
class GASelector
{
private:
	double CurrentTotalFitness; // current total fitness of population
	//parameters
	double p_mut; // probability of mutation
	double p_cross; //probability of crossover


	std::vector<double> selection_prob;
	std::vector<double> die_prob;
	std::vector<double> chrom_fitness; // fitness of each chromosome




	std::vector<Chromosome*>* data;
	std::vector<Chromosome*>* parents;
	std::vector<Chromosome*>* to_mutate;
	std::vector<std::pair< Chromosome*, Chromosome*>>* to_crossove;

	std::vector<Chromosome*>* to_die;

	uint chose_size;

	GAEvaluate* evaluate;



public:
	GASelector(std::vector<Chromosome*>* data, GAEvaluate* evaluate);

	void SetData(std::vector<Chromosome*>* data);
	void SetCrossoverProbability(double prob);
	void SetChoseSize(uint size);

	void MakeSelection();

	std::vector<Chromosome*>* GetForMutation();
	std::vector<std::pair< Chromosome*,Chromosome*>>* GetForCrossover();

	std::vector<Chromosome*>* GetToDie();

	std::vector<Chromosome*>* GetParents();


private:
	uint GetPopSize();
	void SelectParents();
	void SelectForMutationAndCrossover();
	void SelectToDie();
	void CalculateFitness();
	void CalculateProbabilities();

	void CopyParents();

	void ClearData();
	bool ParentsOrToDieHasChromosome(Chromosome * chr);
};

#endif // !GASELECTOR_H
