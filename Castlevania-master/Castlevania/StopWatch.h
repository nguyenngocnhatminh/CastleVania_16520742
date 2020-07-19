#pragma once
#include"SubWeapon.h"
#define STOPWATCH_FREEZE_TIME 3000


class StopWatch :public SubWeapon
{

	DWORD stopwatch_start;
public:
	virtual void Render() {};
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void  GetBoundingBox(float& l, float& t, float& r, float& b) {
	};
	DWORD CheckFreezeTime() {
		return this->stopwatch_start;
	}


	StopWatch();
	~StopWatch();
};

