#include "HolyWater.h"
#include"Ground.h"
#include"Simon.h"
void HolyWater::Render()
{
	int ani;
	if (state == HOLYWATER_STATE_JAR)
	{
		ani = HOLYWATER_ANI_JAR;
	}
	else
	{
		ani = HOLYWATER_ANI_BURNING;
	}
	animations[ani]->Render(nx,x, y);
}

void HolyWater::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->IsDestroy())
	{
		return;
	}
	if (this->setDestroy)
	{
		this->isDestroy = true;
		return;
	}
	if (state == HOLYWATER_STATE_JAR)
	{
		if (nx > 0)
		{
			this->vx = HOLYWATER_FALLING_VX;
		}
		else
		{
			this->vx = -HOLYWATER_FALLING_VX;
		}
	}

	vy += HOLYWATER_GRAVITY * dt;
	CGameObject::Update(dt,scene);

	if (this->burning_start == 0)
	{
		if (this->state == HOLYWATER_STATE_BURNING)
		{
			this->burning_start = GetTickCount64();
		}
	}
	else if (GetTickCount64() - burning_start > HOLYWATER_BURNING_TIME)
	{
		this->Destroy();
		return;
	}
	if (this->is_touchable_ground == true)
	{
		this->SetState(HOLYWATER_STATE_BURNING);
	}
	SubWeapon::Update(dt, scene, coObjects);

}

void HolyWater::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + HOLYWATER_BBOX_WIDTH;
	b = t + HOLYWATER_BBOX_HEIGHT;

}

void HolyWater::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case HOLYWATER_STATE_JAR:
		this->vy = -HOLYWATER_FALLING_VY;
		break;
	case HOLYWATER_STATE_BURNING:
	{
		this->vx = 0;
		this->vy = 0;
	}
	}
}
