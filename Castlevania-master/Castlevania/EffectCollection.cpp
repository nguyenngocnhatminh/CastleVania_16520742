#include "EffectCollection.h"

Effect* EffectCollection::SpawnEffect(int id)
{
	switch (id)
	{
	case SPARK:
		return new Spark();
		break;
	case FLAME:
		return new Flame();
		break;

	}
}