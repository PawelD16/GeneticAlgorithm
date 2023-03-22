#include "CIncorrectProbabilityException.h"

CIncorrectProbabilityException::CIncorrectProbabilityException(const std::string& nameOfProbability) :
	CIncorrectValueException(
		nameOfProbability
		+ INCORRECT_PROBABILITY_INFO,
		0,
		1
	)
{
}