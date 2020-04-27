#include "AxeItem.h"

void AxeItem::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void AxeItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 30;
	b = y + 28;
}

void AxeItem::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{

	Item::Update(dt, scene, colliable_objects);

}
