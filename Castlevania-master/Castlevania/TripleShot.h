#pragma once
#include "GameObject.h"
#include"Item.h"

#define TRIPLESHOT_WIDTH  30
#define TRIPLESHOT_HEIGHT 30


class TripleShot : public Item
{

public:
	TripleShot() :Item() {
		AddAnimation("TRIPLESHOT_ITEM_ANI");
		this->SetScore(ZERO_POINT);
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

