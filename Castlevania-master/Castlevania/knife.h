#pragma once
#include"SubWeapon.h"

#define KNIFE_BBOX_WIDTH 32
#define KNIFE_BBOX_HEIGHT 18

#define KNIFE_SPEED_X 0.5f
class knife:public SubWeapon
{
public:
	knife();
	~knife();

	virtual void Render();
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);


};


