#pragma once
#include "Enemy.h"

#define RAVEN_BBOX_WIDTH 32
#define RAVEN_BBOX_HEIGHT 32

#define RAVEN_ANI_IDLE 0
#define	RAVEN_ANI_FLY 1
#define RAVEN_ANI_FLAP 2

#define RAVEN_STATE_IDLE 1
#define RAVEN_STATE_FLY_DOWN 2
#define RAVEN_STATE_FLY_STRAIGHT 3
#define RAVEN_STATE_FLAP 4
#define RAVEN_STATE_FLY_UP 5

#define RAVEN_FLY_VX 0.15f
#define RAVEN_FLY_VY 0.1f

#define RAVEN_DOWN_DISTANCE 50

#define RANGE_FROM_SIMON_Y 200
#define RANGE_FROM_SIMON_X 250

#define TIME_RAVEN_FLAP 500

#define RAVEN_DIRECTION_RIGHT 1
#define RAVEN_DIRECTION_LEFT -1

#define RAVEN_HP 1
class Raven:public Enemy
{
	int state;
	float start_y;
	DWORD time_flap;
public:
	Raven():Enemy()
	{
		this->AddAnimation("RAVEN_ANI_IDLE");
		this->AddAnimation("RAVEN_ANI_FLY");
		this->AddAnimation("RAVEN_ANI_FLAP");
		this->SetState(RAVEN_STATE_IDLE);
		this->SetHP(RAVEN_HP);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	int GetState();
	void SetStartY(float y)
	{
		this->start_y = y;
	}

};

