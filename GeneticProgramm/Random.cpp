#include "Random.h"
#include <iostream>

Random::Random()
{
	std::random_device rd;
	this->generator = std::mt19937(rd());
	fraction = 1.0 / ((double)(generator.max()) + 1.0);
}

double Random::GenerateDoubleInRange(double min, double max)
{
	
	return 0.0;
}

double Random::GenerateDouble()
{
	double gen = (double)(generator() * fraction);
	//std::cout << gen << std::endl;
	return gen;
}

int Random::GenerateIntInRange(int min, int max)
{
	int gen = (int)(generator() * fraction * ((double)max - (double)min + 1.0) + (double)min);
	//std::cout << gen << std::endl;
	return gen;
}
