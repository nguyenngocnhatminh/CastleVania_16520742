#include "Bridge.h"
#include"Ground.h"
void Bridge::Render()
{
	if (!isDestroy)
	{
		animations[0]->Render(0, x, y);
	}
	RenderBoundingBox();
}

void Bridge::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy == false)
	{
		l = x;
		t = y;
		r = x + BRIDGE_BBOX_WIDTH;
		b = y + BRIDGE_BBOX_HEIGHT;
	}
}
void Bridge::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isDestroy)
	{
		return;
	}
	CGameObject::Update(dt, scene);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(colliable_objects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				this->vx = -vx;
			}
			else {
				if (nx != 0)
					x += dx;
				else if (nx != 0)
					y += dy;
			}
		}
	}
}
