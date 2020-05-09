﻿#include "Monkey.h"
#include "Ground.h"
#include "define.h"

void Monkey::Render()
{
	int ani = 0;
	switch (state)
	{
	case MONKEY_STATE_IDLE:
		ani = MONKEY_ANI_IDLE;
		break;
	case MONKEY_STATE_PREPARE:
		ani = MONKEY_ANI_PREPARE;
		break;
	case MONKEY_STATE_JUMP:
		ani = MONKEY_ANI_JUMP;
		break;
	}
	animations[ani]->Render(nx, x, y);
}

void Monkey::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MONKEY_BBOX_WIDTH;
	b = y + MONKEY_BBOX_HEIGHT;
}

void Monkey::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{

	CGameObject::Update(dt, scene);

	if (isDestroy)
	{
		return;
	}

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x || x>cam.x + SCREENSIZE::WIDTH)
		{
			if(IsAttack())
			{
				this->Destroy();
			}
		}
	}

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (!this->IsAttack())
		{
			if (this->nx == MONKEY_JUMP_RIGHT)
			{
				if (pScene->GetSimon()->x - this->x < RANGE_FROM_SIMON)
				{

					this->isPrepare = true;
				}
			}
			else
			{
				if (this->x - pScene->GetSimon()->x - MONKEY_BBOX_WIDTH < RANGE_FROM_SIMON)
				{
					this->isPrepare = true;
				}
			}
		}
		else
		{
			
			if (this->nx == MONKEY_JUMP_RIGHT)
			{
				if (this->x - pScene->GetSimon()->x - MONKEY_BBOX_WIDTH > RANGE_FROM_SIMON)
				{
					this->nx = MONKEY_JUMP_LEFT;
				}
			}
			else if (this->nx == MONKEY_JUMP_LEFT)
			{
				if (pScene->GetSimon()->x - this->x > RANGE_FROM_SIMON)
			{
				this->nx = MONKEY_JUMP_RIGHT;
			}
		}
			
		}
	}

	if (isPrepare)
	{
		this->SetState(MONKEY_STATE_PREPARE);
	}

	if (time_prepare == 0)
	{
		if (this->GetState() == MONKEY_STATE_PREPARE)
			this->time_prepare = GetTickCount64();
	}
	else if (GetTickCount64() - time_prepare > TIME_PREPARE_TOJUMP)
	{
		this->isPrepare = false;
		this->time_prepare = 0;
		this->SetIsAttack(true);
		this->SetState(MONKEY_STATE_JUMP);
	}



	vy += MONKEY_GRAVITY * dt;
	if (vx != 0)
	{
		if (this->nx == MONKEY_JUMP_RIGHT)
			vx = MONKEY_SPEED_X;
		if (this->nx == MONKEY_JUMP_LEFT)
			vx = -MONKEY_SPEED_X;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
			
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;	
		if (ny <= 0)
		y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				if (e->ny != 0)
				{
					if (GetState() == MONKEY_STATE_JUMP && vy >= 0) {
						if (IsAttack())
							this->SetState(MONKEY_STATE_PREPARE);
						else
							this->SetState(MONKEY_STATE_IDLE);
					}
					if (ny != 0) vy = 0;
				}
			}
			else
			{
				if (e->nx != 0) // va chạm chiều x
					x += dx;
				if (e->ny != 0)
					y += dy;
			}
		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

int Monkey::GetState() {
	return this->state;
}

void Monkey::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case MONKEY_STATE_IDLE:
		vx = 0;
		break;
	case MONKEY_STATE_PREPARE:
		vx = 0;
		break;
	case MONKEY_STATE_JUMP:
		vx = MONKEY_SPEED_X;
		if (isPrepare == true)
		{
			vy = -MONKEY_SPEED_Y_LOW;
		}
		else
		{
			if ((rand() % 2) + 1 == 2)
				vy = -MONKEY_SPEED_Y_LOW;
			else vy = -MONKEY_SPEED_Y_HIGH;
		}
		break;
	}
}

void Monkey::SetStartDirection(int dir)
{
	this->start_direction = dir;
	this->nx = dir;
}

int Monkey::GetStartDirection()
{
	return this->start_direction;
}