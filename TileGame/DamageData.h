#pragma once
#include "DamageDealer.h"

struct DamageData
{
	float Damages{};

	/// <summary>
	/// To ignore % of armor
	/// </summary>
	float ArmorPercing{};

	DamageDealer& whoMadeDamages;


};