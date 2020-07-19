#pragma once
#include<map>
#include"TileLayer.h"
#include<d3dx9.h>
#include<string>
#include"ObjectLayer.h"
#include<rapidxml/rapidxml.hpp>
#include<rapidxml/rapidxml_utils.hpp>
using namespace rapidxml;


struct TileSet
{
	int imageWidth;
	int imageHeight; 
	std::string name;
	int columns; 
	int rows;
	int tileCount;

	int tileWidth;
	int tileHeight;

};




class Map
{
private:
	int MapID;
	int width; 
	int height; 
	int TexID;
	int tileWidth;
	int tileHeight;
	TileSet tileSet;
	
	std::map<std::string, TileLayer*> layers;
	
	std::map<std::string, ObjectLayer*> objectLayers;
	void BuildMapLayer(xml_node<>* node);
	void BuildTileSet(xml_node<>* node);
	void BuildObjectLayer(xml_node<>* node);
public:

	int getWidth()
	{
		return this->width*tileWidth;
	}

	int getHeight()
	{
		return this->height*tileHeight;
	}

	std::map<std::string, ObjectLayer*> GetObjectLayer()
	{
		return objectLayers;

	}

	int GetMapID()
	{
		return this->MapID;
	}


	Map(int texID,int id) :width(0), height(0), tileWidth(0), tileHeight(0) 
	{ 
		this->MapID = id;
		this->TexID = texID;
	}
	void BuildMap(const std::string path);

	void Render(D3DXVECTOR2 camera);
	TileLayer* GetLayer(std::string name);
};

