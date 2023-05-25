#pragma once
#include "raylib.h"

#include "DamageData.h"

//++ToDo: rajouter les critiques, si jamais tu fait énormément de damages

//++Question: Comment je peut faire pour qu'on puisse rajouter WIP WIP

/// <summary>
/// 
/// </summary>
struct LifeData
{
	float maxLife{};
	float currentLife{};
	/// <summary>
	/// For damages reduciton, in %
	/// </summary>
	float armor{};
};

class LifeManager
{
public:
	LifeManager();
	LifeManager(float MaxLife, float Armor );
	~LifeManager();

	void TakeDamages(DamageData data);

	const LifeData& ReturnLifeData();


private:
	void Death();

	LifeData lifeData{0,0,0};

	
	



};

