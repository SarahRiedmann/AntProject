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
	std::shared_ptr<Area> myarea;
	unsigned int foodlevel = 1;

public:
	Anthill(std::shared_ptr<Area> _myarea);
	void addFood();
	void setFoodlevel(unsigned int newfoodlevel);
	std::shared_ptr<Area> getMyarea();
	unsigned int getFoodLevel();

	void act() override;
};

