#pragma once
#include "raylib.h"

struct DamageData;

//++ToDo: rajouter les critiques, si jamais tu fait énormément de damages

//++Question: Comment je peut faire pour qu'on puisse rajouter WIP WIP

class LifeManager
{
public:
	LifeManager();
	LifeManager(float MaxLife, float Armor );
	~LifeManager();

	void TakeDamages(DamageData data);

private:
	void Death();

	float maxLife{};
	float currentLife{};
	
	/// <summary>
	/// For damages reduciton, in %
	/// </summary>
	float armor{};


};

