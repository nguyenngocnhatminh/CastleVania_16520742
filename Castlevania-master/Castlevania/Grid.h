#pragma once
#include<vector>
#include"GameObject.h"
#include<vector>
#include<Windows.h>
#include<string>
#include"Library/RapidXML//rapidxml.hpp"
#include"Library/RapidXML//rapidxml_utils.hpp"

using namespace rapidxml;
#define CELL_SIZE 256
#define COLOR_RED 0 
#define COLOR_BLUE 1

typedef std::vector<LPGAMEOBJECT> cellObjects;

typedef std::vector<LPGAMEOBJECT> cellObjects;


class Grid
{
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int cellSize = CELL_SIZE;

	unsigned int numXCell;
	unsigned int numYCell;

	std::vector<std::vector<cellObjects>> cells; //mang 2 chieu luu object
	std::vector<LPGAMEOBJECT> alwaysUpdateObject;
	std::vector<LPGAMEOBJECT> staticOject;
public:
	void RenderCell(RECT rec, int color, int alpha = 64);

	void BuildGrid(const std::string& filePath);
	void Add(LPGAMEOBJECT object);
	void AddToAlwayUpdateObjects(LPGAMEOBJECT object);
	void Update(LPGAMEOBJECT object);
	void Update(float dt);
	void ResetStaticObject();
	void GetListobject(vector<LPGAMEOBJECT>& listobjects);
	Grid(unsigned int mapWidth, unsigned int mapHeight);
	void Render();
	~Grid();
};

