#include "stdafx.h"
#include "Environment.h"
#include <list>
#include <iostream>
#include <cassert>
#include <random>
#include "Area.h"
#include "Anthill.h"

Environment* Environment::_instance = nullptr;

Environment::Environment()
{
}

Environment::~Environment()
{
	for (unsigned int i = 0; i < vectorAreas.size(); i++)
	{
		delete(vectorAreas[i]);
	}
	//std::cout << vectorAreas.size() << " Areas deleted" << std::endl;
}


Environment * Environment::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Environment;
	}
	return _instance;
}


int Environment::getRows()
{
	return rows;
}

int Environment::getCols()
{
	return cols;
}

void Environment::createAreas()
{
	int numAreas = rows * cols;

	for (int i = 0; i < numAreas; i++)
	{
		Area* temp = new Area(i, this);
		vectorAreas.push_back(temp);
	}
}

void Environment::linkAreas()
{
	Area* pArea;
	int x, y;
	for (unsigned int i = 0; i < vectorAreas.size(); i++)
	{
		pArea = vectorAreas[i];
		x = pArea->getX();
		y = pArea->getY();

		// linkes oberes Eck
		if (x == 0 && y == 0)
		{
			pArea->setEast(vectorAreas[i + 1]);
			pArea->setSouthEast(vectorAreas[i + cols + 1]);
			pArea->setSouth(vectorAreas[i + cols]);
		}
		// rechtes oberes Eck
		else if (x == cols - 1 && y == 0)
		{
			pArea->setWest(vectorAreas[i - 1]);
			pArea->setSouthWest(vectorAreas[i + cols - 1]);
			pArea->setSouth(vectorAreas[i + cols]);
		}
		// linkes unteres Eck
		else if (x == 0 && y == rows - 1)
		{
			pArea->setNorth(vectorAreas[i - cols]);
			pArea->setNorthEast(vectorAreas[i - cols + 1]);
			pArea->setEast(vectorAreas[i + 1]);
		}
		// rechtes unteres Eck
		else if (x == cols - 1 && y == rows - 1)
		{
			pArea->setNorth(vectorAreas[i - cols]);
			pArea->setNorthWest(vectorAreas[i - cols - 1]);
			pArea->setWest(vectorAreas[i - 1]);
		}
		//erste Reihe
		else if (x >= 1 && x <= cols - 1 && y == 0)
		{
			pArea->setEast(vectorAreas[i + 1]);
			pArea->setSouthEast(vectorAreas[i + cols + 1]);
			pArea->setSouth(vectorAreas[i + cols]);
			pArea->setSouthWest(vectorAreas[i + cols - 1]);
			pArea->setWest(vectorAreas[i - 1]);
		}
		//letzte Reihe
		else if (x >= 1 && x <= cols - 1 && y == rows - 1)
		{
			pArea->setEast(vectorAreas[i + 1]);
			pArea->setNorthEast(vectorAreas[i - cols + 1]);
			pArea->setNorth(vectorAreas[i - cols]);
			pArea->setNorthWest(vectorAreas[i - cols - 1]);
			pArea->setWest(vectorAreas[i - 1]);
		}
		//erste Spalte
		else if (y >= 1 && y <= rows - 1 && x == 0)
		{
			pArea->setNorth(vectorAreas[i - cols]);
			pArea->setNorthEast(vectorAreas[i - cols + 1]);
			pArea->setEast(vectorAreas[i + 1]);
			pArea->setSouthEast(vectorAreas[i + cols + 1]);
			pArea->setSouth(vectorAreas[i + cols]);
		}
		//letzte Spalte
		else if (y >= 1 && y <= rows - 1 && x == cols - 1)
		{
			pArea->setNorth(vectorAreas[i - cols]);
			pArea->setNorthWest(vectorAreas[i - cols - 1]);
			pArea->setWest(vectorAreas[i - 1]);
			pArea->setSouthWest(vectorAreas[i + cols - 1]);
			pArea->setSouth(vectorAreas[i + cols]);
		}
		//alle mittendrin
		else
		{
			pArea->setNorth(vectorAreas[i - cols]);
			pArea->setNorthEast(vectorAreas[i - cols + 1]);
			pArea->setEast(vectorAreas[i + 1]);
			pArea->setSouthEast(vectorAreas[i + cols + 1]);
			pArea->setSouth(vectorAreas[i + cols]);
			pArea->setSouthWest(vectorAreas[i + cols - 1]);
			pArea->setWest(vectorAreas[i - 1]);
			pArea->setNorthWest(vectorAreas[i - cols - 1]);
		}
	}
}

Area* Environment::getRoot()
{
	root = vectorAreas.front();
	return root;
}

Area* Environment::getArea(int index)
{
	return vectorAreas[index];
}

Environment* Environment::setupEnv(int _rows, int _cols)
{
	assert(rows == -1 && cols == -1);

		rows = _rows;
		cols = _cols;

		createAreas();
		linkAreas();

		return this;
}

void Environment::cleanUp()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
		std::cout << "Environment instance deleted!" << std::endl;
	}
}

Anthill * Environment::addAnthill()
{
	unsigned int randIndex = getRandArea();
	if (vectorAreas[randIndex]->getAnthill() != nullptr) addAnthill();

	return addAnthill(randIndex);
}

Anthill* Environment::addAnthill(unsigned int index)
{
	assert(index < static_cast<unsigned int>(rows * cols));
	assert(vectorAreas[index]->getAnthill() == nullptr);

	Item* anthill = Creator::getInstance()->create(Itemtyp::anthill, vectorAreas[index]);
	vectorAreas[index]->items.push_back(anthill);

	return dynamic_cast<Anthill*>(anthill);
}

Food * Environment::addFood(unsigned int index)
{
	assert(index < static_cast<unsigned int>(rows * cols));

	Item* food = Creator::getInstance()->create(Itemtyp::food, getArea(index));

	return dynamic_cast<Food*>(food);
}

unsigned int Environment::getRandArea()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0, (rows * cols) - 1);
	int randIndex = static_cast<int>(dist(gen));
	return randIndex;
}

std::map<int, Anthill*> Environment::getAllAnthills()
{
	std::map<int, Anthill*> anthills;

	for (int index = 0; index < vectorAreas.size(); index++)
	{
		Anthill* anthill = vectorAreas[index]->getAnthill();
		if (anthill != nullptr)
		{
			anthills[index] = anthill;
		}
	}
	return anthills;
}

std::map<int, std::vector<Ant*>> Environment::getAllAnts()
{
	std::map<int, std::vector<Ant*>> ants;

	for (int index = 0; index < vectorAreas.size(); index++)
	{
		std::vector<Ant*> antsOnArea = vectorAreas[index]->getAllAntsOnArea();
		if (antsOnArea.size() != 0)
		{
			ants[index] = antsOnArea;
		}
	}
	return ants;
	
}

bool Environment::antsAlive()
{
	return (getAllAnts().size() != 0);
}

void Environment::clearAll()
{
	for (int index = 0; index < vectorAreas.size(); index++)
	{
		vectorAreas[index]->clearItemsList();
	}
}

void Environment::actAll()
{
	for (int index = 0; index < vectorAreas.size(); index++)
	{
		vectorAreas[index]->reset();
	}
	
	for (int index = 0; index < vectorAreas.size(); index++)
	{
		vectorAreas[index]->actAllItems();
	}
}

// debug function
void Environment::showAreas()
{
	for (unsigned int i = 0; i < vectorAreas.size(); i++)
	{
		vectorAreas[i]->showNeighbors();
	}
}


