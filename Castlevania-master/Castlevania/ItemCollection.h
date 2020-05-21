#pragma once
#include "Item.h"
#include"Heart.h"
#include "WhipItem.h"
#include"BigHeart.h"
#include"DaggerItem.h"
#include"MoneyBag.h"
#include "Crown.h"
#include"BoomerangItem.h"
#include"DoubleShot.h"
#include"HolyWaterItem.h"
#include"AxeItem.h"
#include"Food.h"
#include"GoldPotion.h"
#include"TripleShot.h"

#define BIGHEART 1
#define SMALLHEART 2
#define DAGGER 3
#define WHIP 4
#define MONEYBAG 5
#define CROWN 6
#define BOOMERANG 7
#define DOUBLESHOT 8
#define HOLYWATER 9
#define AXE 10
#define FOOD 11
#define GOLDPOTION 12
#define TRIPLESHOT 13
class ItemCollection
{
	int idItem;
public:
	Item* SpawnItem(int id,int x);
};

