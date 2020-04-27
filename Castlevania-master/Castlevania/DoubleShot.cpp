#include "DoubleShot.h"

void DoubleShot::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Item::Update(dt, scene, colliable_objects);
}

void DoubleShot::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void DoubleShot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + DOUBLESHOT_WIDTH;
	b = y + DOUBLESHOT_HEIGHT;
}
