#include "Tree.h"


#pragma once
#ifndef CHROMOSOME_H
#define CHROMOSOME_H
typedef unsigned int uint;
class Chromosome
{
private:
	Tree* data;

public:
	Chromosome(Tree* tree);

	Tree* GetData();
};


#endif // !CHROMOSOME_H
