﻿#include "ObjectLayer.h"

int ObjectTile::GetProperty(std::string key)
{
	if (this->properties.count(key)>0) 
	{
		return this->properties.at(key)->value;
	}
	return -999;
}
