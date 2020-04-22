#pragma once
#pragma once
#include "GameObject.h"
#include"Item.h"

#define GOLDPOTION_WIDTH  30
#define GOLDPOTION_HEIGHT 30

class GoldPotion : public Item
{

public:
	GoldPotion() :Item() {
		AddAnimation("GOLD_POTION_ANI");
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};



