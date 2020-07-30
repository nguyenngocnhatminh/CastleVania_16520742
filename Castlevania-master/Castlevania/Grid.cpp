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
#include "TypeConverter.h"
#include "Ground.h"
#include "SkeletonBlock.h"
#include "MoneyTrigger.h"
#include "BossTrigger.h"
#include "DeathZone.h"
#include"ItemCollection.h"
#include"Item.h"
#include "SitTrigger.h"
#include "Portal.h"
#include "Bridge.h"
#include"SpearGuard.h"
#include "Bat.h"
#include "Ghost.h"
#include "Skeleton.h"
#include "Monkey.h"
#include "Raven.h"
#include "Zombie.h"
#include "PhantomBat.h"

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

void Grid::LoadGrid(const std::string FilePath,Scene* scene)
{
	char* fileLoc = new char[FilePath.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc

#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, FilePath.size() + 1, FilePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// grid main property
	xml_node<>* rootNode = doc.first_node("grid");
	int cellSize = std::atoi(rootNode->first_attribute("cellSize")->value());;
	int id = std::atoi(rootNode->first_attribute("id")->value());;
	int  num_col = std::atoi(rootNode->first_attribute("numCol")->value());
	int  num_row = std::atoi(rootNode->first_attribute("numRow")->value());
	this->cellSize = cellSize;
	this->numXCell = num_col;
	this->numYCell = num_row;

	// create vector to hold objects
	this->cells.resize(numYCell);
	for (int i = 0; i < numYCell; i++)
		cells[i].resize(numXCell);

	for (size_t i = 0; i < numYCell; i++) {
		for (size_t j = 0; j < numXCell; j++) {
			this->cells[i][j].clear();
		}
	}

	for (xml_node<>* child = rootNode->first_node("objectgroup"); child; child = child->next_sibling()) //cú pháp lập
	{
		const std::string nodeName = child->name();
		if (nodeName != "objectgroup") // kiểm tra node có phải layer không cho chắc ăn
		{
			continue;// không phải tiếp tục vòng lặp
		}

		ObjectLayer* objectlayer;// object layer tượng chưng cho 1 object group

		const std::string name = std::string(child->first_attribute("name")->value());
		const int id = std::atoi(child->first_attribute("id")->value());
		std::map<int, ObjectTile*> objectgroup;

		// child  lúc này là 1 object group tại lần lập hiện tại
			//lập toàn bộ objectgroup node lấy ra thông tin các object
		for (xml_node<>* ggchild = child->first_node(); ggchild; ggchild = ggchild->next_sibling()) //cú pháp lập
		{
			//	const std::string ggname = std::string(ggchild->first_attribute("name")->value());
			const int ggid = std::atoi(ggchild->first_attribute("id")->value());
			const float x = std::atof(ggchild->first_attribute("x")->value());
			const float y = std::atof(ggchild->first_attribute("y")->value());
			const float width = std::atof(ggchild->first_attribute("width")->value());
			const float height = std::atof(ggchild->first_attribute("height")->value());

			const int row = std::atof(ggchild->first_attribute("row")->value());
			const int col = std::atof(ggchild->first_attribute("col")->value());

			std::string lName = "NONAME";
			xml_attribute<>* name = ggchild->first_attribute("name");
			if (name != NULL)
			{
				lName = name->value();
			}
			//ĐỌC PROPERTY CỦA OBJECT

			xml_node<>* propNode = ggchild->first_node("properties");
			ObjectTile* object = new ObjectTile(ggid, x, y, width, height,col,row);
			if (propNode != NULL)
			{
				std::map<std::string, OProperty*> properties;
				for (xml_node<>* pchild = propNode->first_node(); pchild; pchild = pchild->next_sibling()) //cú pháp lập
				{
					OProperty* property = new OProperty();
					property->name = std::string(pchild->first_attribute("name")->value());
					property->value = atoi(pchild->first_attribute("value")->value());
					properties.insert(std::make_pair(property->name, property));

				}
				object->SetProerties(properties);
			}



			//tạo 1 object

			// cho vào object group
			// khi kết thúc vòng lập ta lưu được hết các object trong group hiện tại
			// sau đó child sẽ là objectgroup tiếp theo trong map
			objectgroup.insert(std::make_pair(ggid, object));
		}
		// khởi tạo object group với id, name và các object con nằm trong nó
		objectlayer = new ObjectLayer(id, name, objectgroup);
		//cho objectgroup vào cái std::map lưu object của Map
		this->objectLayers.insert(std::make_pair(name, objectlayer));
	}
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);

		pScene->SetSimon(new CSIMON());

		pScene->GetSimon()->SetlastState(CGame::GetInstance()->GetSimonProp());


		CGame::GetInstance()->SetSimonProp(new SimonProperties());

		for (auto const& x : objectLayers)
		{
			ObjectID objID = string2EntityType.at(x.first);
			switch (objID)
			{
			case OPlayer:
				for (auto const& y : x.second->GetObjectGroup())
				{
					pScene->GetSimon()->setStartPoint(y.second->GetX());
					pScene->GetSimon()->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					try
					{
						pScene->GetSimon()->SetDirection(y.second->GetProperty("nx"));
						pScene->GetSimon()->SetState(y.second->GetProperty("state"));
						if (pScene->GetSimon()->GetState() >= 10 && pScene->GetSimon()->GetState() <= 17)
						{
							pScene->GetSimon()->SetIsOnStair(true);
						}
					}
					catch (exception ex)
					{
						pScene->GetSimon()->SetState(SIMON_STATE_IDLE);
						DebugOut(L"1 \n ");

					}
					pScene->GetSimon()->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(pScene->GetSimon());
				}
				break;
			case OGround:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Ground* ground = new Ground();
					ground->SetPosition(y.second->GetX(), y.second->GetY());
					ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
					ground->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(ground, true);
				}
				break;
			case OSkeletonBlock:
				for (auto const& y : x.second->GetObjectGroup())
				{
					SkeletonBlock* ground = new SkeletonBlock();
					ground->SetPosition(y.second->GetX(), y.second->GetY());
					ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
					ground->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(ground, true);
				}
				break;
			case ODeathZone:
				for (auto const& y : x.second->GetObjectGroup())
				{
					DeathZone* ground = new DeathZone();
					ground->SetPosition(y.second->GetX(), y.second->GetY());
					ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
					ground->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(ground, true);
				}
				break;
			case OBossTrigger:
				for (auto const& y : x.second->GetObjectGroup())
				{
					BossTrigger* trigger = new BossTrigger();
					trigger->SetPosition(y.second->GetX(), y.second->GetY());
					trigger->SetSize(y.second->GetWidth(), y.second->GetHeight());
					trigger->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(trigger, true);
				}
				break;
			case OMoneyBagTrigger:
				for (auto const& y : x.second->GetObjectGroup())
				{
					MoneyTrigger* trigger = new MoneyTrigger();
					trigger->SetPosition(y.second->GetX(), y.second->GetY());
					trigger->SetSize(y.second->GetWidth(), y.second->GetHeight());
					auto moneyBagLayer = objectLayers.at("MoneyBag");
					for (auto const& child : moneyBagLayer->GetObjectGroup())
					{
						ItemCollection* item = new ItemCollection();
						Item* mnBag = item->SpawnItem(y.second->GetProperty("item"), child.second->GetX());
						mnBag->SetIsHidden(true);
						mnBag->SetPosition(child.second->GetX(), child.second->GetY() - child.second->GetHeight());
						trigger->SetItem(mnBag);
					}
					trigger->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(trigger, true);
				}
				break;
			case OSitTrigger:
				for (auto const& y : x.second->GetObjectGroup())
				{
					SitTrigger* trigger = new SitTrigger();
					trigger->SetPosition(y.second->GetX(), y.second->GetY());
					trigger->SetSize(y.second->GetWidth(), y.second->GetHeight());
					auto moneyBagLayer = objectLayers.at("MoneyBag");
					for (auto const& child : moneyBagLayer->GetObjectGroup())
					{
						ItemCollection* item = new ItemCollection();
						Item* mnBag = item->SpawnItem(y.second->GetProperty("item"), child.second->GetX());
						mnBag->SetIsHidden(true);
						mnBag->SetPosition(child.second->GetX(), child.second->GetY() - child.second->GetHeight());
						trigger->SetItem(mnBag);
					}
					trigger->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(trigger, true);
				}
				break;
			case OTorch:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Torch* torch = new Torch();
					torch->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					torch->SetItem(y.second->GetProperty("item"));
					torch->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(torch);
				}
				break;
			case OPortal:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Portal* portal = new Portal();
					portal->SetSize(y.second->GetWidth(), y.second->GetHeight());
					portal->SetPosition(y.second->GetX(), y.second->GetY());
					portal->setNextMapId(y.second->GetProperty("Map_ID"));
					portal->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(portal);
				}
				break;
			case OSkeletonTrigger:
				for (auto const& y : x.second->GetObjectGroup())
				{
					SkeletonTrigger* trigger = new SkeletonTrigger();
					trigger->SetSize(y.second->GetWidth(), y.second->GetHeight());
					trigger->SetPosition(y.second->GetX(), y.second->GetY());
					trigger->SetDirection(y.second->GetProperty("Direction"));
					trigger->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(trigger, true);
				}
				break;
			case OCam:
				for (auto const& y : x.second->GetObjectGroup())
				{
					RECT cameraBoder;
					cameraBoder.left = y.second->GetX();
					cameraBoder.top = y.second->GetY();
					cameraBoder.right = y.second->GetX() + y.second->GetWidth();
					cameraBoder.bottom = y.second->GetY() + y.second->GetHeight();

					pScene->SetCamera(cameraBoder);
				}
				break;
			case OBossCamera:
				for (auto const& y : x.second->GetObjectGroup())
				{
					RECT boder;
					boder.left = y.second->GetX();
					boder.top = y.second->GetY();
					boder.right = y.second->GetX() + y.second->GetWidth();
					boder.bottom = y.second->GetY() + y.second->GetHeight();

					pScene->SetBossCamera(boder);
				}
				break;
			case OStair:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Stair* stair = new Stair();
					stair->SetSize(y.second->GetWidth(), y.second->GetHeight());
					stair->SetPosition(y.second->GetX(), y.second->GetY());
					stair->SetDirection(y.second->GetProperty("direction"));
					int x = y.second->GetProperty("isSpecial");
					stair->SetSpecial(x);
					stair->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(stair);
				}
				break;
			case OBirck:
				for (auto const& y : x.second->GetObjectGroup())
				{
					BreakWall* breakwall = new BreakWall();
					breakwall->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					breakwall->SetItem(y.second->GetProperty("item"));
					breakwall->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(breakwall,true);

				}
				break;
			case OCandle:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Candle* candle = new Candle();
					candle->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					candle->SetItem(y.second->GetProperty("item"));
					candle->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(candle);
				}
				break;
			case OBridge:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Bridge* bridge = new Bridge();
					bridge->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					bridge->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(bridge);

				}
				break;
			case OSpearGuard:
				for (auto const& y : x.second->GetObjectGroup())
				{
					SpearGuard* enemy = new SpearGuard();
					enemy->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetStarDirection(y.second->GetProperty("Direction"));
					enemy->SetRange(y.second->GetProperty("Range"));
					enemy->SetZone(y.second->GetProperty("Range"), y.second->GetX());
					enemy->SetType(y.second->GetProperty("Type"));
					enemy->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(enemy);

				}
				break;
			case OBat:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Bat* enemy = new Bat();
					enemy->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetStartY(y.second->GetY() - y.second->GetHeight());
					enemy->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(enemy);
				}
				break;
			case OGhost:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Ghost* enemy = new Ghost();
					enemy->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetStartDirection(y.second->GetProperty("Direction"));
					enemy->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(enemy);
				}
				break;
			case OMonkey:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Monkey* enemy = new Monkey();
					enemy->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetStartDirection(y.second->GetProperty("Direction"));
					enemy->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(enemy);
				}
				break;
			case OSkeleton:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Skeleton* enemy = new Skeleton();
					enemy->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetStartDirection(y.second->GetProperty("Direction"));
					enemy->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(enemy);
				}
				break;
			case ORaven:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Raven* enemy = new Raven();
					enemy->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetNx(y.second->GetProperty("Direction"));
					enemy->SetStartY(y.second->GetY());
					enemy->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(enemy);
				}
				break;
			case OZombie:
				for (auto const& y : x.second->GetObjectGroup())
				{
					Zombie* enemy = new Zombie();
					enemy->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetNx(y.second->GetProperty("Direction"));
					enemy->SetStartPositon(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					enemy->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(enemy);
				}
				break;
			case OBoss:
				for (auto const& y : x.second->GetObjectGroup())
				{
					PhantomBat* boss = new PhantomBat();
					boss->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					boss->SetCellIndex(y.second->GetColumn(), y.second->GetRow());
					AddDefaultGrid(boss);
				}
				break;
			default:
				break;
			}

		}
		if (pScene->GetSimon()->GetState() == SIMON_STATE_DIE)
		{
			pScene->GetSimon()->SetHp(16);
			pScene->GetSimon()->SetState(SIMON_STATE_IDLE);
			DebugOut(L"2\n ");
		}
	}

}

