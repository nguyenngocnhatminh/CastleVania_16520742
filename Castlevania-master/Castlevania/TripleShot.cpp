#include "TripleShot.h"

void TripleShot::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Item::Update(dt, scene, colliable_objects);
}

void TripleShot::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void TripleShot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + TRIPLESHOT_WIDTH;
	b = y + TRIPLESHOT_HEIGHT;
}
