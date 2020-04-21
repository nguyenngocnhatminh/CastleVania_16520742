#pragma once
#include"GameObject.h"

#define CANDLE_BBOX_WIDTH  16
#define CANDLE_BBOX_HEIGHT 32

class Candle:public CGameObject
{
protected:
	int item;
public:
	Candle() :CGameObject() {
		this->item = 1;
		AddAnimation("CANDLE_ANI_BURNING");	//0	
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetItem() { return this->item; }
	void SetItem(int e) { this->item = e; }
};

