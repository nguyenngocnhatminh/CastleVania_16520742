#pragma once
#include"HiddenObject.h"
class BossTrigger :public HiddenObject
{
	float width;
	float height;
public:
	BossTrigger() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

