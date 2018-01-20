#pragma once
#include <random>
#include <vector>
#include "Item.h"
#include "Food.h"
#include "Pheromone.h"
#include "Anthill.h"


class Area;

class Ant :
	public Item
{
public:
	const static int MAX_YEARS_TO_LIVE = 20;

private:
	static int idCounter;
	int id;

	Area* myarea;
	bool hasFood;
	int yearsToLive = MAX_YEARS_TO_LIVE;

	std::vector<Area*> wayBack;

	void move(Area* nextArea);
	void leavePheromoneTrace();
	void homeSweetHome();
	void rememberWayBack(Area* stepBack);
	void removeAnt();
	
	Food* tryfoodPickup();
	Area* findNeighborsFood();
	Area* findPheromoneTrace();
	Area* randomDirection();

public:
	Ant(Area* _myarea);
	Area* getMyarea();

	void act() override;
};

