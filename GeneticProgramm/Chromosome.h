#include "Tree.h"


#pragma once
#ifndef CHROMOSOME_H
#define CHROMOSOME_H
typedef unsigned int uint;
class Chromosome
{
private:
	Tree* data;
	double fitness;
	bool is_calculated;
public:
	Chromosome(Tree* tree);
	~Chromosome();

	Tree* GetData();

	bool IsCalculated();
	bool SetCalculated(bool calc);

	void SetFitness(double fitness);
	double GetFitness();
};


#endif // !CHROMOSOME_H
