#pragma once
#include"HiddenObject.h"
#define RANGE_FROM_SIMON_X 120
#define RANGE_FROM_SIMON_Y 120
class SkeletonTrigger :public HiddenObject
{
	bool isActive;
	int Direction;
	int ID;
public:
	SkeletonTrigger() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	void SetDirection(int dir)
	{
		this->Direction = dir;
	}
	int GetDirection()
	{
		return this->Direction;
	}
};

