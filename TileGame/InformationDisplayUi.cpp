#include "InformationDisplayUi.h"

InformationDisplayUi::InformationDisplayUi(): position{0,0}, infoLinkedTo{nullptr}
{
}

InformationDisplayUi::~InformationDisplayUi()
{
}

void InformationDisplayUi::Draw()
{
	if (infoLinkedTo != nullptr)
	{ 
		//std::cout << infoLinkedTo->GetTitle().c_str() << std::endl;
		DrawText(infoLinkedTo->GetTitle().c_str(), position.x, position.y, 20, WHITE);
	}
}
