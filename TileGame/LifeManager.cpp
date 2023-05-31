#include "LifeManager.h"
#include <iostream>
#include "DamageData.h"

LifeManager::LifeManager() : lifeData{0,0,0}
{
}

LifeManager::LifeManager(float MaxLife, float Armor): lifeData{MaxLife,MaxLife,Armor}
{
}

LifeManager::~LifeManager()
{
}

void LifeManager::TakeDamages(DamageData data)
{
	float finalArmor = lifeData.armor - data.ArmorPercing;
	if (lifeData.armor - data.ArmorPercing <= 0) finalArmor = 0;
	float nextLife = lifeData.currentLife - ( data.Damages - 1*(finalArmor /100) );

	if (nextLife <= 0) Death();
	else 
	{
		lifeData.currentLife = nextLife;
		std::cout << "Have take damges, life now: " << lifeData.currentLife << std::endl;
	}
}

const LifeData& LifeManager::ReturnLifeData()
{
	return lifeData;
}

void LifeManager::Death()
{
	std::cout << "Death" << std::endl;
	//delete this;
}
