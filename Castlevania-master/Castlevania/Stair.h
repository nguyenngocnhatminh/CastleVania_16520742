#pragma once
#include"HiddenObject.h"
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

