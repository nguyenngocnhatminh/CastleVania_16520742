#include "PlayScene.h"
#include "define.h"
#include"Game.h"
#include"Textures.h"

#include"HiddenObject.h"
#include"Ground.h"
#include"debug.h"
#include"Torch.h"
#include"MoneyTrigger.h"
#include"ItemCollection.h"
#include"Portal.h"
#include"Stair.h"
#include"Candle.h"
#include"BreakWall.h"
#include"TypeConverter.h"
#include "Bridge.h"
#include"SpearGuard.h"
#include"Bat.h"
#include"Ghost.h"
#include"Monkey.h"
#include"Skeleton.h"
#include "SkeletonTrigger.h"
#include "Raven.h"
#include "Zombie.h"
#include "SitTrigger.h"
#include "BossTrigger.h"
#include "PhantomBat.h"
#include "DeathZone.h"
#include "SkeletonBlock.h"

void PlayScene::LoadSprite(const std::string& filePath, const int tex)
{
	// ở đây mình truyền vào man
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();


	LPDIRECT3DTEXTURE9 objecttex = textures->Get(tex);
	// đọc vào file xml
	char* fileLoc = new char[filePath.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc
#



	   //TODO: make multi format version of string copy
	// phần này k quan tâm lắm dạng như cú pháp thôi
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());


	xml_node<>* rootNode = doc.first_node("resource");
	xml_node<>* spriteSheetNode = rootNode->first_node("spritesheet");

	// lập toàn bộ các node con của node gamedata

	for (xml_node<>* child = spriteSheetNode->first_node(); child; child = child->next_sibling())
	{

		const std::string& ID = std::string(child->first_attribute("ID")->value());

		xml_node<>* frameNode = child->first_node("frame");



		int x = std::atoi(frameNode->first_attribute("x")->value());
		int y = std::atoi(frameNode->first_attribute("y")->value());
		int w = std::atoi(frameNode->first_attribute("width")->value());
		int h = std::atoi(frameNode->first_attribute("height")->value());

		int r = x + w;
		int b = y + h;

		sprites->Add(ID, x, y, r, b, objecttex);
	}




}
void PlayScene::LoadAnimation(const string& filePath)
{
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	char* fileLoc = new char[filePath.size() + 1];
#

#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 


	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* rootNode = doc.first_node("resource");
	xml_node<>* aniNode = rootNode->first_node("animations");


	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{

		const std::string& ID = std::string(child->first_attribute("ID")->value());
		int timeLoop = std::atoi(child->first_attribute("defaulttime")->value());
		ani = new CAnimation(timeLoop);
		for (xml_node<>* grand = child->first_node(); grand; grand = grand->next_sibling())
		{
			const std::string& spriteID = std::string(grand->first_attribute("spriteID")->value());

			ani->Add(spriteID);
		}

		animations->Add(ID, ani);


	}


}
D3DXVECTOR2 PlayScene::GetCamera()
{
	return CGame::GetInstance()->GetCamera();
}
void PlayScene::Load()
{
	this->LoadDefault();
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	const std::string filePath = this->MapPath;

	char* fileLoc = new char[filePath.size() + 1];
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 


	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());


	xml_node<>* rootNode = doc.first_node("Base");

	xml_node<>* texNode = rootNode->first_node("textures");

	for (xml_node<>* child = texNode->first_node(); child; child = child->next_sibling())
	{
		int idTex;
		int red;
		int green;
		int blue;

		const std::string& path = std::string(child->first_attribute("path")->value());
		idTex = std::atoi(child->first_attribute("ID")->value());

		red = std::atoi(child->first_attribute("red")->value());
		green = std::atoi(child->first_attribute("green")->value());
		blue = std::atoi(child->first_attribute("blue")->value());


		std::wstring cover = std::wstring(path.begin(), path.end());
		textures->Add(idTex, cover.c_str(), D3DCOLOR_XRGB(red, green, blue));

	}


	xml_node<>* spriteNode = rootNode->first_node("sprites");
	//load sprite
	for (xml_node<>* child = spriteNode->first_node(); child; child = child->next_sibling()) //cú pháp lập
	{
		// duyệtt	
		//mình load từ file lên mà man. 
		// load path và idtex lên truyền vào loadsprite
		int idTex;
		// nhớ ép kiểu
		const std::string& path = std::string(child->first_attribute("path")->value());
		idTex = std::atoi(child->first_attribute("idTex")->value());

		LoadSprite(path, idTex);

	}

	xml_node<>* aniNode = rootNode->first_node("animations");
	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{
		const std::string& path = std::string(child->first_attribute("path")->value());
		LoadAnimation(path);

	}


	//file here
	gameMap = new Map(TexID, id);

	gameMap->BuildMap(FilePath);

	grid = new Grid(gameMap->getWidth(), gameMap->getHeight());
	hub = new Hub(this);

	const std::string GridPath = "GameContent\\Data\\Grid\\grid.xml";

	grid->LoadGrid(GridPath,this);

	CGame::GetInstance()->SetCamPos(0, 0);
}

