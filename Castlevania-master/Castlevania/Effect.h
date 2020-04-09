#pragma once
#include"GameObject.h"

#define EFFECT_LIFE_TIME 300

#define Spark_Effect 0
#define Flame_Effect 1

class Effect :public CGameObject
{
	int life_time;
public:
	Effect() :CGameObject() {
		life_time = GetTickCount();
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


