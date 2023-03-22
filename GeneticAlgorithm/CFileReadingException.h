#pragma once
#include <exception>

#include "Constants.h"

class CFileReadingException :public std::exception
{
public:
	CFileReadingException(const std::string& message, int pairNumber, const std::string& pathToSourceFile);
	CFileReadingException(const std::string& message, const std::string& pathToSourceFile);

	~CFileReadingException() = default;
};