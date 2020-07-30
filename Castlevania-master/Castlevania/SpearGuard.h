#pragma once
#include"Enemy.h"
#define SPEAR_BBOX_WIDTH 32
#define	SPEAR_BBOX_HEIGHT 62

#define SPEAR_GUARD_RIGHT 1
#define SPEAR_GUARD_LEFT -1

#define SPEAR_GUARD_VX 0.05f

#define SPEAR_GUARD_NORMAL 1	//Con nguoi sat di chuyen het duong
#define IRONMAN 2 // Con nguoi sat di ca giat ca giat

#define ZONE_1 1
#define ZONE_2 2
#define ZONE_3 3

#define SPEAR_GUARD_HP 2
#define SPEAR_GUARD_SCORE 400
class SpearGuard:public Enemy
{
	int Type;
	float MaxX;
	float MinX;
	int Start_Direct;
	int Zone=1;
	float range;
	bool first_meet=false; // laan dau cham mat simon
public:
	SpearGuard():Enemy()
	{
		this->AddAnimation("SPEAR_GUARD_ANI");
		this->SetHP(SPEAR_GUARD_HP);
		this->SetScore(SPEAR_GUARD_SCORE);
	}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetStarDirection(int dir);
	int GetStartDirection();

	void SetZone(float range, float x);


	void SetRange(float range);

	float GetRange();

	void SetType(int type);

	int GetType();

	
};

