#include "LifeManager.h"
#include <iostream>
#include "DamageData.h"

LifeManager::LifeManager() : maxLife{ 0 }, currentLife{ 0 }, armor{ 0 }
{
}

LifeManager::LifeManager(float MaxLife, float Armor): maxLife{MaxLife}, currentLife{maxLife},armor{Armor}
{
}

LifeManager::~LifeManager()
{
}

void LifeManager::TakeDamages(DamageData data)
{
	float finalArmor = armor - data.ArmorPercing;
	if (armor - data.ArmorPercing <= 0) finalArmor = 0;
	float nextLife = currentLife - ( data.Damages - 1*(finalArmor /100) );

	if (nextLife <= 0) Death();
	else 
	{
		currentLife -= nextLife;
	}
}

LifeData LifeManager::ReturnLifeData()
{
	return {maxLife,currentLife,armor};
}

void LifeManager::Death()
{
	std::cout << "Death" << std::endl;
}
