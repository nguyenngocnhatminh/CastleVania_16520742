#pragma once
#include"GameObject.h"

#define EFFECT_LIFE_TIME 300


class Effect :public CGameObject
{
	int lifetime;
public:
	Effect() :CGameObject() {
		lifetime = GetTickCount();
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


