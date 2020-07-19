#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#include"Game.h"
#include"Debug.h"
class Enemy:public CGameObject
{
protected:
	int hp;
	DWORD start_point;
	bool isAttack = false;
	int score;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetNx(int nx) {
		this->nx = nx;
	}
	void SetIsAttack(bool x);
	bool IsAttack();

	void SpawnItem();

	void SubtractHP(unsigned int point)
	{
		this->hp = this->hp - point;
		if (this->hp < 0)
			this->hp = 0;
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

