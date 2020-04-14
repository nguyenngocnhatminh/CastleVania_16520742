#pragma once
#include"GameObject.h"
#include "Item.h"

class Torch:public CGameObject
{
protected:
	int item;
public:
	Torch():CGameObject() {
		this->item = 1;
		AddAnimation("TORCH_ANI");	//0	
	}
	virtual void Render();
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetItem() { return this->item; }
	void SetItem(int e) { this->item = e; }
};


