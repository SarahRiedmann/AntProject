#pragma once
#include <vector>
#include "Item.h"
#include "Food.h"
#include "Ant.h"

class Area;

class Anthill :
	public Item
{
private:
	Area* myarea;
	unsigned int foodlevel = 1;

public:
	Anthill(Area* _myarea);
	void addFood();
	void setFoodlevel(unsigned int newfoodlevel);
	Area* getMyarea();
	unsigned int getFoodLevel();

	void act() override;
};

