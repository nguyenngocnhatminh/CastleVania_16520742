#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#include"Game.h"
#include"Debug.h"
class Enemy:public CGameObject
{
	int hp;
	DWORD start_point;
	bool isAttack = false;
	int ID;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {}
	void SetNx(int nx) {
		this->nx = nx;
	}
	void SetIsAttack(bool x);
	bool IsAttack();
	void SetID(int id);
	int GetID();


};

