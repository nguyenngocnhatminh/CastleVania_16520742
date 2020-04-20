#include "BigHeart.h"

void BigHeart::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Item::Update(dt, scene, colliable_objects);
}

void BigHeart::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void BigHeart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BHEART_WIDTH;
	b = y + BHEART_HEIGHT;
}
