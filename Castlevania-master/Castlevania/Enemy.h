#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#define TIME_BURN 400
#define TIME_HOLY 50

#define TIME_HURT 200

#include"Game.h"
#include"Debug.h"

class Enemy:public CGameObject
{
protected:
	int hp;
	DWORD start_point;
	bool isAttack = false;
	int score;
	bool isBurn = false;
	DWORD time_burn;

	bool isDameByHolywater = false;
	DWORD time_holywater;

	bool isHurt = false;
	DWORD time_hurt;

	bool isHurtByBom = false;
	bool isHurtByBomReturn = false;

	DWORD time_hurtbybom;
	DWORD time_hurtbybom_return;
public:
	bool isVisible;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetNx(int nx) {
		this->nx = nx;
	}
	void SetIsAttack(bool x);
	bool IsAttack();

	void SpawnItem();

	bool GetHurtByBom()
	{
		return this->isHurtByBom;
	}
	void SetTimeHurtByBom(DWORD dt)
	{
		this->time_hurtbybom = dt;
	}
	bool GetHurtByBomReturn()
	{
		return this->isHurtByBomReturn;
	}
	void SetTimeHurtByBomReturn(DWORD dt)
	{
		this->time_hurtbybom_return = dt;
	}

	void SetHurtByBom(bool x)
	{
		this->isHurtByBom = true;
	}
	void SetHurtByBomReturn(bool x)
	{
		this->isHurtByBomReturn = true;
	}

	bool GetHurt()
	{
		return this->isHurt;
	}

	void SetTimeBurn(DWORD dt)
	{
		this->time_burn = dt;
	}
	void SetBurn(bool x)
	{
		this->isBurn = x;
	}
	bool GetBurn()
	{
		return this->isBurn;
	}

	void SetTimeHoly(DWORD dt)
	{
		this->time_holywater = dt;
	}

	void SetIsDameByHoly(bool x)
	{
		this->isDameByHolywater = x;
	}
	bool GetIsDameByHoly()
	{
		return this->isDameByHolywater;
	}

	void SubtractHP(unsigned int point)
	{
		this->hp = this->hp - point;
		if (this->hp < 0)
			this->hp = 0;
		this->isHurt = true;
		this->time_hurt = GetTickCount();
	}
	unsigned int GetHP()
	{
		return this->hp;
	}

	void SetHP(int hp)
	{
		this->hp = hp;
	}

	int GetScore()
	{
		return this->score;
	}

	void SetScore(int score)
	{
		this->score = score;
	}

	Enemy() :CGameObject() {
	}
};

