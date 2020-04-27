#include "DaggerItem.h"

void DaggerItem::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void DaggerItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 32;
	b = y + 30;
}

void DaggerItem::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{

	Item::Update(dt, scene, colliable_objects);

}
