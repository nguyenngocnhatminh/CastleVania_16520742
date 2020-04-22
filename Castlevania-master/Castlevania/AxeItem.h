#pragma once
#include"Item.h"

class AxeItem :public Item
{
public:
	AxeItem() :Item()
	{
		AddAnimation("AXE_ITEM_ANI");
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

