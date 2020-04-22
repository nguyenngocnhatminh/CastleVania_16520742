#pragma once
#include"HiddenObject.h"
class Portal :public HiddenObject
{
	int NextMapID;
public:
	Portal() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	void setNextMapId(int id)
	{
		this->NextMapID = id;
	}
	int GetNextMapId() { return this->NextMapID; }
};

