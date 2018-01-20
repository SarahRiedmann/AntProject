#include "stdafx.h"
#include "Test.h"

int testWidth(Environment* env)
{
	Area* currentArea = env->getRoot();
	int j = 1;
	while (currentArea->getEast() != NULL)
	{
		currentArea = currentArea->getEast();
		j++;
	}
	if (j != env->getCols())
	{
		return -1;
	}
	return 0;
}

int testHeight(Environment* env)
{
	Area* currentArea = env->getRoot();
	int i = 1;
	while (currentArea->getSouth() != NULL)
	{
		currentArea = currentArea->getSouth();
		i++;
	}
	if (i != env->getRows())
	{
		return -1;
	}
	return 0;
}

/*int testRoundTrip(Environment* env)
{
	Area* currentArea = env->getRoot();
	// einmal rundum gehen, außen muss NULL sein
	// 4x nach Osten
	currentArea = currentArea->getEast();
	if (currentArea->getNorth() != NULL) return -1;
	currentArea = currentArea->getEast();
	if (currentArea->getNorth() != NULL) return -1;
	currentArea = currentArea->getEast();
	if (currentArea->getNorth() != NULL) return -1;
	currentArea = currentArea->getEast();
	if (currentArea->getNorth() != NULL) return -1;
	// 4x nach Sueden
	currentArea = currentArea->getSouth();

	if (currentArea->getEast() != NULL) return -1;
	currentArea = currentArea->getSouth();
	if (currentArea->getEast() != NULL) return -1;
	currentArea = currentArea->getSouth();
	if (currentArea->getEast() != NULL) return -1;
	currentArea = currentArea->getSouth();
	if (currentArea->getEast() != NULL) return -1;
	// 4x nach Westen
	currentArea = currentArea->getWest();
	if (currentArea->getSouth() != NULL) return -1;
	currentArea = currentArea->getWest();
	if (currentArea->getSouth() != NULL) return -1;
	currentArea = currentArea->getWest();
	if (currentArea->getSouth() != NULL) return -1;
	currentArea = currentArea->getWest();
	if (currentArea->getSouth() != NULL) return -1;
	// 3x nach Norden
	currentArea = currentArea->getNorth();
	if (currentArea->getWest() != NULL) return -1;
	currentArea = currentArea->getNorth();
	if (currentArea->getWest() != NULL) return -1;
	currentArea = currentArea->getNorth();
	if (currentArea->getWest() != NULL) return -1;
	// Norden sollte nach einem Rundgang das Startfeld sein
	if (currentArea->getNorth() != env->getRoot()) return -1;
	// 3x nach Osten
	currentArea = currentArea->getEast();
	currentArea = currentArea->getEast();
	currentArea = currentArea->getEast();
	// 2x nach Sueden
	currentArea = currentArea->getSouth();
	currentArea = currentArea->getSouth();
	// 2x nach Westen
	currentArea = currentArea->getWest();
	currentArea = currentArea->getWest();
	// 1x nach Norden
	currentArea = currentArea->getNorth();
	// 1x nach Osten
	currentArea = currentArea->getEast();

	if (currentArea->getNorth()->getNorth()->getNorth() != NULL) return -1;
	if (currentArea->getEast()->getEast()->getEast() != NULL) return -1;
	if (currentArea->getSouth()->getSouth()->getSouth() != NULL) return -1;
	if (currentArea->getWest()->getWest()->getWest() != NULL) return -1;
	return 0;
}*/

