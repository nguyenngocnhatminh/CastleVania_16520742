#pragma once
#include"HiddenObject.h"
class DeathZone :public HiddenObject
{
	float width;
	float height;
public:
	DeathZone() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

