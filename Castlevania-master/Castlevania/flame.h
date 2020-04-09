#pragma once
#include "Effect.h"
class flame:public Effect
{
public:
	flame() :Effect() {
		AddAnimation("FLAME_ANI_BURNING");
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

