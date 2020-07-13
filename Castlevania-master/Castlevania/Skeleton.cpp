#include "Skeleton.h"
#include "Ground.h"
#include "SkeletonTrigger.h"
#include "define.h"
#include "SkeletonWeapon.h"
#include "SkeletonBlock.h"

void Skeleton::Render()
{
	int ani = 0;
	switch (state)
	{
	case SKELETON_STATE_IDLE:
		ani = SKELETON_ANI_JUMP;
		break;
	case SKELETON_STATE_WALK:
		ani = SKELETON_ANI_WALK;
		break;
	case SKELETON_STATE_JUMP:
		ani = SKELETON_ANI_JUMP;
		break;
	}

	animations[ani]->Render(nx, x, y);
}

void Skeleton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + SKELETON_BBOX_WIDTH;
	b = y + SKELETON_BBOX_HEIGHT;
}

void Skeleton::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);

	if (isDestroy)
	{
		return;
	}
	
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();
		if (cam.x != 0)
		{
			if (x > cam.x && x < cam.x + SCREENSIZE::WIDTH)
			{
				this->SetIsAttack(true);
			}
		}
	}
	if (this->IsAttack())
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			if (this->isBlock == false)
			{
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				zone = CaculatorZoneMove(pScene->GetSimon());
			}
		}
	}


	if (IsAttack())
	{
	
		if (this->GetState() == SKELETON_STATE_WALK)
		{
			if (isAutoWalk == false) // khong bi dung tuong
			{
				this->AutoWalk(zone);
			}
			else AutoWalkColliGround();
		}

	}


	vy += SKELETON_GRAVITY * dt;


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
					if (ny != 0) vy = 0;
					Ground* ground = dynamic_cast<Ground*>(e->obj);
					if (this->IsAttack())
					{
							if ((ground->x != groundzone.MinX && ground->x + ground->GetWidth() != groundzone.MaxX)
								|| (ground->x != groundzone.MaxX && ground->x + ground->GetWidth() != groundzone.MinX))
							{
								this->groundzone = CacualatorGroundZone(ground);
							}

							if (this->GetState() == SKELETON_STATE_JUMP)
							{
								this->SetState(SKELETON_STATE_WALK);
							}
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								if (this->EqualZone(zone, groundzone) == true)
								{
									this->SetState(SKELETON_STATE_JUMP);
								}
							}

					}
				}
				if (e->nx != 0)
				{
					this->vx = -vx;
					this->isAutoWalk = true;
				}
			}
			else if (dynamic_cast<SkeletonBlock*>(e->obj))
			{
				if (e->nx != 0)
				{
					this->vx = -vx;
					this->isAutoWalk = true;
				}
			}
			else
			{
				if (e->nx != 0) // va chạm chiều x
					x += dx;
				if(e->ny!=0)
					y += dy;
			}

		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	bool flagOnGround = false;
	for (std::size_t i = 0; i < colliable_objects->size(); i++)
	{
		LPGAMEOBJECT e = colliable_objects->at(i);
		if (dynamic_cast<Ground*>(e) && !flagOnGround) // BUG khi đứng lên brick
		{
			Ground* f = dynamic_cast<Ground*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b + 15; 
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				flagOnGround = true;
			}
		}
	}

	if (!flagOnGround)
	{
		if ( this->state != SKELETON_STATE_JUMP) {
			SetState(SKELETON_STATE_WALK);
		}

	}

	if (!this->spawnweapon && this->IsAttack())
	{
			SkeletonWeapon* weapon = new SkeletonWeapon();
			weapon->SetPosition(this->x, this->y);
			weapon->SetNxDirection(nx);
			if (dynamic_cast<PlayScene*>(scene))
			{
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				pScene->SpawnObject(weapon);
			}
			if (!weapon->IsDestroy())
			{
				this->spawnweapon = true;
			}
			this->timespawnWeapon = GetTickCount();
	}
	if (this->spawnweapon)
	{
		this->SetisSpawnWeapon();
	}
}


void Skeleton::SetisSpawnWeapon()
{
	if (GetTickCount() - this->timespawnWeapon > TIME_SPAWN_WEAPON && this->timespawnWeapon != 0)
	{
		this->spawnweapon = false;
	}
}

