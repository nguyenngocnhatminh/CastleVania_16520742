#include "flame.h"


void flame::Render()
{
	animations[0]->Render(0, x, y);
}

void flame::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Effect::Update(dt, scene, colliable_objects);
}
