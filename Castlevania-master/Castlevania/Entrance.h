#pragma once
#include"HiddenObject.h"
class Entrance :public HiddenObject
{
	int NextMapID;
public:
	Entrance() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	void setNextMapId(int id)
	{
		this->NextMapID = id;
	}
	int GetNextMapId() { return this->NextMapID; }
};