MoveZone Skeleton::CaculatorZoneMove(CSIMON* simon)
{
	MoveZone zone{};

	if (this->nx == SKELETON_DIRECTION_RIGHT)
	{
		zone.MinX = simon->x - RANGE_MAX_FROM_SIMON_X;
		zone.MaxX = zone.MinX + RANGE_SKELETON_MOVE;
	}
	else if (this->nx == SKELETON_DIRECTION_LEFT)
	{
		zone.MaxX = simon->x + RANGE_MAX_FROM_SIMON_X;
		zone.MinX = zone.MaxX - RANGE_SKELETON_MOVE;
	}

	return zone;
}




MoveZone Skeleton::CacualatorGroundZone(Ground* ground)
{
	MoveZone groundzone{};
	float minX = ground->x-5; //offset
	float maxX = ground->x + ground->GetWidth()+5;
	if (minX > maxX)
	{
		swap(minX, maxX);
	}
	groundzone.MinX = minX;
	groundzone.MaxX = maxX;
	return groundzone;
}


void Skeleton::AutoWalk(MoveZone zone)
{
	if (this->nx == SKELETON_DIRECTION_RIGHT)
	{
		if (this->x + SKELETON_BBOX_WIDTH >= zone.MaxX)
			this->vx = -SKELETON_SPEED_VX;
		if (this->x <= zone.MinX)
			this->vx = SKELETON_SPEED_VX;
	}
	else if (this->nx == SKELETON_DIRECTION_LEFT)
	{
		if (this->x - SKELETON_BBOX_WIDTH <= zone.MinX)
			this->vx = SKELETON_SPEED_VX;
		if (this->x >= zone.MaxX)
			this->vx = -SKELETON_SPEED_VX;
	}
}

void Skeleton::AutoWalkColliGround()
{
	this->rang_autowalk--;
	if (rang_autowalk == 0)
	{
		this->isAutoWalk = false;
		rang_autowalk = SKELETON_AUTOWALK_RANGE;
		this->vx = -vx;
	}
}

void Skeleton::Jump(MoveZone groundzone)
{
	if (this->nx == SKELETON_DIRECTION_RIGHT)
	{
		if (this->x + SKELETON_BBOX_WIDTH >= groundzone.MaxX)
		{
			vx = SKELETON_JUMP_VX;
			vy = -SKELETON_JUMP_VY;
		}
		else if (this->x <= groundzone.MinX)
		{
			vx = -SKELETON_JUMP_VX;
			vy = -SKELETON_JUMP_VY;
		}
	}
}

void Skeleton::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case SKELETON_STATE_WALK:
		vy = 0;
		break;
	case SKELETON_STATE_JUMP:
			if (this->x + SKELETON_BBOX_WIDTH >= groundzone.MaxX)
			{
				vx = SKELETON_JUMP_VX;
				vy = -SKELETON_JUMP_VY;
			}
			else if (this->x <= groundzone.MinX)
			{
				vx = -SKELETON_JUMP_VX;
				vy = -SKELETON_JUMP_VY;
			}
		break;
	case SKELETON_STATE_IDLE:
		break;
	}
}

int Skeleton::GetState()
{
	return this->state;
}

void Skeleton::SetStartDirection(int dir)
{
	this->nx = dir;
	this->start_direction = dir;
}
int Skeleton::GetStartDirection()
{
	return this->start_direction;
}

bool Skeleton::EqualZone(MoveZone zone, MoveZone groundzone)
{
	if (this->nx == SKELETON_DIRECTION_RIGHT)
	{
		if ((this->x + SKELETON_BBOX_WIDTH >= groundzone.MaxX && zone.MaxX >= groundzone.MaxX)
			|| (this->x <= groundzone.MinX && zone.MinX <= groundzone.MinX))
		{
			return true;
		}
	}
	else if (this->nx == SKELETON_DIRECTION_LEFT)
	{
		if ((this->x + SKELETON_BBOX_WIDTH >= groundzone.MaxX && zone.MaxX >= groundzone.MaxX)
			|| (this->x  <= groundzone.MinX && zone.MinX <= groundzone.MinX))
		{
			return true;
		}
	}
}