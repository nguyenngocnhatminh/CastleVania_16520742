#include "ItemCollection.h"

Item* ItemCollection::SpawnItem(int id,int x)
{
	switch (id)
	{
		case BIGHEART:
			return new BigHeart();
			break;
		case SMALLHEART:
			return new Heart(x);
			break;
		case DAGGER:
			return new DaggerItem();
			break;
		case WHIP:
			return new WhipItem();
			break;
		case MONEYBAG:
			return new MoneyBag();
			break;
		case CROWN:
			return new Crown();
			break;
		case BOOMERANG:
			return new BoomerangItem();
			break;
		case DOUBLESHOT:
			return new DoubleShot();
			break;
		case HOLYWATER:
			return new HolyWaterItem();
			break;
		case AXE:
			return new AxeItem();
			break;
		case FOOD:
			return new Food();
			break;
		case GOLDPOTION:
			return new GoldPotion();
			break;
		case TRIPLESHOT:
			return new TripleShot();
			break;
	}
}

Item* ItemCollection::SpawnRandomItem(int x)
{
	int rank = 0 + rand() % (300 + 1 - 0);
	if (rank < 100)
	{
		return new Heart(x);
	}
	else if (rank < 150)
	{
		return new BigHeart();
	}
	else if (rank < 180)
	{	
		MoneyBag* item = new MoneyBag();
		item->SetState(MONEYBAG_RED);
		return item;

	}
	else if (rank < 190)
	{
		MoneyBag* item = new MoneyBag();
		item->SetState(MONEYBAG_BLUE);
		return item;
	}
	else if (rank < 200)
	{
		MoneyBag* item = new MoneyBag();
		item->SetState(MONEYBAG_WHITE);
		return item;
	}
	else if (rank < 240)
	{
		return new AxeItem();
	}
	//else if (rank < 280)
	//{
	//	// stopwatch
	//}
	else if (rank < 290)
	{
		return new HolyWaterItem();
	}
	else {
		return new BoomerangItem();
	}

}
