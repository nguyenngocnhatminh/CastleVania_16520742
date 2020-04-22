#pragma once
#include "Item.h"
#include"Heart.h"
#include "WhipItem.h"
#include"BigHeart.h"
#include"DaggerItem.h"
#include"MoneyBag.h"
#include "Crown.h"
#include"BoomerangItem.h"

#define BIGHEART 1
#define SMALLHEART 2
#define DAGGER 3
#define WHIP 4
#define MONEYBAG 5
#define CROWN 6
#define BOOMERANG 7

class ItemCollection
{
	int idItem;
public:
	Item* SpawnItem(int id);
};

