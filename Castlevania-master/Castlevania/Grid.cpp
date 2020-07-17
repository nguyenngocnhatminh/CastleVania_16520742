﻿#include "Grid.h"
#include "Textures.h"
#include "Game.h"
#include"define.h"
#include "Enemy.h"
#include "Item.h"
#include "SubWeapon.h"
#include "Effect.h"
#include "Candle.h"
#include "Torch.h"
#include "BreakWall.h"


Grid::Grid(unsigned int mapWidth, unsigned int mapHeight):mapWidth(mapWidth),mapHeight(mapHeight+100)
{
	//ceil tra ve gia tri nguyen nho nhat sau so do 1.6 => 2, 2.3=>3
	this->numXCell = ceil((float)this->mapWidth / this->cellSize) + 1;
	this->numYCell = ceil((float)this->mapHeight / this->cellSize);

	//clear grid

	this->cells.resize(numYCell);

	for (int i = 0; i < numYCell; i++)
		cells[i].resize(numXCell);
	for (size_t i = 0; i < numYCell; i++)
	{
		for (size_t j = 0; j < numXCell; j++)
		{
			this->cells[i][j].clear();
		}
	}

}

Grid::~Grid()
{}

void Grid::CleanObject()
{
	if (numYCell > 0 && numXCell > 0)
	{
		for (size_t i = 0; i < numYCell; i++)
		{
			for (size_t j = 0; j < numXCell; j++)
			{
				this->cells[i][j].clear();
			}
		}
		this->alwaysUpdateObject.clear();
	}
}

void Grid::RenderCell(RECT rec, int color, int alpha)
{
	D3DXVECTOR3 p(rec.left, rec.top + 80, 0);
	RECT rect = { 0,0,0,0 };
	LPDIRECT3DTEXTURE9 bbox;
	switch (color)
	{
	case COLOR_RED:
		bbox = CTextures::GetInstance()->Get(ID_TEX_SPRITE_BBOX_RED);
		break;
	case COLOR_BLUE:
		bbox = CTextures::GetInstance()->Get(ID_TEX_SPRITE_BBOX_BLUE);
		break;
	default:
		bbox = CTextures::GetInstance()->Get(ID_TEX_SPRITE_BBOX_BLUE);
		break;
	}

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)rec.right - (int)rec.left;
	rect.bottom = (int)rec.bottom - (int)rec.top;


	CGame::GetInstance()->DrawUI(true, 0 , rec.left, rec.top, bbox, rect.left, rect.top, rect.right, rect.bottom, alpha);

}

void Grid::Render()
{
	float camx, camy;
	CGame::GetInstance()->GetCameraUI(camx, camy);
	//ham floor lay so nguyen lon nhat sau khi chia
	int startCol = floor(camx / this->cellSize);
	if (startCol > 0)
	{
		startCol -= 1;
	}
	else startCol = 0;

	int endCol = floor((camx + SCREENSIZE::WIDTH) / this->cellSize);
	if (endCol > numXCell)
	{
		endCol = numXCell;
	}
	else endCol = endCol + 1;

	for (int i = 0; i < numYCell; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			string _UIinfo = "";
							//left			top			right					bottom
			RECT cell = { j * cellSize,i * cellSize,j * cellSize + cellSize ,i * cellSize + cellSize };
			//so le mau cho de nhin :))
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
					RenderCell(cell, COLOR_RED, 100); 
				else
					RenderCell(cell, COLOR_BLUE, 100);
			}
			else
			{
				if (j % 2 == 0)
					RenderCell(cell, COLOR_BLUE, 100);
				else
					RenderCell(cell, COLOR_RED, 100);
			}
		}
	}

}