void Grid::AddDefaultGrid(LPGAMEOBJECT object, bool isAlwaysUpdate)
{
	CellIndex index = object->GetCellIndex();
	if (index.x > numXCell || index.y > numYCell - 1)
		return;

	if (!isAlwaysUpdate)
		this->cells[index.y][index.x].push_back(object);
	else
		alwaysUpdateObject.push_back(object);
}

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
	vector<LPGAMEOBJECT> ortheroject;

	enemiesobject.clear();
	itemobject.clear();
	subWeaponobject.clear();
	effectobject.clear();
	ortheroject.clear();

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
						ortheroject.push_back(obj);
					}
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
	listobjects.insert(listobjects.end(), ortheroject.begin(), ortheroject.end());
	listobjects.insert(listobjects.end(), itemobject.begin(), itemobject.end());
	listobjects.insert(listobjects.end(), enemiesobject.begin(), enemiesobject.end());
	listobjects.insert(listobjects.end(), subWeaponobject.begin(), subWeaponobject.end());
	listobjects.insert(listobjects.end(), effectobject.begin(), effectobject.end());
}

void Grid::Update(LPGAMEOBJECT object)
{
	float cx, cy;

	CGame::GetInstance()->GetCameraUI(cx, cy);

	float x, y;
	object->GetPosition(x, y);

	float l, t, r, b;
	object->GetBoundingBox(l, t, r, b);

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
