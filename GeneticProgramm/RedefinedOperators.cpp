#include "RedefinedOperators.h"
#include <iostream>
double RedefOp::myplus(double p1, double p2)
{
    return p1+p2;
}

double RedefOp::myminus(double p1, double p2)
{
    return p1-p2;
}

double RedefOp::mymult(double p1, double p2)
{
    return p1*p2;
}

double RedefOp::myabs(double p)
{
    return abs(p);
}

double RedefOp::mydiv(double p1, double p2)
{
    if (abs(p2) < DBL_EPSILON)
    {
        
        if (p2 < 0)
        {
            p2 = -1.0 * DBL_EPSILON;
        }
        else
        {
            p2 = DBL_EPSILON;
        }
    }
    return p1/p2;
}

double RedefOp::cosinus(double p)
{
    return cos(p);
}

double RedefOp::sinus(double p)
{
    return sin(p);
}

double RedefOp::tangens(double p)
{
    return tan(p);
}

double RedefOp::cotangens(double p)
{
    return 1/tan(p);
}

double RedefOp::power(double p1, double p2)
{
    return pow(p1,p2);
}

double RedefOp::myexp(double p)
{
    auto res = exp(p);
    if (res == std::numeric_limits<double>().infinity())
    {
        res = DBL_MAX;
    }
    return res;
}

