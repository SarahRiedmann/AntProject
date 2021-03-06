#include "stdafx.h"
#include "Creator.h"
#include "Ant.h"
#include "Food.h"
#include "Pheromone.h"
#include "Anthill.h"
#include "Area.h"
#include "Item.h"
#include <cassert>
#include <iostream>

Creator* Creator::_instance = nullptr;

Creator * Creator::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Creator;
	}
	return _instance;
}


Item* Creator::create(Itemtyp typ, Area* myarea)
{
	assert(myarea != nullptr);

	switch (typ)
	{
	case Itemtyp::ant:
		std::cout << "Ant created at " << myarea->getX() << "," << myarea->getY() << std::endl;
		return myarea->addToList(new Ant(myarea));
	case Itemtyp::anthill:
		std::cout << "Anthill created at " << myarea->getX() << "," << myarea->getY() << std::endl;
		return myarea->addToList(new Anthill(myarea));
	case Itemtyp::food:
		std::cout << "Food created at " << myarea->getX() << "," << myarea->getY() << std::endl;
		return myarea->addToList(new Food());
	case Itemtyp::pheromone:
		//std::cout << "Pheromone created at " << myarea->getX() << "," << myarea->getY() << std::endl;
		return myarea->addToList(new Pheromone());
	}
	return nullptr;
}

