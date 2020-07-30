#include "SpearGuard.h"
#include"Ground.h"
void SpearGuard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y + 5;
	r = x + SPEAR_BBOX_WIDTH;
	b = y + SPEAR_BBOX_HEIGHT;
}

void SpearGuard::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	Enemy::Update(dt, scene, colliable_objects);
	CGameObject::Update(dt,scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);
	
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (pScene->GetSimon()->y < this->y)
		{
			if (!this->IsAttack())
				this->first_meet = true;
			this->SetIsAttack(true);
		}
		
	}

	if (this->Type == SPEAR_GUARD_NORMAL)
	{
		if (this->x + SPEAR_BBOX_WIDTH > this->MaxX)
			nx = SPEAR_GUARD_LEFT;
		if (this->x < this->MinX)
			nx = SPEAR_GUARD_RIGHT;
	}
	if (this->Type == IRONMAN)
	{
		if (this->first_meet == true)
		{
			nx = SPEAR_GUARD_RIGHT;
			Zone = ZONE_3;
			this->first_meet = false;
		}
		if (Zone == ZONE_1)
		{
			if ((this->x + SPEAR_BBOX_WIDTH) > (this->MaxX - this->range*2/3) && nx==SPEAR_GUARD_RIGHT)
			{
				nx = SPEAR_GUARD_LEFT;
				Zone = ZONE_2;
			}
			if (this->x < this->MinX)
				nx = SPEAR_GUARD_RIGHT;
		
		}
		if (Zone == ZONE_2)
		{
			if (this->x + SPEAR_BBOX_WIDTH > this->MaxX - this->range/3 && nx == SPEAR_GUARD_RIGHT)
			{
				nx = SPEAR_GUARD_LEFT;
				if (!IsAttack())
					Zone = ZONE_1;
				else Zone = ZONE_3;
			}
			if (!IsAttack())
			{
				if (this->x < this->MinX)
					nx = SPEAR_GUARD_RIGHT;
			}
			else 
			{
				if (this->x < MinX + range/3)
					nx = SPEAR_GUARD_RIGHT;
			}
		}
		if (Zone == ZONE_3)
		{
			if (this->x + SPEAR_BBOX_WIDTH > this->MaxX)
			{
				nx = SPEAR_GUARD_LEFT;
				Zone = ZONE_2;
			}
			if (this->x < this->MinX + this->range/3)
				nx = SPEAR_GUARD_RIGHT;
		}
	}
	vx = nx * SPEAR_GUARD_VX;

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny <= 0)
			y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->nx != 0)
				x += dx;
			else if (e->ny < 0) 
				y += dy;
		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void SpearGuard::SetStarDirection(int dir)
{
	this->Start_Direct = dir;
}

int SpearGuard::GetStartDirection()
{
	return this->Start_Direct;
}

void SpearGuard::SetZone(float range, float x)
{
	if (this->Start_Direct == SPEAR_GUARD_RIGHT)
	{
		MinX = x;
		MaxX = MinX + range;
	}
	if (this->Start_Direct == SPEAR_GUARD_LEFT)
	{
		MaxX = x + SPEAR_BBOX_WIDTH;
		MinX = MaxX - range;
	}

}

void SpearGuard::SetRange(float range)
{
	this->range = range;
}

float SpearGuard::GetRange()
{
	return this->range;
}

void SpearGuard::SetType(int type)
{
	this->Type = type;
}

int SpearGuard::GetType()
{
	return this->Type;
}

