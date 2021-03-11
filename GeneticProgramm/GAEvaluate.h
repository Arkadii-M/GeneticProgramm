#include "Calculate.h"
#include "Chromosome.h"
#include <vector>
#include <armadillo>
#include <math.h>
#pragma once
#ifndef GA_EVALUATE
#define GA_EVALUATE
using namespace arma;
typedef double (*YFunc)(double);
typedef double (*KFunc)(double, double);

class GAEvaluate
{
private:

	Calcluate* calc;

	// x in [x_a,x_b], x_steps - linspace steps;
	double x_a;
	double x_b;
	int x_steps;

	// int_a,int_b - integration limits,int_steps - steps of the [int_a,int_b]
	double int_a;
	double int_b;
	int int_steps;

	//y(x) = integral from a to b  (k(x,t)*u(t)) dt

	YFunc y;
	KFunc k;

	std::vector<double> y_vals;
	std::vector<std::vector<double>> k_vals;
	bool is_y_k_calculated;
public:
	GAEvaluate(Calcluate* calc);
	~GAEvaluate();

	void SetXInterval(double x_a, double x_b, int steps);

	void SetIntegralLimits(double int_a, double int_b, int int_steps);

	void SetYFunc(YFunc y);
	void SetKFunc(KFunc k);
	//void SetX(std::vector<double> x);
	//void SetY(std::vector<double> y);

	double Eval(Chromosome * chr);
private:
	void CalcYAndK();


};


#endif GA_EVALUATE