#include "CKnapsackProblem.h"

//by copy so we can potentially use the same thing many times
CKnapsackProblem::CKnapsackProblem(
	double maxKnapsackCapacity,
	std::vector<std::pair<double, double>> valuesAndWeightsOfItems
) :
	maxKnapsackCapacity(maxKnapsackCapacity),
	valuesAndWeightsOfItems(valuesAndWeightsOfItems)
{
	if (maxKnapsackCapacity <= 0)
	{
		throw CIncorrectValueException(INCORRECT_CAPACITY_OF_KNAPSACK_INFO, 0);
	}

	if (valuesAndWeightsOfItems.size() <= 0)
	{
		throw CIncorrectValueException(INCORRECT_SET_SIZE_INFO, 0);
	}

	if (!nonNegativeElementsVectorOfPairs(valuesAndWeightsOfItems))
	{
		throw CIncorrectValueException(INCORRECT_WEIGHTS_OF_ITEMS_INFO);
	}
}

CKnapsackProblem::CKnapsackProblem(const std::string& pathToSourceFile):
	CKnapsackProblem(std::move(readInstanceFromFile(pathToSourceFile)))
{
}

CKnapsackProblem::CKnapsackProblem(const CKnapsackProblem& other) :
	maxKnapsackCapacity(other.maxKnapsackCapacity)
{
	valuesAndWeightsOfItems.reserve(other.valuesAndWeightsOfItems.size());

	for (std::pair<double, double> i : other.valuesAndWeightsOfItems)
	{
		valuesAndWeightsOfItems.push_back(i);
	}
}

double CKnapsackProblem::grade(std::vector<bool>& result)
{
	double sumOfValues = 0;
	double sumOfWeights = 0;

	for (int i = 0;i < result.size();++i)
	{
		if (result[i])
		{
			sumOfValues += valuesAndWeightsOfItems[i].first;
			sumOfWeights += valuesAndWeightsOfItems[i].second;
		}
	}

	return sumOfWeights <= maxKnapsackCapacity ? sumOfValues : 0.0;
}

int CKnapsackProblem::getRequiredGeneSize()
{
	return (int)valuesAndWeightsOfItems.size();	//values and weights of items have the same size
}

CKnapsackProblem CKnapsackProblem::readInstanceFromFile(const std::string& pathToSourceFile)
{
	std::ifstream myFile(pathToSourceFile);	//opens a file in std::ios:in mode (reading from file)

	if (!myFile)
	{
		throw CFileReadingException(FILE_NOT_FOUND_INFO, pathToSourceFile);
	}

	int itemsCount, pairNumber = 0;
	double newMaxKnapsackCapacity, value, weight;

	myFile >> itemsCount >> newMaxKnapsackCapacity;

	if (itemsCount <= 0)
	{
		throw CFileReadingException(INCORRECT_ITEMS_AMOUNT_INFO, pathToSourceFile);
	}


	if (newMaxKnapsackCapacity <= 0)
	{
		throw CFileReadingException(INCORRECT_CAPACITY_OF_KNAPSACK_INFO, pathToSourceFile);
	}


	std::vector<std::pair<double, double>> newValuesAndWeightsOfItems;
	newValuesAndWeightsOfItems.reserve(itemsCount);

	for (;pairNumber < itemsCount && myFile >> value >> weight;++pairNumber)
	{
		if (value < 0)
		{
			throw CFileReadingException(INCORRECT_VALUES_OF_ITEMS_INFO, pairNumber, pathToSourceFile);
		}

		if (weight < 0)
		{
			throw CFileReadingException(INCORRECT_WEIGHTS_OF_ITEMS_INFO, pairNumber, pathToSourceFile);
		}

		newValuesAndWeightsOfItems.push_back(std::make_pair(value, weight));
	}

	if (!myFile.eof() && !myFile)
	{
		throw CFileReadingException(INCORRECT_TYPE_INFO, pairNumber, pathToSourceFile);;
	}

	if (newValuesAndWeightsOfItems.size() != itemsCount || !myFile.eof())
	{
		throw CFileReadingException(INCORRECT_NUMBER_OF_ITEMS_INFO, pathToSourceFile);
	}

	myFile.close();

	return CKnapsackProblem(newMaxKnapsackCapacity, newValuesAndWeightsOfItems);
}

template<typename T, typename S>
bool nonNegativeElementsVectorOfPairs(std::vector<std::pair<T, S>>& vectorToCheck)
{
	for (int i = 0;i < vectorToCheck.size();++i)
	{
		if (vectorToCheck[i].first < 0 || vectorToCheck[i].second < 0)
		{
			return false;
		}
	}

	return true;
}