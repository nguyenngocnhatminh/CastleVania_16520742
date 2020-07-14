#include "Grid.h"
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


Grid::Grid(unsigned int mapWidth, unsigned int mapHeight):mapWidth(mapWidth),mapHeight(mapHeight+80)
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


	this->alwaysUpdateObject.clear();
	this->staticOject.clear();
}

Grid::~Grid()
{}

void Grid::RenderCell(RECT rec, int color, int alpha)
{
	D3DXVECTOR3 p(rec.left, rec.top + 80, 0);
	RECT rect = { 0,0,0,0 };
	LPDIRECT3DTEXTURE9 bbox;
	switch (color)
	{
	case COLOR_RED:
		bbox = CTextures::GetInstance()->Get(ID_TEX_SPRITE_BBOX);
		break;
	case COLOR_BLUE:
		bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		break;
	default:
		bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		break;
	}

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)rec.right - (int)rec.left;
	rect.bottom = (int)rec.bottom - (int)rec.top;


	CGame::GetInstance()->DrawUI(true, 0 , rec.left, rec.top + 80, bbox, rect.left, rect.top, rect.right, rect.bottom, alpha);

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
			//CGame::GetInstance()->DrawUIText(_UIinfo, cell);
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

void Grid::AddToAlwayUpdateObjects(LPGAMEOBJECT object)
{
	this->alwaysUpdateObject.push_back(object);
}

void Grid::Add(LPGAMEOBJECT object)
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
	this->cells[cellY][cellX].push_back(object);
	
	if (dynamic_cast<Candle*>(object)
		|| dynamic_cast<Torch*>(object)
		|| dynamic_cast<BreakWall*>(object)
		//||dynamic_cast<BossZone*>(object)
		)
	{
		this->staticOject.push_back(object);
	}

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
}

void Grid::ResetStaticObject()
{
	for (size_t i = 0; i < this->staticOject.size(); i++)
	{
		LPGAMEOBJECT object = this->staticOject.at(i);
		if (object->IsDestroy())
		{
			object->isDestroy = false;
		}
	}
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
		if(object->CheckActive())
			if (dynamic_cast<Item*>(object)
				|| dynamic_cast<Enemy*>(object)
				|| dynamic_cast<SubWeapon*>(object))
			{
				//if (!dynamic_cast<PhantomBat*>(object))
				//{
				//	object->Destroy();
				//}
				object->Destroy();
			}
	}

	//ra khoi map => destroy
	if (x<-15 || x>mapWidth || y<0 || y>SCREENSIZE::HEIGHT)
	{
		object->Destroy();
	}

	CellIndex oldCell = object->GetCellIndex();
	//tim vi tri cu cua cell chua object
	//xem object dang o cell nao

	int cellX = (int)(x / this->cellSize);
	int cellY = (int)(y / cellSize);

	if (!dynamic_cast<Torch*>(object)
		&& !dynamic_cast<Candle*>(object)
		&& !dynamic_cast<BreakWall*>(object)
		/*&&!dynamic_cast<BoosZone*>(object)*/)
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
			// xóa luôn
			delete object;
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

void Grid::Update(float dt)
{

}

//void Grid::BuildGrid(const std::string& filePath)
//{
//	char* fileLoc = new char[filePath.size() + 1]; // 1
//
//	   //TODO: make multi format version of string copy
//#ifdef MACOS
//	strlcpy(fileLoc, file.c_str(), file.size() + 1);
//#else
//	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
//#endif 
//
//	//TODO: error checking - check file exists before attempting open.
//	rapidxml::file<> xmlFile(fileLoc);
//	rapidxml::xml_document<> doc;
//	doc.parse<0>(xmlFile.data());
//
//	xml_node<>* rootNode = doc.first_node("map");
//	xml_attribute<>* gridAtribute = rootNode->first_attribute("CellSize");
//	if (gridAtribute == NULL)
//	{
//		xml_attribute<>* atribute = doc.allocate_attribute("CellSize", "256");
//		rootNode->append_attribute(atribute);
//
//	}
//	else {
//		return;
//	}
//	for (xml_node<>* child = rootNode->first_node("objectgroup"); child; child = child->next_sibling()) {
//
//		int id = std::atoi(child->first_attribute("id")->value()); // lay ID Object group
//		std::string objectGroupName = std::string(child->first_attribute("name")->value()); // lay ten object group
//		for (xml_node<>* smailchild = child->first_node(); smailchild; smailchild = smailchild->next_sibling()) {
//			int x = 0, y = 0, w = 0, h = 0;
//			x = std::stof(smailchild->first_attribute("x")->value());
//			y = std::stof(smailchild->first_attribute("y")->value());
//			w = std::atoi(smailchild->first_attribute("width")->value());
//			h = std::atoi(smailchild->first_attribute("height")->value());
//			int scid = std::atoi(smailchild->first_attribute("id")->value()); // lay ID
//
//
//			xml_attribute<>* cellX = doc.allocate_attribute("cellcol", "256");
//			smailchild->append_attribute(cellX);
//
//
//
//		}
//
//
//
//	}
//
//
//	std::ofstream theFile(filePath.c_str());
//	theFile << doc;
//	theFile.close();
//}