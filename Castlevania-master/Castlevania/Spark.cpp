#include "Spark.h"

Spark::Spark()
{
	AddAnimation("SPARK_ANI");
}


Spark::~Spark()
{
}

void Spark::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Effect::Update(dt,scene);
}


