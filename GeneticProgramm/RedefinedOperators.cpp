#include "RedefinedOperators.h"

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
    if (abs(p2) < 0.001)
    {
        return 1;
    }
    return p1/p2;
}

