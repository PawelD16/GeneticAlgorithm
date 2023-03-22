#pragma once
#include <vector>

#include "CIndividual.h"
#include "CIncorrectProbabilityException.h"

//TESTED
//using default move, copy constructors and = operators, as there is nothing that cannot be shared! 

class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm(
		int stopCondition,
		double breedingProbability,
		double mutationProbability,
		int populationSize,
		int breedingPartakersAmount,
		IProblem* problem
	);
	CGeneticAlgorithm(const CGeneticAlgorithm& other) = default;
	CGeneticAlgorithm(CGeneticAlgorithm&& other) = default;
	~CGeneticAlgorithm() = default;

	CGeneticAlgorithm& operator=(const CGeneticAlgorithm& other) = default;
	CGeneticAlgorithm& operator=(CGeneticAlgorithm&& other) = default;

	std::pair<double, std::vector<bool>> getBestResult();
	void runSimulation();

private:
	double breedingProbability;
	double mutationProbability;
	int stopCondition;
	int populationSize;
	int	breedingPartakersAmount;
	std::vector<CIndividual> population;
	IProblem* problem;	//using a pointer as to allow myself to use inheriting IProblem classes
	std::mt19937 generator;

	CIndividual getBestIndividual(std::vector<CIndividual>& somePopulation);

	void calculateFitnessIfNotUpToDate();
	void mutateEntirePopulation();
	void deleteRandomIndividual(std::vector<CIndividual>& somePopulation);
	//void deleteWorstIndividual(std::vector<CIndividual>& somePopulation);
	void breedEntirePopulationWithAddidtionalIndividuals(std::vector<CIndividual>& newPopulation);
};