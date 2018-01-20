#include "stdafx.h"
#include "Area.h"
#include <iostream>
#include <vector>
#include "Ant.h"


Area::Area(int _index, Environment * _env): env(_env), index(_index)
{
	x = index % env->getCols();
	y = (index - x) / env->getCols();
	//std::cout << x << " / " <<  y << std::endl;
}

Area::~Area()
{
	//std::cout << "Area element deleted" << std::endl;
}

//setter functions
void Area::setNorthWest(Area * a)
{
	neighbors[NORTHWEST] = a;
}

void Area::setNorth(Area * a)
{
	neighbors[NORTH] = a;
}

void Area::setNorthEast(Area * a)
{
	neighbors[NORTHEAST] = a;
}

void Area::setEast(Area * a)
{
	neighbors[EAST] = a;
}

void Area::setSouthEast(Area * a)
{
	neighbors[SOUTHEAST] = a;
}

void Area::setSouth(Area * a)
{
	neighbors[SOUTH] = a;
}

void Area::setSouthWest(Area * a)
{
	neighbors[SOUTHWEST] = a;
}

void Area::setWest(Area * a)
{
	neighbors[WEST] = a;
}


//getter functions
Area * Area::getNorthWest()
{
	return neighbors[NORTHWEST];
}

Area * Area::getNorth()
{
	return neighbors[NORTH];
}

Area * Area::getNorthEast()
{
	return neighbors[NORTHEAST];
}

Area * Area::getEast()
{
	return neighbors[EAST];
}

Area * Area::getSouthEast()
{
	return neighbors[SOUTHEAST];
}

Area * Area::getSouth()
{
	return neighbors[SOUTH];
}

Area * Area::getSouthWest()
{
	return neighbors[SOUTHWEST];
}

Area * Area::getWest()
{
	return neighbors[WEST];
}


//debug functions
void Area::printName()
{
	std::cout << "Ich bin Area " << index << " an der Stelle " << x << ", " << y << std::endl;
}

void Area::showNeighbors()
{
	printName();
	std::cout << " --------------- " << std::endl;

	for (unsigned int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i] != nullptr)
		{
			neighbors[i]->printName();
		}
	}
	std::cout << std::endl;
}


unsigned int Area::getX()
{
	return x;
}

unsigned int Area::getY()
{
	return y;
}

std::vector<Area*> Area::getDirections()
{
	std::vector<Area*> validNeighbors;

	for (unsigned int neighbor = 0; neighbor < neighbors.size(); neighbor++)
	{
		if (neighbors[neighbor] == nullptr) { continue; }
		validNeighbors.push_back(neighbors[neighbor]);
	}
	return validNeighbors;
}

Pheromone * Area::getPheromone()
{
	for (unsigned int item = 0; item < items.size(); item++)
	{
		if (Pheromone* pheromon = dynamic_cast<Pheromone*>(items[item]))
		{
			return pheromon;
		}
	}
	return nullptr;
}

Food * Area::getFirstFood()
{
	std::vector<Food*> foodMenu = getAllFoodOnArea();
	if(foodMenu.size() == 0) { return nullptr; }
	return foodMenu.front();
}

Ant * Area::getFirstAnt()
{
	std::vector<Ant*> ants = getAllAntsOnArea();
	if (ants.size() == 0) { return nullptr; }
	return ants.front();
}

std::vector<Ant*> Area::getAllAntsOnArea()
{
	std::vector<Ant*> ants;
	for (unsigned int item = 0; item < items.size(); item++)
	{
		if (Ant* ant = dynamic_cast<Ant*>(items[item]))
		{
			ants.push_back(ant);
		}
	}
	return ants;
}


Anthill * Area::getAnthill()
{
	for (unsigned int item = 0; item < items.size(); item++)
	{
		if (Anthill* anthill = dynamic_cast<Anthill*>(items[item]))
		{
			return anthill;
		}
	}
	return nullptr;
}

std::vector<Food*> Area::getAllFoodOnArea()
{
	std::vector<Food*> foodMenu;
	for (unsigned int item = 0; item < items.size(); item++)
	{
		if (Food* food = dynamic_cast<Food*>(items[item]))
		{
			foodMenu.push_back(food);
		}
	}
	return foodMenu;
}

void Area::eatUp()
{
	items.erase(std::remove_if(items.begin(), items.end(), [](Item* item)
	{
		Food* food = dynamic_cast<Food*>(item);
		return (food != nullptr);
	}), items.end());
}

void Area::eatUpFirst()
{
	for (unsigned int item = 0; item < items.size(); item++)
	{
		if (Food* food = dynamic_cast<Food*>(items[item]))
		{
			items.erase(items.begin() + item);
			return;
		}
	}
}

void Area::clearItemsList()
{
	items.erase(std::remove_if(items.begin(), items.end(), [](Item* item)
	{
		return (item != nullptr);
	}), items.end());
}

void Area::actAllItems()
{
	for (int item = 0; item < items.size(); item++)
	{
		items[item]->act();

	}
}

void Area::reset()
{
	for (int item = 0; item < items.size(); item++)
	{
		items[item]->reset();
	}
}
