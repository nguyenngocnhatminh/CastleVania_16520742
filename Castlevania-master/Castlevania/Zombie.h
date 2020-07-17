#pragma once
#include"Enemy.h"

#define ZOMBIE_BBOX_WIDTH 32
#define ZOMBIE_BBOX_HEIGHT 64

#define ZOMBIE_GRAVITY	0.002f
#define ZOMBIE_WALKING_SPEED 0.1f

#define ZOMBIE_HP 1
#define ZOMBIE_SCORE 100

#define ZOMBIE_DIRECTION_RIGHT 1
#define ZOMBIE_DIRECTION_LEFT -1

#define ZOMBIE_TIME_RESPAWN 1500
class Zombie:public Enemy
{
	bool isVisible;
	DWORD time_respawn;
	float start_x;
	float start_y;
public:
	Zombie():Enemy()
	{
		this->AddAnimation("ZOMBIE_ANI_WALKING");
		this->SetHP(ZOMBIE_HP);
		this->SetScore(ZOMBIE_SCORE);
		time_respawn = 0;
		isVisible = true;
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetStartPositon(int x, int y)
	{
		this->start_x = x;
		this->start_y = y;
	}
};

