#pragma once
#include"Enemy.h"
#include"Ground.h"

#define SKELETON_STATE_IDLE -1
#define SKELETON_STATE_WALK 0
#define SKELETON_STATE_JUMP 1

#define SKELETON_ANI_WALK 0
#define SKELETON_ANI_JUMP 1

#define SKELETON_BBOX_WIDTH 32
#define SKELETON_BBOX_HEIGHT 64

#define SKELETON_SPEED_VX 0.06f
#define SKELETON_GRAVITY 0.002f
#define SKELETON_JUMP_VY 0.65f
#define SKELETON_JUMP_VX 0.15f
#define SKELETON_JUMPBACK_VX 0.2f
#define SKELETON_JUMPBACK_VY 0.4f


#define SKELETON_DIRECTION_RIGHT 1
#define SKELETON_DIRECTION_LEFT -1

#define RANGE_MAX_FROM_SIMON_X 180
#define RANGE_SKELETON_MOVE	64

#define SKELETON_HP 1

#define TIME_SPAWN_WEAPON 1500

struct MoveZone
{
	float MaxX;
	float MinX;
};


class Skeleton:public Enemy
{
	int state;
	float range_move;
	int start_direction;
	bool isBlock = false;
	MoveZone zone;
	MoveZone groundzone;
	bool isSpawnWeapon;
	bool spawnweapon;
	DWORD timespawnWeapon;
public:
	Skeleton():Enemy()
	{
		range_move = 0;
		this->AddAnimation("SKELETON_ANI_WALK");
		this->AddAnimation("SKELETON_ANI_JUMP");
		this->SetState(SKELETON_STATE_WALK);
		this->SetHP(SKELETON_HP);

	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) ;
	void SetState(int state);
	int GetState();
	void SetStartDirection(int dir);
	int GetStartDirection();
	MoveZone CaculatorZoneMove(CSIMON* simon);
	MoveZone CacualatorGroundZone(Ground* ground);
	void AutoWalk(MoveZone zone);
	void Jump(MoveZone groundzone);
	bool EqualZone(MoveZone zone,MoveZone groundzone);
	void SetisSpawnWeapon();
};

