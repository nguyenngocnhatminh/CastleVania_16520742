#pragma once
#include"GameObject.h"


class Torch:public CGameObject
{
public:
	Torch():CGameObject() {
		isDestroy = false;
		AddAnimation("TORCH_ANI");	//0	
	}
	virtual void Render();
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


