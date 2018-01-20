#pragma once
#include <iostream>
#include <memory>

enum class Itemtyp {ant, anthill, food, pheromone};

class Item;
class Area;
class Creator
{
private:
	Creator() {};
	//~Creator() { std::cout << "Creator deleted!" << std::endl; };

public:
	static Creator& getInstance();

	Item* create(Itemtyp typ, std::shared_ptr<Area> myarea);
};