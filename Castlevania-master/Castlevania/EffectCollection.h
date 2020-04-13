#pragma once
#include "Effect.h"
#include"Spark.h"
#include "flame.h"


#define SPARK 1
#define FLAME 2


class EffectCollection
{
	int idEffect;
public:
	Effect* SpawnEffect(int id);
};

