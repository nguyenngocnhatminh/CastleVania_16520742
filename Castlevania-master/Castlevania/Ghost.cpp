#include "Ghost.h"
#include "define.h"

void Ghost::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (this->isHidden == false)
	{
		l = x;
		t = y;
		r = x + GHOST_BBOX_WIDTH;
		b = y + GHOST_BBOX_HEIGHT;
	}

}

void Ghost::Render()
{
	if (this->isHidden)
		return;
	animations[0]->Render(nx, x, y);
}

void Ghost::SetStartDirection(int dir)
{
	this->start_direction = dir;
}

int Ghost::GetStartDirection()
{
	return this->start_direction;
}

void Ghost::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (this->IsDestroy())
		return;
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);

	if (this->isHidden)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			D3DXVECTOR2 cam = pScene->GetCamera();
			if(cam.x != 0)
			{
				if(this->start_direction==GHOST_DIRECTION_LEFT)
				{
					if (this->x + GHOST_BBOX_WIDTH > cam.x + SCREENSIZE::WIDTH)
					{
						this->isHidden = false;
						this->nx = GHOST_DIRECTION_LEFT;
					}
				}
				if (this->start_direction == GHOST_DIRECTION_RIGHT)
				{
					if (this->x > cam.x)
					{
						this->isHidden = false;
						this->nx = GHOST_DIRECTION_RIGHT;
					}
				}
			}
		}
	}

	if (!this->isHidden)
	{
		if (nx == GHOST_DIRECTION_LEFT)
		{
			if (dynamic_cast<PlayScene*>(scene))
			{
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				if (pScene->GetSimon()->x - this->x > RANGE_FROM_SIMON
					&& pScene->GetSimon()->x-this->x>0)
				{
					nx = GHOST_DIRECTION_RIGHT;
				}

			}
		}
		if (nx == GHOST_DIRECTION_RIGHT)
		{
			if (dynamic_cast<PlayScene*>(scene))
			{
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				if (this->x - pScene->GetSimon()->x - GHOST_BBOX_WIDTH > RANGE_FROM_SIMON
					&& this->x- pScene->GetSimon()->x >0)
				{
					nx = GHOST_DIRECTION_LEFT;
				}

			}
		}
		vx = nx * GHOST_SPEED_VX;
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