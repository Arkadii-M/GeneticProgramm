#pragma once
#include <cstdlib>
#include <cfloat>
#ifndef REDEDINED_OPERATORS
#define REDEDINED_OPERATORS


class RedefOp
{
public:
	static double myplus(double p1, double p2);
	static double myminus(double p1, double p2);
	static double mymult(double p1, double p2);
	static double myabs(double p);
	static double mydiv(double p1, double p2);
	static double cosinus(double p);
	static double sinus(double p);
	static double tangens(double p);
	static double cotangens(double p);
	static double power(double p1, double p2);
	static double myexp(double p);
};
#endif // !REDEDINED_OPERATORS
