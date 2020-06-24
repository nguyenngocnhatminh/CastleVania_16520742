#pragma once
#include"Item.h"

#define CROWN_ITEM_SCORE 1000
class Crown :public Item
{
	bool isHiddenObject;
public:
	Crown() :Item()
	{
		AddAnimation("CROWN_ITEM_COLOR");
		this->SetScore(CROWN_ITEM_SCORE);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);


};

