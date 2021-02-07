#include "GAEvaluate.h"

GAEvaluate::GAEvaluate(Calcluate* calc):
	calc(calc),
	x(NULL),
	y(NULL)
{
}

GAEvaluate::~GAEvaluate()
{
	delete calc;
}

void GAEvaluate::SetX(std::vector<double> x)
{
	this->x = x;
}

void GAEvaluate::SetY(std::vector<double> y)
{
	this->y = y;
}

double GAEvaluate::Eval(Chromosome* chr)
{

	double res = 0.0;
	Tree* tree = chr->GetData();

	auto y_iter = y.begin();
	auto x_iter = x.begin();
	while (y_iter < y.end())
	{
		calc->SetVarValue("x", *x_iter);
		res += abs(calc->CalcTree(tree) - *y_iter);
		y_iter++;
		x_iter++;
	}
	return -res;
}
