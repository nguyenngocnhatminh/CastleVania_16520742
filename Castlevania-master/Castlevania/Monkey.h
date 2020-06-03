#pragma once
#include "Enemy.h"

#define MONKEY_STATE_IDLE 0
#define MONKEY_STATE_PREPARE 1
#define MONKEY_STATE_JUMP 2

#define MONKEY_ANI_IDLE 0
#define MONKEY_ANI_PREPARE 1
#define MONKEY_ANI_JUMP 2

#define MONKEY_SPEED_X 0.2f
#define MONKEY_SPEED_X_LOW 0.5f
#define MONKEY_SPEED_Y_HIGH 0.65f
#define MONKEY_SPEED_Y_LOW 0.25f
#define MONKEY_GRAVITY 0.002f
#define MONKEY_FALL_VY 0.2f

#define MONKEY_BBOX_WIDTH 32
#define MONKEY_BBOX_HEIGHT 32

#define RANGE_FROM_SIMON 200

#define TIME_PREPARE_TOJUMP 800

#define MONKEY_JUMP_RIGHT 1
#define MONKEY_JUMP_LEFT -1

#define MONKEY_OY_HEIGHT 30

#define MONKEY_HP 1
#define MONKEY_SCORE 500
class Monkey:public Enemy
{
	int state;
	bool isPrepare;
	DWORD time_prepare;
	int start_direction;

public:
	Monkey()
	{
		this->AddAnimation("MONKEY_ANI_IDLE");
		this->AddAnimation("MONKEY_ANI_PREPARE_JUMP");
		this->AddAnimation("MONKEY_ANI_JUMP");
		this->SetState(MONKEY_STATE_IDLE);
		isPrepare = false;
		this->SetHP(MONKEY_HP);
		this->SetScore(MONKEY_SCORE);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	int GetState();
	void SetStartDirection(int dir);
	int GetStartDirection();

};

