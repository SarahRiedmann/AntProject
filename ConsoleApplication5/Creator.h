#pragma once

enum class Itemtyp {ant, anthill, food, pheromone};

class Item;
class Area;
class Creator
{
private:
	static Creator* _instance;
	Creator() {};

public:
	static Creator* getInstance();

	Item* create(Itemtyp typ, Area* myarea);
};

