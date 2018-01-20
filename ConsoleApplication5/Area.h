#pragma once
#include <algorithm>
#include <vector>
#include <memory>
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

class Area
{
private:
	int x;
	int y;
	int index;
	
	std::vector<std::shared_ptr<Area>> neighbors = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	//std::vector<std::shared_ptr<Area>> validNeighbors;

public:
	Area(int _index);
	~Area();

public:
	std::vector<Item*> items;
	Item* addToList(Item* item) { items.push_back(item); return item; };

	void setNorthWest(std::shared_ptr<Area> a);
	void setNorth(std::shared_ptr<Area> a);
	void setNorthEast(std::shared_ptr<Area> a);
	void setEast(std::shared_ptr<Area> a);
	void setSouthEast(std::shared_ptr<Area> a);
	void setSouth(std::shared_ptr<Area> a);
	void setSouthWest(std::shared_ptr<Area> a);
	void setWest(std::shared_ptr<Area> a);

	std::shared_ptr<Area> getNorthWest();
	std::shared_ptr<Area> getNorth();
	std::shared_ptr<Area> getNorthEast();
	std::shared_ptr<Area> getEast();
	std::shared_ptr<Area> getSouthEast();
	std::shared_ptr<Area> getSouth();
	std::shared_ptr<Area> getSouthWest();
	std::shared_ptr<Area> getWest();

	void printName();
	void showNeighbors();

	unsigned int getX();
	unsigned int getY();

	std::vector<std::shared_ptr<Area>> getDirections();

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