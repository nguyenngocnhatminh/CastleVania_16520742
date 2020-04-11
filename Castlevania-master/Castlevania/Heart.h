#pragma once
#include "GameObject.h"
#include"Item.h"

#define HEART_WIDTH  16
#define HEART_HEIGHT 16

class Heart : public Item
{
public:
	Heart() {
		AddAnimation("HEART_ANI_SMALL");
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

