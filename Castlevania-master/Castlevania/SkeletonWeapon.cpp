#include "SkeletonWeapon.h"
#include "define.h"

void SkeletonWeapon::Render()
{
	animations[0]->Render(nx, x, y);
}

void SkeletonWeapon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + SKELETON_WEAPON_BBOX_WIDTH;
	b = y + SKELETON_WEAPON_BBOX_HEIGHT;
}

void SkeletonWeapon::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);
	
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (y < cam.y || y > cam.y + SCREENSIZE::HEIGHT - 100)
		{
			this->isDestroy = true;
		}

	}

	if (this->isDestroy)
		return;

	if (!this->IsAttack())
	{
		vy = -SKELETON_WEAPON_VY;
		int a = rand() % 3 + 1;
		if (a == 1)
			vx = SKELETON_WEAPON_VX_01 * nx;
		else if (a == 2)
			vx = SKELETON_WEAPON_VX_02 * nx;
		else if (a == 3)
			vx = SKELETON_WEAPON_VX_03 * nx;
		this->SetIsAttack(true);
	}

	vy += GRAVITY * dt;
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
