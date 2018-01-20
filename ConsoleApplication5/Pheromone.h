#pragma once
#include "Item.h"
class Pheromone :
	public Item
{
private:
	int intensity;
	static const int INTMAX;

public:
	Pheromone();
	void renewIntensity();

	int getIntensity();

	void act() override;
};

