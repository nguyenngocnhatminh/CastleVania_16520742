#include "Bat.h"
void Bat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BAT_BBOX_WIDTH;
	b = y + BAT_BBOX_HEIGHT;

}

void Bat::Render()
{
	int ani = 0;
	if(this->state==BAT_STATE_IDLE)
	{
		ani = BAT_ANI_IDLE;
		animations[ani]->Render(nx, x, y);
	}
	else
	{
		ani = BAT_ANI_FLYING;
		animations[ani]->Render(nx, x, y);
	}
}

int Bat::GetState()
{
	return this->state;
}

void Bat::SetState(int state)
{
	this->state = state;
	switch (state)
	{
		case BAT_STATE_IDLE:
		{
			vx = 0;
			vy = 0;
			break;
		}
		case BAT_STATE_FLYING_DOWN:
		{
			vx = BAT_FLY_SPEED_X;
			vy = BAT_FLY_SPEED_Y;
			break;
		}
		case BAT_STATE_FLYING_STRAIGHT:
		{
			vx = BAT_FLY_SPEED_X;
			vy = 0;
			break;
		}
	}
	

}

void Bat::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (pScene->GetSimon()->y -this->y < RANGE_FROM_SIMON_Y &&
			pScene->GetSimon()->x - this->x < RANGE_FROM_SIMON_X)
		{
			this->SetIsAttack(true);
		}

	}

	if(this->IsAttack())
	{
		if (this->y - this->start_y > BAT_DOWN_DISTANCE)
			this->SetState(BAT_STATE_FLYING_STRAIGHT);
		else
			this->SetState(BAT_STATE_FLYING_DOWN);
	}
	

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

void Bat::SetStartY(float y)
{
	this->start_y = y;
}

float Bat::GetStartY()
{
	return this->start_y;
}