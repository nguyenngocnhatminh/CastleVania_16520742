#pragma once
#include"Item.h"
class Crown :public Item
{
	bool isHiddenObject;
public:
	Crown() :Item()
	{
		AddAnimation("CROWN_ITEM_COLOR");
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);


};

