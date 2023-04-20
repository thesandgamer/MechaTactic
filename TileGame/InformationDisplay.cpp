#include "InformationDisplay.h"

InformationDisplay::InformationDisplay(string titleP): title{titleP}, position{nullptr}
{
}

InformationDisplay::InformationDisplay(): title {NULL}, position{ nullptr }
{
}

void InformationDisplay::SetPos(Vector3* pos)
{
	//std::cout << "Position ref in info: " << pos << std::endl;
	position = pos; 
}
