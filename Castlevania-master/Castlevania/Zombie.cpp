#include "Zombie.h"
#include "Ground.h"
#include "define.h"


void Zombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->isVisible == true)
	{
		left = x;
		top = y + 2;
		right = left + ZOMBIE_BBOX_WIDTH;
		bottom = top + ZOMBIE_BBOX_HEIGHT;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Zombie::Render()
{
	if (this->isVisible == true)
	{
		animations[0]->Render(nx, x, y);
	}
	RenderBoundingBox();
}


void Zombie::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, scene, coObjects);
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x < cam.x || y < cam.y || y > cam.y + SCREENSIZE::HEIGHT)
		{
			this->SetDestroy();
		}

	}

	if (this->setDestroy)
	{
		this->isVisible = false;
		if (time_respawn == 0)
		{
			time_respawn = GetTickCount();
		}
		this->setDestroy = false;
	}			
	if (time_respawn > 0)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			CSIMON* simon = pScene->GetSimon();
			if ((simon->x + SCREENSIZE::WIDTH / 2 <= this->start_x && this->nx < 0)
				|| (this->start_x + SCREENSIZE::WIDTH / 2 <= simon->x && this->nx > 0))
			{
				if (GetTickCount() - time_respawn > ZOMBIE_TIME_RESPAWN)
				{
					this->SetPosition(start_x, start_y);
					this->isVisible = true;
					time_respawn = 0;
				}
			}

		}
	}
	
	if (isVisible == true)
	{
		CGameObject::Update(dt, scene);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);

		vy += ZOMBIE_GRAVITY * dt;
		if (nx == ZOMBIE_DIRECTION_RIGHT) vx = ZOMBIE_WALKING_SPEED;
		else if (nx == ZOMBIE_DIRECTION_LEFT) vx = -ZOMBIE_WALKING_SPEED;


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
				if (dynamic_cast<Ground*>(e->obj)) {
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;

				}
				else {
					if (e->nx != 0)
						x += dx;
					else if (e->ny < 0) {
						y += dy;
					}

				}
			}


		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}