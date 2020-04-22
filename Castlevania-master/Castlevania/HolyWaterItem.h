#pragma once
#include"Item.h"

class HolyWaterItem :public Item
{
public:
	HolyWaterItem() :Item()
	{
		AddAnimation("HOLYWATER_ITEM_ANI");
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

