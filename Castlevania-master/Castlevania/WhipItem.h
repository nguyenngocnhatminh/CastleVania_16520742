#pragma once
#include"Item.h"
class WhipItem :public Item
{
public:
	WhipItem() :Item()
	{
		AddAnimation("MORNING_STAR_ANI");
	};
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);

};

