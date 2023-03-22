#pragma once
#include <fstream>

#include "Constants.h"
#include "IProblem.h"
#include "CFileReadingException.h"
#include "CIncorrectValueException.h"

//TESTED
class CKnapsackProblem : public IProblem
{
public:
	CKnapsackProblem(
		double maxKnapsackCapacity, 
		std::vector<std::pair<double, double>> valuesAndWeightsOfItems
	);
	CKnapsackProblem(const std::string& pathToSourceFile);
	CKnapsackProblem(const CKnapsackProblem& other);
	CKnapsackProblem(CKnapsackProblem&& other) = default;
	~CKnapsackProblem() = default;

	CKnapsackProblem& operator=(const CKnapsackProblem& other) = default;
	CKnapsackProblem& operator=(CKnapsackProblem&& other) = default;

	double grade(std::vector<bool>& result);
	int getRequiredGeneSize();

private:
	double maxKnapsackCapacity;
	std::vector<std::pair<double, double>> valuesAndWeightsOfItems;

	CKnapsackProblem readInstanceFromFile(const std::string& pathToSourceFile);
};

template<typename T, typename S>
bool nonNegativeElementsVectorOfPairs(std::vector<std::pair<T, S>>& vectorToCheck);