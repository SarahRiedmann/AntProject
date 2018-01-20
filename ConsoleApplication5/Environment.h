#pragma once
#include <vector>
#include <map>
#include "Creator.h"

class Area;
class Anthill;
class Ant;
class Food;

class Environment
{
private:
	static Environment* _instance;

	Area* root;
	int rows = -1;
	int cols = -1;
	std::vector<Area*> vectorAreas;

private:
	Environment();

public:
	~Environment();
	static Environment* getInstance();

	int getRows();
	int getCols();
	Area* getRoot();
	Area* getArea(int index);
	Environment* setupEnv(int _rows, int _cols);
	static void cleanUp();
	Anthill* addAnthill();
	Anthill* addAnthill(unsigned int index);
	Food* addFood(unsigned int index);
	unsigned int getRandArea();
	std::map<int, Anthill*> getAllAnthills();
	std::map<int, std::vector<Ant*>> getAllAnts();
	bool antsAlive();
	void clearAll();
	void actAll();

private:
	void createAreas();
	void linkAreas();
	void showAreas();

};

