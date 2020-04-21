#include "Candle.h"

void Candle::Render()
{
	if (!isDestroy)
	{
		animations[0]->Render(0, x, y);
	}
	//RenderBoundingBox();
}

void Candle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy == false)
	{
		l = x;
		t = y;
		r = x + CANDLE_BBOX_WIDTH;
		b = y + CANDLE_BBOX_HEIGHT;
	}
}
void Candle::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (this->isDestroy)
	{
		return;
	}
	if (this->setDestroy)
	{
		isDestroy = true;
	}
}
