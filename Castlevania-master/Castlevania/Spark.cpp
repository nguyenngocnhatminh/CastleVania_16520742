#include "Spark.h"


void Spark::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Effect::Update(dt,scene);
}



void Spark::Render()
{
	animations[0]->Render(0, x, y);
}
