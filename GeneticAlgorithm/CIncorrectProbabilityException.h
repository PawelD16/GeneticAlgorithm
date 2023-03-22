#pragma once
#include "CIncorrectValueException.h"

class CIncorrectProbabilityException :public CIncorrectValueException
{
public:
	CIncorrectProbabilityException(const std::string& nameOfProbability);

	~CIncorrectProbabilityException() = default;
};