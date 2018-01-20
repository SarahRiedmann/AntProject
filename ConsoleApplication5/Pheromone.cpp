#include "stdafx.h"
#include "Pheromone.h"

const int Pheromone::INTMAX = 5;

Pheromone::Pheromone() :intensity(INTMAX)
{
}

void Pheromone::renewIntensity()
{
	intensity = INTMAX;
}

int Pheromone::getIntensity()
{
	return intensity;
}


void Pheromone::act()
{
	if (intensity > 0)
	{
		intensity--;
	}
}
