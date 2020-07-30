#pragma once
#include"Enemy.h"

#define SKELETON_WEAPON_BBOX_WIDTH 32
#define SKELETON_WEAPON_BBOX_HEIGHT 32

#define SKELETON_WEAPON_VY 0.6f

#define SKELETON_WEAPON_VX_01 0.2f
#define SKELETON_WEAPON_VX_02 0.25f
#define SKELETON_WEAPON_VX_03 0.3f

#define GRAVITY 0.002f

#define SKELETON_WEAPON_HP 1
#define SKELETON_WEAPON_SCORE 100
class SkeletonWeapon:public Enemy
{
public:
	SkeletonWeapon():Enemy()
	{
		this->AddAnimation("SKELETON_WEAPON_ANI");
		this->SetHP(SKELETON_WEAPON_HP);
		this->SetScore(SKELETON_WEAPON_SCORE);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetNxDirection(int nx) {
		this->nx = nx;
	}
};

