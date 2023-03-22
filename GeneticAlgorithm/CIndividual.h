#pragma once
#include <random>
#include <list>

#include "CKnapsackProblem.h"

//TESTED
class CIndividual
{
public:
	CIndividual(int genotypeSize, std::mt19937& generator);
	CIndividual(const CIndividual& other) = default;
	CIndividual(CIndividual&& other) = default;
	~CIndividual() = default;

	void mutate(double mutationProbability, std::mt19937& generator);
	static std::vector<CIndividual> listSwitchBreed(std::list<CIndividual>& toCrossBreed);

	void calculateFitnessIfNotUpToDate(IProblem& problem);
	double getFitness();
	std::vector<bool> getGenotype();

	CIndividual& operator=(const CIndividual& other) = default;
	CIndividual& operator=(CIndividual&& other) = default;

private:
	//used ONLY when crossBreeding to save unneded steps (filling the genotype), so it remains private
	CIndividual();

	std::vector<bool> genotype;	//special case for vector that allows bool to be 1bit, not 8 bits
	double fitness;
	bool isFitnessUpToDate;
};

std::ostream& operator<<(std::ostream& os, CIndividual& individual);