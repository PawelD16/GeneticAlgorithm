#include "CIndividual.h"

CIndividual::CIndividual() :
	fitness(0.0),
	isFitnessUpToDate(false)
{
}

CIndividual::CIndividual(int genotypeSize, std::mt19937& generator) :
	fitness(0.0),
	isFitnessUpToDate(false)
{
	if (genotypeSize <= 0)
	{
		throw CIncorrectValueException(INCORRECT_GENOTYPE_SIZE_INFO, 0);
	}

	genotype.reserve(genotypeSize);	//sets a size for vector, so no additional memory allocations are required

	std::uniform_int_distribution<> distrib(0, 1);	//generate random 0 and 1, recommended in Instruction for project

	for (int i = 0;i < genotypeSize;++i)
	{
		genotype.push_back(distrib(generator));	//0 and 1 as bools!
	}
}

void CIndividual::mutate(double mutationProbability, std::mt19937& generator)
{
	isFitnessUpToDate = false;
	std::uniform_real_distribution<> distrib(0.0, 1.0);

	for (int i = 0;i < genotype.size();++i)
	{
		if (distrib(generator) <= mutationProbability)
		{
			genotype[i] = !genotype[i];
		}
	}
}

void CIndividual::calculateFitnessIfNotUpToDate(IProblem& problem)
{
	if (!isFitnessUpToDate)
	{
		fitness = problem.grade(genotype);
		isFitnessUpToDate = true;
	}
}

double CIndividual::getFitness()
{
	return fitness;
}

std::vector<bool> CIndividual::getGenotype()
{
	return genotype;
}

//n parent-child cross breeding
std::vector<CIndividual> CIndividual::listSwitchBreed(std::list<CIndividual>& toCrossBreed)
{
	std::vector<CIndividual> children;

	int children_amount = (int)toCrossBreed.size();
	int children_genotype_size = (int)toCrossBreed.front().genotype.size();

	children.reserve(children_amount);

	for (int i = 0;i < children_amount;++i)
	{
		children.push_back(CIndividual());
		children.back().genotype.reserve(children_genotype_size);
	}

	for (int i = 0;i < children_genotype_size;++i)
	{
		for (int j = 0;j < children_amount;++j)
		{
			children[j].genotype.push_back(toCrossBreed.front().genotype[i]);

			//shuffling the elements in list, treating as a queue, complexity O(1)
			toCrossBreed.push_front(std::move(toCrossBreed.back()));
			toCrossBreed.pop_back();
		}
	}

	return children;
}

std::ostream& operator<<(std::ostream& os, CIndividual& individual)
{
	std::vector<bool> temp = individual.getGenotype();

	os << "\nFitness: " << individual.getFitness();
	os << "\nSize of genepool: " << temp.size();
	os << "\nGenepool: {";

	for (int i = 0;i < temp.size() - 1;++i)
	{
		os << temp[i] << ", ";
	}

	if (temp.size() > 0)
	{
		os << temp[temp.size() - 1];
	}

	os << "}";

	return os;
}