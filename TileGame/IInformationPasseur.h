#pragma once
#include <string>
using std::string;

class IInformationPasseur
{
public:
	virtual string GetInformationOf() = 0;

};