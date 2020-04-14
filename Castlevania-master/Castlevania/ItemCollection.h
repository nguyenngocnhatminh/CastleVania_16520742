#pragma once
#include "Item.h"
#include"Heart.h"
#include "WhipItem.h"
#include"BigHeart.h"
#include"DaggerItem.h"
#include"MoneyBag.h"

#define BIGHEART 1
#define SMALLHEART 2
#define DAGGER 3
#define WHIP 4
#define MONEYBAG 5

class ItemCollection
{
	int idItem;
public:
	Item* SpawnItem(int id);
};

