#pragma once
#include"HiddenObject.h"
class Ground:public HiddenObject
{
	float width;
	float height;
public:
	Ground() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

