#pragma once
#include "SubWeapon.h"
#include"Dagger.h"
#include"Boomerang.h"

#define DAGGER 1
#define BOOMERANG 2
class SubWeaponCollection
{
	int id;
public:
	SubWeapon* SpawnSubWeapon(int id);
};


