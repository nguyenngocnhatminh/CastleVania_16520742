#include "BreakWall.h"

void BreakWall::Render()
{
	int ani = 0;
	if (state == BREAKWALL_STATE_NORMAL)
	{
		ani = BREAKWALL_ANI_NORMAL;
	}
	else
	{
		ani = BREAKWALL_ANI_BREAK;
	}
	animations[ani]->Render(0,x,y);
	RenderBoundingBox();
}

void BreakWall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy == false)
	{
		l = x;
		t = y;
		r = x + BREAKWALL_BBOX_WIDTH;
		b = y + BREAKWALL_BBOX_HEIGHT;
	}
}
void BreakWall::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
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
