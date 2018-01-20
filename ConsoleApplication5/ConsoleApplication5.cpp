
#include <iostream>
#include "stdafx.h"
#include "Environment.h"
#include "Area.h"
#include <iostream>
#include "Test.h"
#include "Ant.h"
#include "Anthill.h"
#include "Creator.h"
#include "AntLostException.h"

int main()
{

	Environment* env = Environment::getInstance()->setupEnv(15, 15);

	env->addAnthill()->setFoodlevel(10);
	env->addAnthill()->setFoodlevel(10);

	int numFood = 30;
	unsigned int randIndex1 = env->getRandArea();
	unsigned int randIndex2 = env->getRandArea();
	unsigned int randIndex3 = env->getRandArea();

	for (int i = 0; i < numFood; i++)
	{
		env->addFood(randIndex1);
		env->addFood(randIndex2);
		env->addFood(randIndex3);
	}

	if (testAll() != 0) { Environment::cleanUp(); return -1; }

	unsigned int numIterations = 0;

	try
	{
		do
		{
			env->actAll();
			numIterations++;
			std::cout << "Lifecycle: " << numIterations << std::endl;

		} while (env->antsAlive());

		std::cout << std::endl;
		std::cout << "Number of Iterations: " << numIterations << std::endl;
		
	}
	catch (AntLostException &e)
	{
		std::cerr << e.getMessage() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	Environment::cleanUp();
    return 0;
}

