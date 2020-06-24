#pragma once
#include"Item.h"

class BoomerangItem :public Item
{
public:
	BoomerangItem() :Item()
	{
		AddAnimation("BOOMERANG_ITEM_ANI");
		this->SetScore(ZERO_POINT);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

