#include "CFileReadingException.h"

CFileReadingException::CFileReadingException(const std::string& message, int pairNumber, const std::string& pathToSourceFile) :
	std::exception((
		message
		+ AT_PAIR
		+ std::to_string(pairNumber)
		+ WHILE_READING_FILE
		+ pathToSourceFile
		).c_str()
	)
{
}

CFileReadingException::CFileReadingException(const std::string& message, const std::string& pathToSourceFile) :
	std::exception((
		message
		+ WHILE_READING_FILE
		+ pathToSourceFile
		).c_str()
	)
{
}