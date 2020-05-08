#pragma once
#include"HiddenObject.h"
#include"Enemy.h"
class EnemyTrigger :public HiddenObject
{
	Enemy* enemy;
public:
	EnemyTrigger() {};
	void SetItem(Enemy* i) { this->enemy = i; }
	Enemy* GetEnemy() { return this->enemy; }
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	void SetAttack()
	{
		this->enemy->SetIsAttack(true);
	}
};