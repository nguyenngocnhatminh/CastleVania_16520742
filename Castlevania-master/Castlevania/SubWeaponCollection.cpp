#include "SubWeaponCollection.h"

SubWeapon* SubWeaponCollection::SpawnSubWeapon(int id)
{
	switch (id)
	{
		case DAGGER:
			return new Dagger();
			break;
		case BOOMERANG:
			return new Boomerang();
			break;
		case HOLYWATER:
			return new HolyWater();
			break;
		case AXE:
			return new Axe();
			break;
		case STOPWATCH:
			return new StopWatch();
			break;
	}
}