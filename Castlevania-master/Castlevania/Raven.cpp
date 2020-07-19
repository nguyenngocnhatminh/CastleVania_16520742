#include "Raven.h"
#include "define.h"

void Raven::Render()
{
	int ani = 0;
	switch (state)
	{
	case RAVEN_STATE_IDLE:
		ani = RAVEN_ANI_IDLE;
		break;
	case RAVEN_STATE_FLY_DOWN:
		ani = RAVEN_ANI_FLY;
		break;
	case RAVEN_STATE_FLY_STRAIGHT:
		ani = RAVEN_ANI_FLY;
		break;
	case RAVEN_STATE_FLAP:
		ani = RAVEN_ANI_FLAP;
		break;
	case RAVEN_STATE_FLY_UP:
		ani = RAVEN_ANI_FLY;
		break;
	}
	animations[ani]->Render(nx, x, y);
}

void Raven::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + RAVEN_BBOX_WIDTH;
	b = y + RAVEN_BBOX_HEIGHT;
}

void Raven::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case RAVEN_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case RAVEN_STATE_FLY_DOWN:
		if (this->nx == RAVEN_DIRECTION_RIGHT)
			vx = RAVEN_FLY_VX;
		else vx = -RAVEN_FLY_VX;
		vy = RAVEN_FLY_VY;
		break;
	case RAVEN_STATE_FLY_STRAIGHT:
		if (this->nx == RAVEN_DIRECTION_RIGHT)
			vx = RAVEN_FLY_VX;
		else vx = -RAVEN_FLY_VX;
		vy = 0;
		break;
	case RAVEN_STATE_FLY_UP:
		if (this->nx == RAVEN_DIRECTION_RIGHT)
			vx = RAVEN_FLY_VX;
		else vx = -RAVEN_FLY_VX;
		vy = -RAVEN_FLY_VY;
		break;
	case RAVEN_STATE_FLAP:
		vx = 0;
		vy = 0;
		time_flap = GetTickCount();
		break;
	}
}

int Raven::GetState()
{
	return this->state;
}

void Raven::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{

	if (isDestroy)
	{
		return;
	}
	Enemy::Update(dt, scene, colliable_objects);
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (abs(pScene->GetSimon()->y - this->y) < RANGE_FROM_SIMON_Y &&
			abs(pScene->GetSimon()->x - this->x) < RANGE_FROM_SIMON_X)
		{
			this->SetIsAttack(true);
		}
		if (this->GetState() == RAVEN_STATE_IDLE || this->GetState() == RAVEN_STATE_FLAP)
		{
			if (this->nx == RAVEN_DIRECTION_RIGHT && this->x > pScene->GetSimon()->x)
				this->nx = RAVEN_DIRECTION_LEFT;
			else if (this->nx == RAVEN_DIRECTION_LEFT && this->x < pScene->GetSimon()->x)
				this->nx = RAVEN_DIRECTION_RIGHT;

		}
	}

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x || x>cam.x + SCREENSIZE::WIDTH)
		{
			if (this->IsAttack())
				this->Destroy();
		}
	}

	if (this->GetState() == RAVEN_STATE_FLAP)
	{
		if (GetTickCount() - this->time_flap >= TIME_RAVEN_FLAP && this->time_flap != 0)
		{
			this->SetStartY(this->y);
		}
	}

	if (this->IsAttack())
	{
		if (abs(this->y - this->start_y) > RAVEN_DOWN_DISTANCE)
		{
			if(this->GetState()!=RAVEN_STATE_FLAP)
				this->SetState(RAVEN_STATE_FLAP);
		}
		else
		{
			if (dynamic_cast<PlayScene*>(scene))
			{
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				if (this->y < pScene->GetSimon()->y)
					this->SetState(RAVEN_STATE_FLY_DOWN);
				else if (this->y+RAVEN_BBOX_HEIGHT > pScene->GetSimon()->y + SIMON_BBOX_HEIGHT)
					this->SetState(RAVEN_STATE_FLY_UP);
				else 
				{
					if (this->GetState() != RAVEN_STATE_FLY_STRAIGHT)
						this->SetState(RAVEN_STATE_FLY_STRAIGHT);
				}

			}
		}
	}
	


	if (this->GetState() == RAVEN_STATE_FLY_STRAIGHT)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			if (this->x >= pScene->GetSimon()->x + SIMON_BBOX_WIDTH + 30 && this->nx == RAVEN_DIRECTION_RIGHT)
			{
				this->vx = -RAVEN_FLY_VX;
			}
			else if (this->x <= pScene->GetSimon()->x - 30 && this->nx == RAVEN_DIRECTION_LEFT)
			{
				this->vx = RAVEN_FLY_VX;
			}
		}
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