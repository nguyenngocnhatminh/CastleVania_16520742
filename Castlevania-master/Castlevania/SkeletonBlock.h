#pragma once
#include"HiddenObject.h"
class SkeletonBlock :public HiddenObject
{
	float width;
	float height;
public:
	SkeletonBlock() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

