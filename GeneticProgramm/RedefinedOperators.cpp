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

