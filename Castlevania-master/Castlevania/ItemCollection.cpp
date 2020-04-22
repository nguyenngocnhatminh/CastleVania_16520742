#include "ItemCollection.h"

Item* ItemCollection::SpawnItem(int id)
{
	switch (id)
	{
		case BIGHEART:
			return new BigHeart();
			break;
		case SMALLHEART:
			return new Heart();
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
	}
}