#include "Food.h"

void Food::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Item::Update(dt, scene, colliable_objects);
}

void Food::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Food::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FOOD_WIDTH;
	b = y + FOOD_HEIGHT;
}