bool AABB(float l, float t, float r, float b, float l1, float t1, float r1, float b1)
{
	float left = l1 - r;
	float top = b1 - t;
	float right = r1 - l;
	float bottom = t1 - b;
	//  xét ngược lại cho nhanh hơn
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

void Grid::Add(LPGAMEOBJECT object, bool isAlwaysUpdate)
{
	float x_, y_;
	object->GetPosition(x_, y_);
	//tinh vi tri cua object
	int cellX = (int)(x_ / this->cellSize);
	int cellY = (int)(y_ / this->cellSize);
	if (cellX > numXCell)
	{
		DebugOut(L"Out of grid (numx)");
		return;
	}
	if (cellY > numYCell)
	{
		DebugOut(L"Out of grid (numy)");
		return;
	}

	object->SetCellIndex(cellX, cellY);
	if (!isAlwaysUpdate)
		this->cells[cellY][cellX].push_back(object);
	else
		alwaysUpdateObject.push_back(object);

}

void Grid::GetListobject(vector<LPGAMEOBJECT>& listobjects)
{
	//sap xep theo tung loai object
	vector<LPGAMEOBJECT> enemiesobject;
	vector<LPGAMEOBJECT> itemobject;
	vector<LPGAMEOBJECT> subWeaponobject;
	vector<LPGAMEOBJECT> effectobject;
	enemiesobject.clear();
	itemobject.clear();
	subWeaponobject.clear();
	effectobject.clear();

	float camx, camy;
	CGame::GetInstance()->GetCameraUI(camx, camy);
	int startCol = floor(camx / this->cellSize);
	if (startCol > 0)
	{
		startCol -= 1;
	}
	else startCol = 0;

	int endCol = floor((camx + SCREENSIZE::WIDTH) / this->cellSize);
	if (endCol > numXCell)
	{
		endCol = numXCell;
	}
	else endCol = endCol + 1;

	for (int i = 0; i < this->numYCell; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			for (size_t k = 0 ; k < this->cells[i][j].size(); k++)
			{
				LPGAMEOBJECT obj = this->cells[i][j].at(k);
				if (!obj->IsDestroy())
				{
					if (dynamic_cast<Enemy*>(obj))
					{
						enemiesobject.push_back(obj);
					}
					else if (dynamic_cast<Item*>(obj))
					{
						itemobject.push_back(obj);
					}
					else if (dynamic_cast<SubWeapon*>(obj))
					{
						subWeaponobject.push_back(obj);

					}
					else if (dynamic_cast<Effect*>(obj))
					{
						effectobject.push_back(obj);
					}
					else
					{
						listobjects.push_back(obj);
					}
				}
				else
				{
					DebugOut(L"khong nhan dien duoc object");
				}
			}
		}
	}

	for (size_t i = 0; i < this->alwaysUpdateObject.size(); i++)
	{
		LPGAMEOBJECT ob = alwaysUpdateObject.at(i);
		if (!ob->IsDestroy())
		{
			listobjects.push_back(ob);
		}
	}

	// lấy theo thứ tự
	listobjects.insert(listobjects.end(), itemobject.begin(), itemobject.end());
	listobjects.insert(listobjects.end(), enemiesobject.begin(), enemiesobject.end());
	listobjects.insert(listobjects.end(), subWeaponobject.begin(), subWeaponobject.end());
	listobjects.insert(listobjects.end(), effectobject.begin(), effectobject.end());
	DebugOut(L"List Object %d\n", listobjects.size());
}

void Grid::Update(LPGAMEOBJECT object)
{
	float cx, cy;

	CGame::GetInstance()->GetCameraUI(cx, cy);

	float x, y;
	object->GetPosition(x, y);

	float l, t, r, b;
	object->GetBoundingBox(l, t, r, b);

	if (AABB(l, t, r, b, cx, cy, cx + SCREENSIZE::WIDTH, cy + SCREENSIZE::HEIGHT))
	{
		object->SetActive();
	}
	else
	{
		if (object->CheckActive())
		{
			if (dynamic_cast<Item*>(object)
				|| dynamic_cast<Enemy*>(object))
			{
				object->Destroy();
			}
		}
	}

	CellIndex oldCell = object->GetCellIndex();
	//tim vi tri cu cua cell chua object
	//xem object dang o cell nao

	int cellX = (int)(x / this->cellSize);
	int cellY = (int)(y / cellSize);

	if (!dynamic_cast<Torch*>(object)
		&& !dynamic_cast<Candle*>(object)
		&& !dynamic_cast<BreakWall*>(object))
	{
		if (object->IsDestroy())
		{
			// loại bỏ cell cũ
			for (vector<LPGAMEOBJECT>::iterator it = cells[oldCell.y][oldCell.x].begin(); it != cells[oldCell.y][oldCell.x].end(); ) {
				if ((*it) == object) {
					it = cells[oldCell.y][oldCell.x].erase(it);
				}
				else ++it;
			}
			return;
		}
	}

	if (oldCell.x == cellX && oldCell.y == cellY)
	{
		return;
	}
	if (oldCell.x != -1 && oldCell.y != -1) // loại bỏ cell cũ
	{
		for (vector<LPGAMEOBJECT>::iterator it = cells[oldCell.y][oldCell.x].begin(); it != cells[oldCell.y][oldCell.x].end(); ) {
			if ((*it) == object) {
				it = cells[oldCell.y][oldCell.x].erase(it);
			}
			else ++it;
		}

	}

	//thêm lại vào cell mới
	Add(object);

}
