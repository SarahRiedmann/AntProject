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

	std::shared_ptr<Area> myarea;
	bool hasFood;
	int yearsToLive = MAX_YEARS_TO_LIVE;

	std::vector<std::shared_ptr<Area>> wayBack;

	void move(std::shared_ptr<Area> nextArea);
	void leavePheromoneTrace();
	void homeSweetHome();
	void rememberWayBack(std::shared_ptr<Area> stepBack);
	void removeAnt();
	
	Food* tryfoodPickup();
	std::shared_ptr<Area> findNeighborsFood();
	std::shared_ptr<Area> findPheromoneTrace();
	std::shared_ptr<Area> randomDirection();

public:
	Ant(std::shared_ptr<Area> _myarea);
	std::shared_ptr<Area> getMyarea();

	void act() override;
};