int testAntMove()
{
	Environment::getInstance()->clearAll();
	Area* area = Environment::getInstance()->getArea(16);
	Ant* ant = static_cast<Ant*>(Creator::getInstance()->create(Itemtyp::ant, area));
	Area* startingPoint = ant->getMyarea();
	std::vector<Area*> neighbors = startingPoint->getDirections();

	std::cout << "I started on Area " << startingPoint->getX() << ", " << startingPoint->getY() << std::endl;
	std::cout << "I have " << neighbors.size() << " neighbors!" << std::endl;

	ant->act();

	for (unsigned int neighbor = 0; neighbor < neighbors.size(); neighbor++)
	{
		for (unsigned int item = 0; item < neighbors[neighbor]->items.size(); item++)
		{
			if (Ant* ant = dynamic_cast<Ant*> (neighbors[neighbor]->items[item]))
			{
				std::cout << "Found Ant on Area " << neighbors[neighbor]->getX() << ", " << neighbors[neighbor]->getY() << "!" << std::endl;
				delete ant;
				return 0;
			}
		}
	}

	Area* newArea = ant->getMyarea();
	std::cout << "I am now on Area " << newArea->getX() << ", " << newArea->getY() << std::endl;
	delete ant;
	return -1;
}

int testPheromones()
{
	Environment::getInstance()->clearAll();
	Area* area = Environment::getInstance()->getArea(7);
	Pheromone* pheromon = static_cast<Pheromone*>(Creator::getInstance()->create(Itemtyp::pheromone, area));
	int intensity = pheromon->getIntensity();
	std::cout << "Pheromon level at the beginning: " << intensity << std::endl;
	pheromon->act();

	int secondIntensity = pheromon->getIntensity();
	std::cout << "Pheromon level later: " << secondIntensity << std::endl;
	
	delete pheromon;
	if(secondIntensity < intensity)
	{
		return 0;
	}
	return -1;
}

int testFood()
{
	Environment::getInstance()->clearAll();
	Area* area = Environment::getInstance()->getArea(7);
	for (int i = 0; i < 5; i++)
	{
		Item* food = Creator::getInstance()->create(Itemtyp::food, area);
		area->items.push_back(food);
	}

	std::vector<Food*> foodlist = area->getAllFoodOnArea();
	std::cout << "Area stores " << foodlist.size() << " food elements before lunch." << std::endl;
	
	area->eatUpFirst();
	foodlist = area->getAllFoodOnArea();
	std::cout << "After a Snack Area stores " << foodlist.size() << " food elements." << std::endl;
	
	area->eatUp();
	foodlist = area->getAllFoodOnArea();
	std::cout << "After lunch Area stores " << foodlist.size() << " food elements." << std::endl;

	area->eatUp();
	foodlist = area->getAllFoodOnArea();
	std::cout << "Looking into the fridge, but " << foodlist.size() << " food elements." << std::endl;

	if(foodlist.size() > 0){return -1;}
	return 0;
}

int testAnthill()
{
	Environment::getInstance()->clearAll();
	Area* area = Environment::getInstance()->getArea(7);
	Anthill* anthill = static_cast<Anthill*>(Creator::getInstance()->create(Itemtyp::anthill, area));
	//static_cast<Anthill*>(anthill)->addFood();
	
	int foodlevel = anthill->getFoodLevel();
	std::cout << "On the anthill are " << foodlevel << " food elements." << std::endl;

	anthill->act();
	foodlevel = anthill->getFoodLevel();
	//delete anthill;

	std::cout << "Now there are " << foodlevel << " food elements in the anthill." << std::endl;
	if (foodlevel != 0)
	{
		std::cout << "Foodlevel is wrong, should be NULL" << std::endl;
		return -1;
	}
	
	int antcounter = 0;
	for (unsigned int item = 0; item < area->items.size(); item++)
	{
		if (Ant* ant = dynamic_cast<Ant*> (area->items[item]))
		{
			antcounter++;
		}
	}
	std::cout << "BUT now there are " << antcounter << " ants!" << std::endl;

	if (antcounter < foodlevel)
	{
		std::cout << "Ant production messed up!" << std::endl;
		return -1;
	}
	return 0;
}

int testAnthillSetup()
{
	Environment::getInstance()->clearAll();
	Environment* env = Environment::getInstance();

	env->addAnthill((size_t)7);
	std::map<int, Anthill*> anthills = env->getAllAnthills();

	if (anthills.count((size_t)7) == 1) 
	{ 
		std::cout << "Anhill successfully created!" << std::endl;
		return 0; 
	}
	return -1;
}

