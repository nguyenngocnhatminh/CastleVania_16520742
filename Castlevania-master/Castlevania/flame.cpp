#include "flame.h"


void Flame::Render()
{
	animations[0]->Render(0, x, y);
}

void Flame::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Effect::Update(dt, scene, colliable_objects);
}
