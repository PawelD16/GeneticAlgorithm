#pragma once
#include <exception>

#include "Constants.h"

class CIncorrectValueException :public std::exception
{
public:
	CIncorrectValueException(const std::string& nameOfValue, double lowerBoundary, double upperBoundary);
	CIncorrectValueException(const std::string& nameOfValue, double lowerBoundary);

	//cannot be negative
	CIncorrectValueException(const std::string& nameOfValue);

	~CIncorrectValueException() = default;
};