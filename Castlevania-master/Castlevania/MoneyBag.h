#pragma once
#include"Item.h"

#define MONEYBAG_RED 0
#define MONEYBAG_BLUE 1
#define MONEYBAG_WHITE 2
#define MONEYBAG_COLORFUL 3

#define MONEYBAG_RED_SCORE 100
#define MONEYBAG_BLUE_SCORE 400
#define MONEYBAG_WHITE_SCORE 700
#define MONEYBAG_COLOR_SCORE 1000
class MoneyBag :public Item
{
	bool isHiddenObject;
	int state;
public:
	MoneyBag() :Item()
	{
		this->AddAnimation("MONEYBAG_ANI_RED");
		this->AddAnimation("MONEYBAG_ANI_BLUE");
		this->AddAnimation("MONEYBAG_ANI_WHITE");
		this->AddAnimation("MONEYBAG_ANI_COLOR");
		this->SetState(MONEYBAG_COLORFUL);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	int GetState();
};

