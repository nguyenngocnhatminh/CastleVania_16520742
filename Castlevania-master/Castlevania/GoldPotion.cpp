#include "GoldPotion.h"

void GoldPotion::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Item::Update(dt, scene, colliable_objects);
}

void GoldPotion::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void GoldPotion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GOLDPOTION_WIDTH;
	b = y + GOLDPOTION_HEIGHT;
}

