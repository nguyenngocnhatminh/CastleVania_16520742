#pragma once
#include"SubWeapon.h"

#define DAGGER_BBOX_WIDTH 32
#define DAGGER_BBOX_HEIGHT 18

#define DAGGER_VX 0.5f

class Dagger :public SubWeapon
{
public:
	Dagger() :SubWeapon() {
		AddAnimation("DAGGER_ITEM_ANI");
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void SetWidth() { this->width = DAGGER_BBOX_WIDTH; }
	virtual void SetHeight() { this->height = DAGGER_BBOX_HEIGHT; }
};

