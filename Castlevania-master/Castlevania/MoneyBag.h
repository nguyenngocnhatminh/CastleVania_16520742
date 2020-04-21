#pragma once
#include"Item.h"
class MoneyBag :public Item
{
	bool isHiddenObject;
public:
	MoneyBag() :Item()
	{
		AddAnimation("MONEYBAG_ANI_COLOR");
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);


};

