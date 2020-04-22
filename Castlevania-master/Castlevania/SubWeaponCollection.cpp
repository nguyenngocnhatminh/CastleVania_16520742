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
	}
}