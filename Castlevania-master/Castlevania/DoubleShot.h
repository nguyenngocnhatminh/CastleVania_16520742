#pragma once
#include "GameObject.h"
#include"Item.h"

#define DOUBLESHOT_WIDTH  28
#define DOUBLESHOT_HEIGHT 28

#define SMALL_ANI_HEART 0
class DoubleShot : public Item
{

public:
	DoubleShot() :Item() {
		AddAnimation("DOUBLESHOT_ITEM_ANI");
		this->SetScore(ZERO_POINT);
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

