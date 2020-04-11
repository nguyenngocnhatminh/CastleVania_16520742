#pragma once

#include"GameObject.h"

#define ITEM_GRAVITY			0.002f
#define ITEM_HIDING_TIME 300// chờ cho effect xong

#define BIGHEART 1
#define SMALLHEAR 2
#define DAGGER 3

class Item :public CGameObject
{
protected:
	DWORD life_time; // thời gian tồn tại của Item
	DWORD wait_time;// có vài item chờ cho effect xong mới xuất hiện
public:
	Item() :CGameObject() {
		wait_time = GetTickCount();
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

