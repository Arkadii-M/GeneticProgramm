#include "Calculate.h"
#include "Chromosome.h"
#include <vector>
#pragma once
#ifndef GA_EVALUATE
#define GA_EVALUATE


class GAEvaluate
{
private:

	Calcluate* calc;
	std::vector<double> x;
	std::vector<double> y;


public:
	GAEvaluate(Calcluate* calc);
	~GAEvaluate();

	void SetX(std::vector<double> x);
	void SetY(std::vector<double> y);

	double Eval(Chromosome * chr);



};


#endif GA_EVALUATE