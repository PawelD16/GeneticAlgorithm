#include "CIncorrectValueException.h"

CIncorrectValueException::CIncorrectValueException(const std::string& nameOfValue, double lowerBoundary, double upperBoundary) :
	std::exception((
		nameOfValue
		+ MUST_BE_BETWEEN_INFO
		+ std::to_string(lowerBoundary)
		+ AND
		+ std::to_string(upperBoundary)
		).c_str()
	)
{
}

CIncorrectValueException::CIncorrectValueException(const std::string& nameOfValue, double lowerBoundary) :
	std::exception((
		nameOfValue
		+ MUST_BE_GREATER_THAN_INFO
		+ std::to_string(lowerBoundary)
		).c_str()
	)
{
}

CIncorrectValueException::CIncorrectValueException(const std::string& nameOfValue) :
	std::exception((
		nameOfValue
		+ CANNOT_BE_NEGATIVE_INFO
		).c_str()
	)
{
}