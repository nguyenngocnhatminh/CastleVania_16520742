#include "HolyWaterItem.h"

void HolyWaterItem::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void HolyWaterItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 32;
	b = y + 32;
}

void HolyWaterItem::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{

	Item::Update(dt, scene, colliable_objects);

}
