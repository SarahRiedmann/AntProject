#include "stdafx.h"
#include "Anthill.h"
#include <vector>
#include "Creator.h"
#include "Area.h"

Anthill::Anthill(std::shared_ptr<Area> _myarea)
{
	myarea = _myarea;
}

void Anthill::addFood()
{
	foodlevel++;
}

void Anthill::setFoodlevel(unsigned int newfoodlevel)
{
	foodlevel = newfoodlevel;
}

std::shared_ptr<Area> Anthill::getMyarea()
{
	return myarea;
}

unsigned int Anthill::getFoodLevel()
{
	return foodlevel;
}


void Anthill::act()
{
	if (foodlevel > 0)
	{
		// TODO : delete ant elements wenn der life cycle vorbei ist
		Item* ant = Creator::getInstance().create(Itemtyp::ant, myarea);
		foodlevel--;
	}
	
}
