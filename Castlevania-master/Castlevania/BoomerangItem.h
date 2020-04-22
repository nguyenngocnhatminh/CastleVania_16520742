#pragma once
#include"Item.h"

class BoomerangItem :public Item
{
public:
	BoomerangItem() :Item()
	{
		AddAnimation("BOOMERANG_ITEM_ANI");
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

