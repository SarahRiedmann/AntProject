#pragma once
#include <algorithm>
#include <vector>
#include "Environment.h"
#include "Item.h"
#include "Pheromone.h"
#include "Food.h"

#define NORTHWEST 0
#define NORTH 1
#define NORTHEAST 2
#define EAST 3
#define SOUTHEAST 4
#define SOUTH 5
#define SOUTHWEST 6
#define WEST 7

class Ant;
class Anthill;
class Environment;
class Area
{
private:
	Environment* env;
	int x;
	int y;
	int index;
	
	std::vector<Area*> neighbors = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	std::vector<Area*> validNeighbors;

public:
	Area(int _index, Environment* env);
	~Area();

public:
	std::vector<Item*> items;
	Item* addToList(Item* item) { items.push_back(item); return item; };

	void setNorthWest(Area* a);
	void setNorth(Area* a);
	void setNorthEast(Area* a);
	void setEast(Area* a);
	void setSouthEast(Area* a);
	void setSouth(Area* a);
	void setSouthWest(Area* a);
	void setWest(Area* a);

	Area* getNorthWest();
	Area* getNorth();
	Area* getNorthEast();
	Area* getEast();
	Area* getSouthEast();
	Area* getSouth();
	Area* getSouthWest();
	Area* getWest();

	void printName();
	void showNeighbors();

	unsigned int getX();
	unsigned int getY();

	std::vector<Area*> getDirections();

	Pheromone* getPheromone();
	Food* getFirstFood();
	std::vector<Food*> getAllFoodOnArea();

	Ant* getFirstAnt();
	std::vector<Ant*> getAllAntsOnArea();

	Anthill* getAnthill();
	void eatUp();
	void eatUpFirst();
	void clearItemsList();
	void actAllItems();
	void reset();
};