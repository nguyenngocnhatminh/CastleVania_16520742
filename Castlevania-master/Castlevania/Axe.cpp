#include "Axe.h"
#include"PlayScene.h"
#include"Ground.h"
void Axe::Render()
{
	animations[0]->Render(nx, x, y);
}

void Axe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + AXE_BBOX_WIDTH;
	b = y + AXE_BBOX_HEIGHT;
}

void Axe::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* coObjects)
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
	if (nx > 0 )
	{
		this->vx = AXE_SPEED_VX;
	}
	else if (nx < 0)
	{
		this->vx = -AXE_SPEED_VX;
	}

	vy += AXE_GRAVITY * dt;

	if (this->is_touchable_ground == true)
	{
		x += dx;
		y += dy;
	}
	SubWeapon::Update(dt, scene, coObjects);


}