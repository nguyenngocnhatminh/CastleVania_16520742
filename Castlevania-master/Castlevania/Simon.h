#pragma once
#include "GameObject.h"
#include"Whip.h"
#include "HiddenObject.h"
#include"knife.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.6f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING_RIGHT 1
#define SIMON_STATE_WALKING_LEFT 2
#define SIMON_STATE_SIT 3
#define SIMON_STATE_JUMP 4
#define SIMON_STATE_FIGHT_STAND 5
#define SIMON_STATE_FIGHT_SIT 6
#define SIMON_STATE_DIE 7


#define SIMON_ANI_IDLE 0 
#define SIMON_ANI_WALKING 1  
#define SIMON_ANI_SIT 2 
#define SIMON_ANI_STAND_ATTACK				3
#define SIMON_ANI_SIT_ATTACK				4
#define SIMON_ANI_DIE				8






#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BIG_BBOX_WIDTH  60
#define SIMON_BIG_BBOX_HEIGHT 63

#define SIMON_SMALL_BBOX_WIDTH  13
#define SIMON_SMALL_BBOX_HEIGHT 15

#define SIMON_UNTOUCHABLE_TIME 5000







class CSIMON : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD fight_start;
	int state;
	Whip* whip;

public: 
	CSIMON() : CGameObject()
	{
		level = SIMON_LEVEL_BIG;
		untouchable = 0;
		this->fight_start = 0;
		state = SIMON_STATE_IDLE; // trạng thái ban đầu cần khai báo khi tạo object
		whip = new Whip();
		AddAnimation("SIMON_ANI_IDLE");	//0	
		AddAnimation("SIMON_ANI_WALKING");//	1	
		AddAnimation("SIMON_ANI_SIT");//	2	
		AddAnimation("SIMON_ANI_STAND_ATTACK");//	2	
		AddAnimation("SIMON_ANI_SIT_ATTACK");//	2	
	}
	~CSIMON() { delete whip; }
	void ResetFightAnimation()
	{
		this->animations[SIMON_ANI_STAND_ATTACK]->ResetFrame();
		this->animations[SIMON_ANI_SIT_ATTACK]->ResetFrame();
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	Whip* GetWhip() { return whip; };
	void SetState(int state);
	void SetDirection(int nx) { this->nx = nx; }
	DWORD GetFightTime()
	{
		return this->fight_start;	
	}

	void ResetFightTime()
	{
		this->fight_start = 0;
	
	}



	int GetState() {
		return this->state;
	}
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};