#pragma once
#include "SubWeapon.h"
#include"Dagger.h"
#include"Boomerang.h"
#include"HolyWater.h"
#include"Axe.h"
#include"StopWatch.h"

#define DAGGER 1
#define BOOMERANG 2
#define HOLYWATER 3
#define AXE 4
#define STOPWATCH 5
class SubWeaponCollection
{
	int id;
public:
	SubWeapon* SpawnSubWeapon(int id);
};


