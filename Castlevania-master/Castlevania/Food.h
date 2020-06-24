#pragma once
#include "GameObject.h"
#include"Item.h"

#define FOOD_WIDTH  28
#define FOOD_HEIGHT 28

class Food : public Item
{

public:
	Food() :Item() {
		AddAnimation("FOOD_ANI");
		this->SetScore(ZERO_POINT);
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