// dọn rác
void PlayScene::UnLoad()
{
	if (SIMON != NULL)
	{
		SimonProperties* prop = new SimonProperties();
		prop->SetProperties(SIMON->GetWhip()->GetState(), SIMON->getCurrentSubweapon(), SIMON->GetHeart(), SIMON->GetHp(), SIMON->GetScore(),SIMON->GetShootState());
		CGame::GetInstance()->SetSimonProp(prop);
	}
	if (grid != NULL)
	{
		grid->CleanObject();
	}
	for (int i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->IsDestroy())
		{
			delete objects[i];
		}
	}
	objects.clear();

}

void PlayScene::GameTimeCounter()
{
	if (this->timeCounter_start == 0)
	{
		timeCounter_start = GetTickCount();
	}
	else if (GetTickCount() - this->timeCounter_start >= 1000)
	{
		if (this->stateTime > 0)
		{
			this->stateTime--;
		}

		this->timeCounter_start = 0;
	}
}

void PlayScene::Update(DWORD dt)
{
	GameTimeCounter();
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	/// Thêm các object trong hàng đợi vào ds object

	GetListobjectFromGrid();

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	/// truyền playscene vào hàm update của các object
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, this, &coObjects);
	}

	if (SIMON == NULL)
	{
		return;
	}
	// Update camera to follow SIMON
	float cx, cy;
	float startpoint;
	SIMON->GetPosition(cx, cy);
	startpoint = SIMON->getStartPoint();
	startpoint -= SCREEN_WIDTH / 2;
	cx = cx - SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH;
	cy -= SCREEN_HEIGHT / 2;
	if (startpoint > this->cameraBoder.right - SCREENSIZE::WIDTH)
	{
		float test = cx - ((cx + SCREENSIZE::WIDTH) - this->cameraBoder.right);
		CGame::GetInstance()->SetCamPos(test, this->cameraBoder.top);
		SIMON->setStartPoint(0);
	}
	else if (cx > this->cameraBoder.left && cx < this->cameraBoder.right - SCREENSIZE::WIDTH)
	{
		CGame::GetInstance()->SetCamPos(cx, this->cameraBoder.top /*cy*/);
	}

	for (vector<LPGAMEOBJECT>::iterator it = objects.begin(); it != objects.end(); ) {

		if ((*it)->IsDestroy()) {
			it = objects.erase(it);
		}
		else ++it;
	}

	if (this->SIMON->GetSwitchScene() >= 0)
	{
		CGame::GetInstance()->SwitchScene(SIMON->GetSwitchScene());
	}

	if (this->SIMON->GetIsFightWithBoss() == true)
	{
		CGame::GetInstance()->SetCamPos(this->BossCamera.left, this->BossCamera.top);
	}
	hub->Update();
	UpdateGrid();
}


void PlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR2 cam = game->GetCamera();
	gameMap->Render(cam);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	SIMON->Render();
	hub->Render();
}
void PlayScene::OnKeyDown(int KeyCode)
{
	ItemCollection* itemcollection = new ItemCollection();
	Item* item = new Item();

	DebugOut(L"[INFO] PRESS KEY DOWN: %d\n", KeyCode);
	if (SIMON->GetState() == SIMON_STATE_UPWHIP) return;
	if (SIMON->GetState() == SIMON_STATE_ENTERCASTLE) return;
	switch (KeyCode)
	{
	case DIK_SPACE:
		// ta cần kiểm tra
		if (SIMON->GetState() != SIMON_STATE_JUMP && SIMON->GetState() != SIMON_STATE_SIT && !SIMON->GetFightTime() && !SIMON->CheckIsOnStair())
		{ // ngooif thi k cho nhay
			SIMON->SetState(SIMON_STATE_JUMP);
		}
		break;

	case DIK_Z:
		if (!SIMON->GetFightTime())
		{

			if (CGame::GetInstance()->IsKeyDown(DIK_UP) && SIMON->getCurrentSubweapon() != 0 && !SIMON->IsSpawnSubWeapon() && !SIMON->CheckIsOnStair())
			{
				if (CGame::GetInstance()->IsKeyDown(DIK_DOWN))
				{
					SIMON->SetState(SIMON_STATE_IDLE);
				}
				SIMON->SpawnSubWeapon(true);
				SIMON->SetIsSpawnWhip(false);
				SIMON->SetTimeSpawnSub(GetTickCount());
			}
			else
			{
				SIMON->SpawnSubWeapon(false);
			}

			if (!CGame::GetInstance()->IsKeyDown(DIK_UP) || SIMON->GetCurrentShoot() < 1 || SIMON->GetHeart() <=0 )
			{
				SIMON->ResetSpawnWhip();
			}
			if (CGame::GetInstance()->IsKeyDown(DIK_UP) && SIMON->GetCurrentShoot() >= 1 && SIMON->GetHeart() > 0)
			{
				SIMON->ResetSpawnSubWeapon();
			}

			if (SIMON->GetState() == SIMON_STATE_SIT)
			{
				SIMON->SetState(SIMON_STATE_FIGHT_SIT);
			}
			else if (SIMON->GetState() == SIMON_STATE_DOWNSTAIR_IDLE)
			{
				SIMON->SetState(SIMON_STATE_DOWNSTAIR_ATTACK);
			}
			else if (SIMON->GetState() == SIMON_STATE_UPSTAIR_IDLE)
			{
				SIMON->SetState(SIMON_STATE_UPSTAIR_ATTACK);
			}
			else
			{
				if (!SIMON->CheckIsOnStair())
					SIMON->SetState(SIMON_STATE_FIGHT_STAND);
			}

		}
		break;
	case DIK_1:
		CGame::GetInstance()->SwitchScene(0);
		break;
	case DIK_2:
		CGame::GetInstance()->SwitchScene(1);
		break;
	case DIK_3:
		CGame::GetInstance()->SwitchScene(2);
		break;
	case DIK_4:
		CGame::GetInstance()->SwitchScene(3);
		break;
	case DIK_5:
		CGame::GetInstance()->SwitchScene(4);
		break;
	case DIK_6:
		CGame::GetInstance()->SwitchScene(5);
		break;
	case DIK_7:
		break;
	case DIK_8:
		CGame::GetInstance()->SwitchScene(7);
		break;
	case DIK_Q:
		SIMON->y -= 200;
		break;
	case DIK_U:
		item = itemcollection->SpawnItem(AXE, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_I:
		item = itemcollection->SpawnItem(DAGGER, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_O:
		item = itemcollection->SpawnItem(HOLYWATER, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_P:
		item = itemcollection->SpawnItem(BOOMERANG, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_Y:
		item = itemcollection->SpawnItem(STOPWATCH, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_K:
		item = itemcollection->SpawnItem(DOUBLESHOT, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_L:
		item = itemcollection->SpawnItem(TRIPLESHOT, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_J:
		this->SIMON->UpHeart();
		break;
	case DIK_M:
		item = itemcollection->SpawnItem(FOOD, this->GetSimon()->x + 100);
		item->SetPosition(this->GetSimon()->x + 100, this->GetSimon()->y - 100);
		this->SpawnObject(item);
		break;
	case DIK_N:
		this->SIMON->SetHp(1);
		break;
	case DIK_V:
		this->SIMON->GetWhip()->SetState(2);
		break;
	case DIK_B:
		this->SIMON->GetWhip()->SetState(0);
		break;
	}

}

void PlayScene::OnKeyUp(int KeyCode)
{
}

void PlayScene::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	if (SIMON->GetUpgrageTime() != 0 && GetTickCount() - SIMON->GetUpgrageTime() > Time_UpWhip)
	{
		SIMON->ResetUpgrageTime();
		SIMON->SetState(SIMON_STATE_IDLE);


	}
	if (SIMON->GetState() == SIMON_STATE_ENTERCASTLE) return;
	if (SIMON->GetState() == SIMON_STATE_UPWHIP) return;
	if (SIMON->GetState() == SIMON_STATE_JUMP) return;

	if (SIMON->GetFightTime() > 0 && GetTickCount() - SIMON->GetFightTime() > 350 && !SIMON->GetTimeSpawnSub())
	{
		switch (SIMON->GetState())
		{
		case SIMON_STATE_FIGHT_SIT:
			SIMON->SetState(SIMON_STATE_SIT);
			break;
		case  SIMON_STATE_FIGHT_STAND:
			SIMON->SetState(SIMON_STATE_IDLE);
			break;

		}
		SIMON->ResetFightAnimation();
		SIMON->ResetFightTime();
	}

	if (SIMON->GetTimeSpawnSub() && GetTickCount() - SIMON->GetTimeSpawnSub() > 350)
	{
		switch (SIMON->GetState())
		{
		case SIMON_STATE_FIGHT_SIT:
			SIMON->SetState(SIMON_STATE_SIT);
			break;
		case  SIMON_STATE_FIGHT_STAND:
			SIMON->SetState(SIMON_STATE_IDLE);

			break;

		}
		SIMON->ResetFightAnimation();
		SIMON->ResetTimeSpawnSub();
		SIMON->ResetFightTime();
	}

	if (SIMON->GetState() == SIMON_STATE_FIGHT_SIT) return;
	if (SIMON->GetState() == SIMON_STATE_FIGHT_STAND) return;
	// nhay thi khong cho bam gi luon

	if (game->IsKeyDown(DIK_UP))
	{

		if (SIMON->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {


			if (SIMON->CheckStepOnStairDirection() == STAIR_TOP_LEFT)
				SIMON->SetStepOnStairDirection(STAIR_BOTTOM_RIGHT);
			else if (SIMON->CheckStepOnStairDirection() == STAIR_TOP_RIGHT)
				SIMON->SetStepOnStairDirection(STAIR_BOTTOM_LEFT);
			SIMON->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}

		else if (SIMON->CheckCanStepUp()) {
			if (!SIMON->CheckIsOnStair() && SIMON->CheckCollideWithStair()) {
				SIMON->SetStartStepOnStair();
			}
			else if (SIMON->GetState() == SIMON_STATE_UPSTAIR_IDLE) {

				SIMON->SetStartStepOnStair();
			}
			return;
		}

	}
	else if (game->IsKeyDown(DIK_DOWN))
	{

		if (SIMON->GetState() == SIMON_STATE_UPSTAIR_IDLE) {
			if (SIMON->CheckStepOnStairDirection() == STAIR_BOTTOM_RIGHT)
				SIMON->SetStepOnStairDirection(STAIR_TOP_LEFT);
			else if (SIMON->CheckStepOnStairDirection() == STAIR_BOTTOM_LEFT) {
				SIMON->SetStepOnStairDirection(STAIR_TOP_RIGHT);
			}
			SIMON->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}
		if (SIMON->CheckCanStepDown()) {
			if (!SIMON->CheckIsOnStair() && SIMON->CheckCollideWithStair()) {
				SIMON->SetStartStepOnStair();
			}
			else if (SIMON->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {
				SIMON->SetStartStepOnStair();
			}
			return;
		}

	}
	if (SIMON->CheckIsOnStair() || SIMON->CheckStairOnStair()) {
		return;
	}

	if (SIMON->GetState() != SIMON_STATE_HURT)
	{
		if (game->IsKeyDown(DIK_RIGHT)) // bắt phím mũi tên phải
		{
			SIMON->SetState(SIMON_STATE_WALKING_RIGHT); //đi phải

		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			SIMON->SetState(SIMON_STATE_WALKING_LEFT);
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			SIMON->SetState(SIMON_STATE_SIT);
		}
		else
		{
			if (SIMON->GetState() != SIMON_STATE_HURT)
			{
				SIMON->SetState(SIMON_STATE_IDLE);
			}

		}
	}


}

void PlayScene::LoadDefault()
{

	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	const std::string filePath = "GameContent\\Data\\Data\\common.xml";

	char* fileLoc = new char[filePath.size() + 1];
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 


	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());


	xml_node<>* rootNode = doc.first_node("Base");

	xml_node<>* texNode = rootNode->first_node("textures");

	for (xml_node<>* child = texNode->first_node(); child; child = child->next_sibling())
	{
		int idTex;
		int red;
		int green;
		int blue;

		const std::string& path = std::string(child->first_attribute("path")->value());
		idTex = std::atoi(child->first_attribute("ID")->value());

		red = std::atoi(child->first_attribute("red")->value());
		green = std::atoi(child->first_attribute("green")->value());
		blue = std::atoi(child->first_attribute("blue")->value());


		std::wstring cover = std::wstring(path.begin(), path.end());
		textures->Add(idTex, cover.c_str(), D3DCOLOR_XRGB(red, green, blue));
	}


	xml_node<>* spriteNode = rootNode->first_node("sprites");
	//load sprite
	for (xml_node<>* child = spriteNode->first_node(); child; child = child->next_sibling()) //cú pháp lập
	{
		// duyệtt	
		//mình load từ file lên mà man. 
		// load path và idtex lên truyền vào loadsprite
		int idTex;
		// nhớ ép kiểu
		const std::string& path = std::string(child->first_attribute("path")->value());
		idTex = std::atoi(child->first_attribute("idTex")->value());

		LoadSpriteDefault(path, idTex);

	}

	xml_node<>* aniNode = rootNode->first_node("animations");
	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{
		const std::string& path = std::string(child->first_attribute("path")->value());
		LoadAnimationDefault(path);

	}

}

void PlayScene::LoadSpriteDefault(const std::string& filePath, const int tex)
{
	// ở đây mình truyền vào man
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();


	LPDIRECT3DTEXTURE9 objecttex = textures->Get(tex);
	// đọc vào file xml
	char* fileLoc = new char[filePath.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc
#



	   //TODO: make multi format version of string copy
	// phần này k quan tâm lắm dạng như cú pháp thôi
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());


	xml_node<>* rootNode = doc.first_node("resource");
	xml_node<>* spriteSheetNode = rootNode->first_node("spritesheet");

	// lập toàn bộ các node con của node gamedata

	for (xml_node<>* child = spriteSheetNode->first_node(); child; child = child->next_sibling())
	{

		const std::string& ID = std::string(child->first_attribute("ID")->value());

		xml_node<>* frameNode = child->first_node("frame");



		int x = std::atoi(frameNode->first_attribute("x")->value());
		int y = std::atoi(frameNode->first_attribute("y")->value());
		int w = std::atoi(frameNode->first_attribute("width")->value());
		int h = std::atoi(frameNode->first_attribute("height")->value());

		int r = x + w;
		int b = y + h;

		sprites->Add(ID, x, y, r, b, objecttex);
		sprites->Get(ID)->SetIsDefault(true);
	}




}
void PlayScene::LoadAnimationDefault(const string& filePath)
{
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	char* fileLoc = new char[filePath.size() + 1];
#

#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 


	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* rootNode = doc.first_node("resource");
	xml_node<>* aniNode = rootNode->first_node("animations");


	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{

		const std::string& ID = std::string(child->first_attribute("ID")->value());
		int timeLoop = std::atoi(child->first_attribute("defaulttime")->value());
		ani = new CAnimation(timeLoop);
		for (xml_node<>* grand = child->first_node(); grand; grand = grand->next_sibling())
		{
			const std::string& spriteID = std::string(grand->first_attribute("spriteID")->value());
			ani->Add(spriteID);
		}
		ani->SetIsDefault(true);
		animations->Add(ID, ani);
	}

}


void PlayScene::GetListobjectFromGrid()
{
	objects.clear();
	while (qObjects.size() > 0)
	{
		objects.push_back(qObjects.front());
		qObjects.pop();
	}

	grid->GetListobject(objects);
}

void PlayScene::UpdateGrid()
{
	for (size_t i = 0; i < this->objects.size(); i++)
	{
		LPGAMEOBJECT obj = this->objects.at(i);
		float x_, y_;
		obj->GetPosition(x_, y_);
		grid->Update(obj);
	}
}