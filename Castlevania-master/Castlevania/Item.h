#pragma once

#include"GameObject.h"

#define ITEM_GRAVITY			0.002f
#define ITEM_HIDING_TIME 300// chờ cho effect xong

#define BIGHEART 1
#define SMALLHEAR 2
#define DAGGER 3
#define MONEYBAG 4
#define CROWN 5

class Item :public CGameObject
{
protected:
	bool isHiddenObject;
	DWORD life_time; 
	DWORD wait_time;
	int score;
public:
	Item() :CGameObject() {
		wait_time = GetTickCount();
		score = 0;
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetIsHidden(bool flag) { this->isHiddenObject = flag; }
	bool GetIsHidden() { return this->isHiddenObject; }
	void SetScore(int score);
	int GetScore();
};

