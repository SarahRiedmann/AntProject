#include "stdafx.h"
#include "Ant.h"
#include <iostream>
#include "Creator.h"
#include "Area.h"
#include "AntLostException.h"

int Ant::idCounter = 0;

Ant::Ant(std::shared_ptr<Area> _myarea) : myarea(_myarea)
{
	id = idCounter;
	idCounter++;
	rememberWayBack(myarea);
}

std::shared_ptr<Area> Ant::getMyarea()
{
	return myarea;
}


void Ant::move(std::shared_ptr<Area> nextArea)
{
	for (std::uint16_t i = 0; i < myarea->items.size(); i++)
	{
		if (this == myarea->items[i])
		{
			myarea->items.erase(myarea->items.begin() + i);
			nextArea->items.push_back(this);

			std::cout << "Ant " << id << " moved from: " << myarea->getX() << "," << myarea->getY() << " to: " << nextArea->getX() << "," << nextArea->getY() << std::endl;

			myarea = nextArea;
			return;
		}
	}
	throw AntLostException("ANT FOUND IN NIRVANA!");
}


void Ant::leavePheromoneTrace()
{
	for (std::uint16_t item = 0; item < myarea->items.size(); item++)
	{
		if (Pheromone* pheromone = dynamic_cast<Pheromone*> (myarea->items[item]))
		{
			pheromone->renewIntensity();
		}
		else
		{
			if (myarea->getAnthill() == nullptr)
			{
				 Creator::getInstance().create(Itemtyp::pheromone, myarea);
		
			}
		}
	}

}

void Ant::homeSweetHome()
{
	for (unsigned int item = 0; item < myarea->items.size(); item++)
	{
		if (Anthill* home = dynamic_cast<Anthill*> (myarea->items[item]))
		{
			home->addFood();
			this->hasFood = false;
			rememberWayBack(myarea);

			std::cout << "Ant " << id << " delivered Food" << std::endl;
			return;
		}
	}

	throw AntLostException("Ant LOST!");
}

void Ant::rememberWayBack(std::shared_ptr<Area> stepBack)
{
	wayBack.push_back(stepBack);
}

void Ant::removeAnt()
{
	myarea->items.erase(std::remove_if(myarea->items.begin(), myarea->items.end(), [this](Item* item)
	{
		Ant* ant = dynamic_cast<Ant*>(item);
		return (ant != nullptr && ant == this);
	}), myarea->items.end());

}


std::shared_ptr<Area> Ant::findPheromoneTrace()
{
	std::vector<std::shared_ptr<Area>> directions = myarea->getDirections();
	std::shared_ptr<Area> neighborMostPheromones = randomDirection();
	int maxPheromonlevel = 0;

	for (std::uint16_t neighbor = 0; neighbor < directions.size(); neighbor++)
	{
		Pheromone* pheromon = directions[neighbor]->getPheromone();
		if (pheromon == nullptr) { continue; }

		if (pheromon->getIntensity() > maxPheromonlevel)
		{
			maxPheromonlevel = pheromon->getIntensity();
			neighborMostPheromones = directions[neighbor];
		}
	}
	std::cout << "Pheromonelevel: " << maxPheromonlevel << " at " << neighborMostPheromones->getX() << "," << neighborMostPheromones->getY() << std::endl;
	return neighborMostPheromones;
}

std::shared_ptr<Area> Ant::randomDirection()
{
	std::vector<std::shared_ptr<Area>> directions = myarea->getDirections();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0, (directions.size()-1));
	int randNum = static_cast<int>(dist(gen));
	return directions[randNum];
}

Food * Ant::tryfoodPickup()
{
	for (unsigned int item = 0; item < myarea->items.size(); item++)
	{
		if (Food* food = dynamic_cast<Food*> (myarea->items[item]))
		{
			myarea->items.erase(myarea->items.begin() + item);
			return food;
		}
	}
	return nullptr;
}

std::shared_ptr<Area> Ant::findNeighborsFood()
{
	std::vector<std::shared_ptr<Area>> directions = myarea->getDirections();

	for (std::uint16_t neighbor = 0; neighbor < directions.size(); neighbor++)
	{
		Food* food = directions[neighbor]->getFirstFood();
		if (food != nullptr)
		{
			return directions[neighbor]; 
		}

	}
	return nullptr;
}



void Ant::act()
{
	std::vector<std::shared_ptr<Area>> directions = myarea->getDirections();

	if (hasChanged())
	{
		std::cout << "Ant " << id << " already moved" << std::endl;
		return;
	}
	std::cout << "Ant " << id << " starts to act" << std::endl;
	change();

	if (yearsToLive < 1)
	{
		// Ant ist tot
		std::cout << "Ant " << id << " died!" << std::endl;
		removeAnt();
		return;
	}
	yearsToLive--;

	if (hasFood == true)
	{
		if (wayBack.size() == 0)
		{
			// TODO : Effizienz Optimierung durch Essen abliefern und Schritt gehen
			homeSweetHome();
			return;
		}
		leavePheromoneTrace();

		std::shared_ptr<Area> nextArea = wayBack.back();
		wayBack.pop_back();
		move(nextArea);

		return;
	}

	else
	{
		std::shared_ptr<Area> nextArea = findNeighborsFood();		
		if (nextArea != nullptr)
		{
			move(nextArea);
			hasFood = true;

			rememberWayBack(myarea);
			nextArea->getFirstFood();
			nextArea->eatUpFirst();
			std::cout << "Food picked up by Ant " << id << std::endl;
			return;
		}

		nextArea = findPheromoneTrace();
		move(nextArea);

		rememberWayBack(myarea);
		return;

	}

	throw std::runtime_error("Unexpected Error!");
}