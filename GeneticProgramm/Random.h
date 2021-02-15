#include <random>
#include <ctime>
#pragma once
#ifndef RANDOM_H
#define RANDOM_H

class Random
{
private:
	std::mt19937 generator;
	double fraction;
public:
	Random();

	double GenerateDoubleInRange(double min, double max);
	double GenerateDouble();
	int GenerateIntInRange(int min, int max);
};



#endif