int testAntLifecycle()
{
	Environment* env = Environment::getInstance();
	env->clearAll();

	Area* area = Environment::getInstance()->getArea(16);
	Ant* ant = static_cast<Ant*>(Creator::getInstance()->create(Itemtyp::ant, area));
	for (int i = 0; i < Ant::MAX_YEARS_TO_LIVE; i++)
	{
		ant->act();
		ant->reset();

		std::map<int, std::vector<Ant*>> ants = env->getAllAnts();
		std::vector<Ant*> antsOnArea = ants.begin()->second;
		if (ants.size() != 1 || antsOnArea.size() != 1) 
		{
			std::cout << "Anzahl Areas mit Ants: " << ants.size() << std::endl;
			std::cout << "Anzahl Ants auf Area: " << antsOnArea.size() << std::endl;
			std::cout << "Too much ants!" << std::endl;
			return -1;
		}

	}
	ant->act();
	ant->reset();

	std::map<int, std::vector<Ant*>> ants = env->getAllAnts();

	if (ants.size() != 0)
	{
		std::cout << "Anzahl Areas mit Ants: " << ants.size() << std::endl;
		std::cout << "Ant not killed properly!" << std::endl;
		return -1;
	}

	std::cout << "Ant Lifecycle successfully tested!" << std::endl;
	return 0;
}

int testFoodSetup()
{
	Environment* env = Environment::getInstance();
	env->clearAll();

	unsigned int numFood = 6;
	unsigned int randIndex = env->getRandArea();
	for (int i = 0; i < numFood; i++)
	{
		env->addFood(randIndex);
	}

	std::vector<Food*> foodMenu = env->getArea(randIndex)->getAllFoodOnArea();
	if (foodMenu.size() != numFood)
	{
		std::cout << "Food Setup failed: " << foodMenu.size() << " Food on Area!" << std::endl;
		return -1;
	}
	std::cout << "Food Setup successful!" << std::endl;
	return 0;
}

int testAll()
{
	Environment* env = Environment::getInstance();
	env->clearAll();

	std::cout << "Starte Test 'testHeight' ..." << std::endl;
	if (testHeight(env) != 0)
	{
		std::cout << "Test 'testHeight' schlug fehl" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << "Starte Test 'testWidth' ..." << std::endl;
	if (testWidth(env) != 0)
	{
		std::cout << "Test 'testWidth' schlug fehl" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;

	/*std::cout << "Starte Test 'testRoundTrip' ..." << std::endl;
	if (testRoundTrip(env) != 0)
	{
		std::cout << "Test 'testRoundTrip' schlug fehl" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;
	*/

	std::cout << "Starte Test 'Pheromon-Test' ..." << std::endl;
	if (testPheromones() != 0)
	{
		std::cout << "Test Pheromon schlug fehl!" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;


	std::cout << "Starte Test 'Anthill-Test' ..." << std::endl;
	if (testAnthill() != 0)
	{
		std::cout << "Test Anthill schlug fehl!" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;


	std::cout << "Starte Test 'Food-Test' ..." << std::endl;
	if (testFood() != 0)
	{
		std::cout << "Test Food schlug fehl!" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;


	std::cout << "Starte Test 'AntMove-Test' ..." << std::endl;
	if (testAntMove() != 0)
	{
		std::cout << "Test AntMove schlug fehl!" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;

	std::cout << "Starte Test 'AnthillSetup-Test' ..." << std::endl;
	if (testAnthillSetup() != 0)
	{
		std::cout << "Test Anthill Setup schlug fehl!" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;

	std::cout << "Starte Test 'Ant-Lifecycle-Test' ..." << std::endl;
	if (testAntLifecycle() != 0)
	{
		std::cout << "Test Ant-Lifecycle Setup schlug fehl!" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;

	std::cout << "Starte Test 'Food-Setup Test' ..." << std::endl;
	if (testFoodSetup() != 0)
	{
		std::cout << "Test Food-Setup schlug fehl!" << std::endl;
		return -1;
	}
	std::cout << "Erfolg!" << std::endl;
	std::cout << std::endl;

	return 0;
}




