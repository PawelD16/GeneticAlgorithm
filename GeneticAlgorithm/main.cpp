#include <iostream>

#include "CGeneticAlgorithm.h"
#include "CKnapsackProblem.h"
#include "CIndividual.h"

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec);

void testOutEverything();
void runActualProblem();

int main()
{
	runActualProblem();
	//testOutEverything();
	return 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec)
{
	os << "{";

	for (int i = 0;i < vec.size() - 1;++i)
	{
		os << vec[i] << ", ";
	}

	if (vec.size() > 0)
	{
		os << vec[vec.size() - 1];
	}

	os << "}";

	return os;
}

void testOutEverything()
{
	//incorrect knapsack capacity
	try
	{
		CKnapsackProblem problem("incorrectKnapsackCapacityTest.txt");
	}
	catch (std::exception e)
	{
		std::cout << "\n" << e.what();
	}
	catch (...)
	{
		std::cout << "ded0";
	}
	
	//incorrect items values/weights
	try
	{
		CKnapsackProblem problem("incorrectValuesTest.txt");
	}
	catch (std::exception e)
	{
		std::cout << "\n" << e.what();
	}
	catch (...)
	{
		std::cout << "ded1";
	}

	//not existing file
	try
	{
		CKnapsackProblem problem("iDoNotExistLmao.txt");
	}
	catch (std::exception e)
	{
		std::cout << "\n" << e.what();
	}
	catch (...)
	{
		std::cout << "ded2";
	}

	//incorrect values for KnapsackProblem
	try
	{
		CKnapsackProblem knapsackProblem(-20.0, std::vector<std::pair<double, double>>());
	}
	catch (std::exception e)
	{
		std::cout << "\n" << e.what();
	}
	catch (...)
	{
		std::cout << "ded3";
	}

	//incorrect values for GeneticAlgorithm
	try
	{
		CGeneticAlgorithm genericAlgorithm(100, 0.7, 0.1, 20, 3, nullptr);
	}
	catch (std::exception e)
	{
		std::cout << "\n" << e.what();
	}
	catch (...)
	{
		std::cout << "ded4";
	}

	//incorrect probability for GeneticAlgorithm
	try
	{
		CGeneticAlgorithm genericAlgorithm(100, 1.0, -0.1, 20, 3, nullptr);
	}
	catch (std::exception e)
	{
		std::cout << "\n" << e.what();
	}
	catch (...)
	{
		std::cout << "ded5";
	}
}

void runActualProblem()
try
{
	IProblem* problem = new CKnapsackProblem("test.txt");	//optimum is 1024!

	CGeneticAlgorithm ga(100, 0.7, 0.1, 50, 5, problem);

	ga.runSimulation();
	std::pair<double, std::vector<bool>> pair = ga.getBestResult();

	std::cout << "Fitness: " << pair.first << "\nWhat elements to pick: " << pair.second;

	delete problem;
}
catch (std::exception e)
{
	std::cout << e.what();
}
catch (...)
{
	std::cout << "Witchcraft! Impossible!";
}