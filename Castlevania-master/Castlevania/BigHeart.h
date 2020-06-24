#pragma once
#include "GameObject.h"
#include"Item.h"

#define BHEART_WIDTH  25
#define BHEART_HEIGHT 20

#define SMALL_ANI_HEART 0
class BigHeart : public Item
{

public:
	BigHeart() :Item() {
		AddAnimation("HEART_ANI_BIG");
		this->SetScore(ZERO_POINT);
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

