#pragma once
#include "GameObject.h"
#include"Item.h"

#define HEART_WIDTH  16
#define HEART_HEIGHT 16
#define HEART_MOVING_VX 0.15f
#define HEART_MOVING_VY 0.05f
#define HEART_OX_HEIGHT 20 

class Heart : public Item
{
	int ox;
	bool isTouchGround = 0;
public:
	Heart() {
		AddAnimation("HEART_ANI_SMALL");
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	/*virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliableobjects);*/
};

