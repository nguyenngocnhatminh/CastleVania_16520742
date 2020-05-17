#pragma once
#include"Enemy.h"

#define BAT_STATE_IDLE 0
#define BAT_STATE_FLYING_DOWN 1
#define BAT_STATE_FLYING_STRAIGHT 2

#define BAT_ANI_IDLE 0
#define BAT_ANI_FLYING 1

#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32

#define BAT_FLY_SPEED_X  0.15f
#define BAT_FLY_SPEED_Y  0.15f

#define BAT_DOWN_DISTANCE 50

#define RANGE_FROM_SIMON_X 150
#define RANGE_FROM_SIMON_Y 100

#define BAT_HP 1
class Bat:public Enemy
{
	float start_y;
	int state;
public:
	Bat()
	{
		this->AddAnimation("BAT_ANI_IDLE");
		this->AddAnimation("BAT_ANI_FLYING");
		state = BAT_STATE_IDLE;
		this->SetHP(BAT_HP);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetState(int state);
	int GetState();
	void SetStartY(float y);
	float GetStartY();
};

