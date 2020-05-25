#pragma once
#include"SubWeapon.h"

#define BOOMERANG_BBOX_WIDTH 30
#define BOOMERANG_BBOX_HEIGHT 30

#define BOOMERANG_VX 0.35f

#define BOOMERANG_HEART_COST 1

class Boomerang :public SubWeapon
{
	int boomerang_range = 50;
public:
	Boomerang() :SubWeapon() {
		AddAnimation("BOOMERANG_ANI");
		this->SetHeartCost(BOOMERANG_HEART_COST);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void SetWidth() { this->width = BOOMERANG_BBOX_WIDTH; }
	virtual void SetHeight() { this->height = BOOMERANG_BBOX_HEIGHT; }
};

