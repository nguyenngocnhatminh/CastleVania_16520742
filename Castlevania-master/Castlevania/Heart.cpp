#include "Heart.h"
#include"Ground.h"
void Heart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + HEART_WIDTH;
	b = y + HEART_HEIGHT;
}
void Heart::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

//void Heart::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliableobject)
//{
//	if (GetTickCount() - wait_start > EFFECTS_LIFE_TIME)
//	{
//		this->isHiding = false;
//	}
//	if (this->isHiding)
//	{
//		return;
//	}
//	this->UpdateItem();
//	if (this->setDestroy) {
//		this->isDestroyed = true;
//		return;
//	}
//
//	CGameObject::Update(dt);
//	this->vy = HEART_MOVING_VY;
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//	coEventsResult.clear();
//	coEvents.clear();
//	CalcPotentialCollisions(colliableobject, coEvents);
//
//	if (coEvents.size() == 0)
//	{
//		y += dy;
//		x = HEART_OX_HEIGHT * sin(y * HEART_MOVING_VX) + ox;
//	}
//	else
//	{
//		float min_tx, min_ty, nx = 0, ny;
//
//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
//
//		// block 
//
//		for (UINT i = 0; i < coEventsResult.size(); i++)
//		{
//			LPCOLLISIONEVENT e = coEventsResult[i];
//			if (dynamic_cast<Ground*>(e->obj)) {
//				this->isTouchGround = true;
//				x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
//				y += min_ty * dy + ny * 0.1f;
//				if (nx != 0) vx = 0;
//				if (ny != 0) vy = 0;
//			}
//			else {
//				if (!this->isTouchGround)
//				{
//					y += dy;
//					x = HEART_OX_HEIGHT * sin(y * HEART_MOVING_VX) + ox;
//				}
//
//			}
//		}
//	}
//	// clean up collision events
//	for (std::size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
//}
