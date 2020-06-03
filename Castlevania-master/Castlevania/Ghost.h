#pragma once
#include"Enemy.h"

#define GHOST_STATE_NORMAL 0
#define GHOST_STATE_ATTACK 1

#define GHOST_BBOX_WIDTH 32
#define GHOST_BBOX_HEIGHT 32

#define GHOST_DIRECTION_RIGHT 1
#define GHOST_DIRECTION_LEFT -1

#define GHOST_SPEED_VX 0.15f

#define RANGE_FROM_SIMON 100
#define GHOST_HP 2
#define GHOST_SCORE 300
class Ghost:public Enemy
{
	bool isHidden;
	int start_direction;
public:
	Ghost():Enemy()
	{
		isHidden = true;
		this->AddAnimation("GHOST_ANI");
		this->SetHP(GHOST_HP);
		this->SetScore(GHOST_SCORE);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetStartDirection(int dir);
	int GetStartDirection();
};

