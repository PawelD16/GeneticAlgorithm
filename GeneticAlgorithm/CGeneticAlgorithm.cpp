#include "CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm(
	int stopCondition,
	double breedingProbability,
	double mutationProbability,
	int populationSize,
	int breedingPartakersAmount,
	IProblem* problem
) :
	stopCondition(stopCondition),
	populationSize(populationSize),
	breedingProbability(breedingProbability),
	mutationProbability(mutationProbability),
	breedingPartakersAmount(breedingPartakersAmount),
	problem(problem),
	generator(std::random_device()())
{
	if (populationSize <= 0)
	{
		throw CIncorrectValueException(NOT_ENOUGH_INDIVIDUALS_INFO, 0);
	}

	if (breedingPartakersAmount > populationSize
		|| breedingPartakersAmount <= 0)
	{
		throw CIncorrectValueException(INCORRECT_BREEDING_PARTAKERS_AMOUNT_INFO, 0, populationSize);
	}

	if (breedingProbability < 0
		|| breedingProbability > 1)
	{
		throw CIncorrectProbabilityException(BREEDING_PROBABILITY);
	}
	if (mutationProbability < 0
		|| mutationProbability > 1)
	{
		throw CIncorrectProbabilityException(MUTATION_PROBABILITY);
	}

	if (stopCondition <= 0)
	{
		throw CIncorrectValueException(INCORRECT_STOP_CONDITION_INFO, 0);
	}

	if (problem == nullptr)
	{
		throw std::invalid_argument(NULLPTR_PROBLEM_INFO);
	}

	population.reserve(populationSize);

	for (int i = 0;i < populationSize;++i)
	{
		population.push_back(CIndividual(problem->getRequiredGeneSize(), generator));
	}
}

//O(2n) complexity, it doesn't matter if there are other ones with same fitness, only having the highest one matters
std::pair<double, std::vector<bool>> CGeneticAlgorithm::getBestResult()
{
	calculateFitnessIfNotUpToDate();

	CIndividual temp = std::move(getBestIndividual(population));
	return std::make_pair(temp.getFitness(), temp.getGenotype());
}

void CGeneticAlgorithm::runSimulation()
{
	std::vector<CIndividual> newPopulation;
	newPopulation.reserve(populationSize * 2);

	calculateFitnessIfNotUpToDate();

	for (int i = 0;i < stopCondition;++i)
	{
		//we find the best individual with each iteration and we do NOT change it
		CIndividual bestInCurrentPopulation = std::move(getBestIndividual(population));

		#pragma warning(suppress: 26800)
		breedEntirePopulationWithAddidtionalIndividuals(newPopulation);

		while ((int)newPopulation.size() > populationSize - 1)
		{
			deleteRandomIndividual(newPopulation);
		}

		population = std::move(newPopulation);

		mutateEntirePopulation();

		population.push_back(std::move(bestInCurrentPopulation));

		calculateFitnessIfNotUpToDate();
	}
}

CIndividual CGeneticAlgorithm::getBestIndividual(std::vector<CIndividual>& somePopulation)
{
	//no need to check size of population. It is guaranteed to be bigger than 0
	double maxCurrentFitness = population[0].getFitness();

	for (int i = 1;i < populationSize;++i)
	{
		if (population[i].getFitness() > maxCurrentFitness)
		{
			maxCurrentFitness = population[i].getFitness();
		}
	}

	for (int i = 0;i < populationSize;++i)
	{
		if (maxCurrentFitness == population[i].getFitness())
		{
			return population[i];
		}
	}
	return population[0];
}

void CGeneticAlgorithm::calculateFitnessIfNotUpToDate()
{
	for (int i = 0;i < population.size();++i)
	{
		population[i].calculateFitnessIfNotUpToDate(*problem);
	}
}

void CGeneticAlgorithm::mutateEntirePopulation()
{
	for (int i = 0;i < population.size();++i)
	{
		population[i].mutate(mutationProbability, generator);
	}
}

void CGeneticAlgorithm::deleteRandomIndividual(std::vector<CIndividual>& somePopulation)
{
	std::uniform_int_distribution<> distribInt(0, (int)(population.size() - 1));

	somePopulation.erase(somePopulation.begin() + distribInt(generator));
}

void CGeneticAlgorithm::breedEntirePopulationWithAddidtionalIndividuals(std::vector<CIndividual>& newPopulation)
{
	std::uniform_int_distribution<> distribInt(0, (int)(population.size() - 1));
	std::uniform_real_distribution<> distribReal(0.0, 1.0);

	while ((int)newPopulation.size() <= populationSize + 1)
	{
		std::list<CIndividual> parentsList;
		while (parentsList.size() < breedingPartakersAmount)
		{
			CIndividual candidate0 = population[distribInt(generator)];
			CIndividual candidate1 = population[distribInt(generator)];

			//choosing better suited parent by tournament
			//by copy (not moving and not directly reassigning) so we can reuse the parent and not have memory leaks
			if (candidate0.getFitness() < candidate1.getFitness())
			{
				parentsList.push_back(std::move(candidate1));
			}
			else
			{
				parentsList.push_back(std::move(candidate0));
			}
		}

		if (distribReal(generator) > breedingProbability)	//breeding unsucessfull
		{
			while (!parentsList.empty())
			{
				newPopulation.push_back(std::move(parentsList.front()));
				parentsList.pop_front();
			}
		}
		else //breeding sucessfull
		{
			std::vector<CIndividual> children = CIndividual::listSwitchBreed(parentsList);

			newPopulation.insert(
				newPopulation.end(),
				std::make_move_iterator(children.begin()),
				std::make_move_iterator(children.end())
			);
		}
	}
}