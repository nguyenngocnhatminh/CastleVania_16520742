#pragma once
#include"HiddenObject.h"
#include"Item.h"
class MoneyTrigger :public HiddenObject
{
	Item* moneyBag;
public:
	MoneyTrigger() {};
	void SetItem(Item* i) { this->moneyBag = i; }
	Item* GetItem() { return this->moneyBag; }
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

