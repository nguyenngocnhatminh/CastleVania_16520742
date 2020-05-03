#pragma once
#include"HiddenObject.h"

#define STAIR_BOTTOM_RIGHT 0
#define STAIR_BOTTOM_LEFT 1
#define STAIR_TOP_RIGHT 2
#define STAIR_TOP_LEFT 3

class Stair:public HiddenObject
{
	int direction;
	bool isActive = false;
public:
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {}
	void SetActive(bool flag)
	{
		this->isActive = flag;
	}
	int GetDirection()
	{
		return this->direction;
	}
	void SetDirection(int direction)
	{
		this->direction = direction;
	}

	bool CheckActive() {
		return this->isActive;
	}
	Stair() {};
};

