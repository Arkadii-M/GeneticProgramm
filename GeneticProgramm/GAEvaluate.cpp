#include "GAEvaluate.h"

GAEvaluate::GAEvaluate(Calcluate* calc):
	calc(calc),
	y(NULL),
	k(NULL),
	x_a(0),
	x_b(0),
	x_steps(0),
	int_a(0),
	int_b(0),
	int_steps(0)
{
	this->k_vals = std::vector< std::vector<double>>();
	this->y_vals = std::vector<double>();
	this->is_y_k_calculated = false;
}

GAEvaluate::~GAEvaluate()
{
	delete calc;
}

void GAEvaluate::SetXInterval(double x_a, double x_b, int steps)
{
	this->x_a = x_a;
	this->x_b = x_b;
	this->x_steps = steps;
}

void GAEvaluate::SetIntegralLimits(double int_a, double int_b, int int_steps)
{
	this->int_a = int_a;
	this->int_b = int_b;
	this->int_steps = int_steps;
}

void GAEvaluate::SetYFunc(YFunc y)
{
	this->y = y;
}

void GAEvaluate::SetKFunc(KFunc k)
{
	this->k = k;
}



double GAEvaluate::Eval(Chromosome* chr)
{
	auto tree = chr->GetData();
	
	vec x = linspace(x_a, x_b, x_steps);

	vec  delta = zeros<vec>(x_steps);

	vec integral_lin = linspace(int_a, int_b, int_steps);
	vec integral_under = zeros<vec>(int_steps);

	std::vector<double> u_temp;
	auto to_calc_points =arma::conv_to<std::vector<double>>().from(integral_lin);
	calc->SetVarInterval("x", to_calc_points);
	u_temp = calc->CalcTreeMany(tree, to_calc_points.size());

	for (int i = 0; i < x_steps; ++i)
	{
		for (int j = 0; j < int_steps; ++j)
		{
			integral_under[j] = k(x[i], integral_lin[j]) * u_temp[j];
		}
		delta[i] = abs(arma::conv_to<double>().from(trapz(integral_lin, integral_under)) - y(x[i]));
	}

	delta.for_each([](mat::elem_type& val) { val *= val; });
	double temp = sum((delta));
	temp /= x_steps;
	temp = sqrt(temp);
	
	/*
	if (!this->is_y_k_calculated)
	{
		this->CalcYAndK();
		this->is_y_k_calculated = true;
	}

	vec  delta = zeros<vec>(x_steps);
	vec integral_under = zeros<vec>(int_steps);
	vec integral_lin = linspace(int_a, int_b, int_steps);

	std::vector<double> u_temp;
	auto to_calc_points = arma::conv_to<std::vector<double>>().from(integral_lin);
	calc->SetVarInterval("x", to_calc_points);
	u_temp = calc->CalcTreeMany(tree, to_calc_points.size());

	for (int i = 0; i < x_steps; ++i)
	{
		for (int j = 0; j < int_steps; ++j)
		{
			integral_under[j] = this->k_vals[i][j] * u_temp[j];
		}
		delta[i] = abs(arma::conv_to<double>().from(trapz(integral_lin, integral_under)) - y_vals[i]);
	}

	delta.for_each([](mat::elem_type& val) { val *= val; });
	double temp = sum((delta));
	temp /= x_steps;
	temp = sqrt(temp);
	*/
	return -temp;
}

void GAEvaluate::CalcYAndK()
{
	vec x = linspace(x_a, x_b, x_steps);
	vec integral_lin = linspace(int_a, int_b, int_steps);

	this->k_vals.clear();
	this->y_vals.clear();

	std::vector<double> temp = std::vector<double>();
	for (int i = 0; i < x_steps; ++i)
	{
		for (int j = 0; j < int_steps; ++j)
		{
			temp.push_back(k(x[i], integral_lin[j]));
		}
		y_vals.push_back(y(x[i]));

		this->k_vals.push_back(temp);
		temp.clear();

	}


}
