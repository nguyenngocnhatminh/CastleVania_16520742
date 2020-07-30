#pragma once
#include"SubWeapon.h"

#define HOLYWATER_GRAVITY 0.0015f
#define HOLYWATER_FALLING_VX 0.25f
#define HOLYWATER_FALLING_VY 0.2f

#define HOLYWATER_BURNING_TIME 1000
#define HOLYWATER_BURNING_ATTACK_TIME 200 
#define HOLYWATER_STATE_JAR 0
#define HOLYWATER_STATE_BURNING 100

#define HOLYWATER_ANI_JAR 0
#define HOLYWATER_ANI_BURNING 1



#define HOLYWATER_BBOX_WIDTH 32
#define HOLYWATER_BBOX_HEIGHT 28

#define HOLYWATER_HEART_COST 1
class HolyWater:public SubWeapon
{
	int state;
	DWORD burning_start;
	DWORD burningAttack_start;
	bool collideOneTime = false;
	bool hitObject = false;
	public:
	HolyWater():SubWeapon()
	{
		AddAnimation("HOLYWATER_ANI_JAR");
		AddAnimation("HOLYWATER_ANI_BURNING");
		this->SetState(HOLYWATER_STATE_JAR);
		this->SetHeartCost(HOLYWATER_HEART_COST);
		this->SetDame(1);
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coOjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};

