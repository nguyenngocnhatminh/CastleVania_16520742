#include "Zombie.h"
#include "Ground.h"


void Zombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 2;
	right = left + ZOMBIE_BBOX_WIDTH;
	bottom = top + ZOMBIE_BBOX_HEIGHT ;
}

void Zombie::Render()
{
	if (this->isVisible == true)
	{
		animations[0]->Render(nx, x, y);
	}
}


void Zombie::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->IsDestroy())
	{
		this->isVisible = false;
		if (time_respawn != 0)
		{
			time_respawn = GetTickCount();
		}
	}
	if (time_respawn > 0)
	{
		if (GetTickCount() - time_respawn > 350)
		{
			this->SetPosition(start_x, start_y);
			this->isVisible = true;
			time_respawn = 0;
		}
	}
	//	if (reSpawn) return;
		//DebugOut(L"update \n");
	if (isVisible == true)
	{
		CGameObject::Update(dt, scene);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		//
		// TO-DO: make sure Goomba can interact with the world and to each of them too!
		// 
			// Simple fall down
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