#include "Item.h"
#include"Ground.h"
#include "PlayScene.h"
#include "define.h"
#include "BreakWall.h"
void Item::Render()
{

}

void Item::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy)
	{
		return;
	}

	if (wait_time != 0 && GetTickCount() - wait_time > ITEM_HIDING_TIME)
	{
		wait_time = 0;
	}
	if (wait_time)
	{
		return;
	}

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (y < cam.y || y > cam.y + SCREENSIZE::HEIGHT - 100)
		{
			this->isDestroy = true;
		}

	}

	CGameObject::Update(dt, scene);
	vy += ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (ny <= 0)
			y += min_ty * dy + ny * 0.4f;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else if (dynamic_cast<BreakWall*>(e->obj)) {
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else
			{
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0)
					y += dy;
			}
		}

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	for (std::size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<Ground*>(e))
		{
			Ground* f = dynamic_cast<Ground*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b ; 
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				if ( this->y <= e->y) 
				{
					vy = 0;
				}
			}
		}
		if (dynamic_cast<BreakWall*>(e))
		{
			BreakWall* f = dynamic_cast<BreakWall*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b;
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				if (this->y <= e->y)
				{
					vy = 0;
				}
			}
		}
	}

}

void Item::SetScore(int score)
{
	this->score = score;
}

int Item::GetScore()
{
	return this->score;
}
