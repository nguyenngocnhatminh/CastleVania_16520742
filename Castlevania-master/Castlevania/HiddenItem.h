#pragma once
#include"HiddenObject.h"
#include"Item.h"
class HiddenItem:public HiddenObject
{
	Item* item;
public:
	HiddenItem();
	void SetItem(Item* item) { this->item = item; }
	Item* GetItem() { return this->item; }
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

