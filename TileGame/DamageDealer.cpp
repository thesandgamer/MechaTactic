#include "DamageDealer.h"
#include "DamageData.h"


void DamageDealer::MakeDamages(LifeManager toDamages, DamageData data)
{
	toDamages.TakeDamages(data);
}
