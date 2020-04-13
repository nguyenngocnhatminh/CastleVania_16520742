#pragma once
#include "SubWeapon.h"
#include"Dagger.h"

#define DAGGER 1
class SubWeaponCollection
{
	int id;
public:
	SubWeapon* SpawnSubWeapon(int id);
};


