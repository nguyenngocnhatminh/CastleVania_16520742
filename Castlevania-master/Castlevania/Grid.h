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
public:
	void Add(LPGAMEOBJECT object,bool isAlwaysUpdate = false);
	void Update(LPGAMEOBJECT object);
	void GetListobject(vector<LPGAMEOBJECT>& listobjects);

	void RenderCell(RECT rec, int color, int alpha = 64);
	Grid(unsigned int mapWidth, unsigned int mapHeight);
	void Render();

	void CleanObject();
	~Grid();
};

