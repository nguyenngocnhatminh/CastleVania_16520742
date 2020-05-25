#pragma once
#include"SubWeapon.h"

#define AXE_GRAVITY 0.001f
#define AXE_SPEED_VX 0.2f
#define AXE_SPEED_VY 0.5f

#define AXE_BBOX_WIDTH 30
#define AXE_BBOX_HEIGHT 28

#define AXE_HEART_COST 1

class Axe :public SubWeapon
{
public:
	Axe()
	{
		AddAnimation("AXE_SUBWEAPON_ANI");
		this->vx = AXE_SPEED_VX;
		this->vy = -AXE_SPEED_VY;
		this->SetHeartCost(AXE_HEART_COST);
	}
	~Axe();
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coOjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};

