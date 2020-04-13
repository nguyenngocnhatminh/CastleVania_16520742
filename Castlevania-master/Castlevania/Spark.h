#pragma once
#include "Effect.h"
class Spark :public Effect
{
public:
	Spark() :Effect() {
		AddAnimation("SPARK_ANI");
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

