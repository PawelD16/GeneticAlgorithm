#pragma once
#include <vector>

class IProblem
{
public:
	virtual ~IProblem() {}	//without virtual destructor, the derived one isn't called

	virtual double grade(std::vector<bool>& result) = 0;
	virtual int getRequiredGeneSize() = 0;
};