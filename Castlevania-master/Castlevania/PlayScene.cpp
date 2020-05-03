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
	
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	const std::string filePath = "GameContent\\Data\\Data\\Base.xml";

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
	// h mình load file base lên rồi load node sprites trong base
	//để lấy đường dẫn sprite của object rồi truyền vào hàm load sprite
	// mục đính là dùng vòng lập load tâtts cả các sprite của object luôn


	//load ani
	xml_node<>* aniNode = rootNode->first_node("animations");
	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{
		const std::string& path = std::string(child->first_attribute("path")->value());
		LoadAnimation(path);

	}


	//file here
	gameMap = new Map(TexID, id);

	gameMap->BuildMap(FilePath);




	SIMON = new CSIMON();

	objects.push_back(SIMON);
	
	auto objectLayer = gameMap->GetObjectLayer();
	for (auto const& x : objectLayer)
	{
		ObjectID objID = string2EntityType.at(x.first);
		switch (objID)
		{
		case OPlayer:
			for (auto const& y : x.second->GetObjectGroup())
			{
				SIMON->setStartPoint(y.second->GetX());
				SIMON->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
			}
			break;
		case OWall:
			break;
		case OGround:
			for (auto const& y : x.second->GetObjectGroup())
			{
				Ground* ground = new Ground();
				ground->SetPosition(y.second->GetX(), y.second->GetY());
				ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
				objects.push_back(ground);
			}
			break;
		case OMoneyBagTrigger:
			for (auto const& y : x.second->GetObjectGroup())
			{
				MoneyTrigger* trigger = new MoneyTrigger();
				trigger->SetPosition(y.second->GetX(), y.second->GetY());
				trigger->SetSize(y.second->GetWidth(), y.second->GetHeight());
				auto moneyBagLayer = objectLayer.at("MoneyBag");
				for (auto const& child : moneyBagLayer->GetObjectGroup())
				{
					ItemCollection* item = new ItemCollection();
					Item *mnBag = item->SpawnItem(y.second->GetProperty("item"));
					mnBag->SetIsHidden(true);
					mnBag->SetPosition(child.second->GetX(), child.second->GetY() - child.second->GetHeight());
					trigger->SetItem(mnBag);
				}
				objects.push_back(trigger);
			}
			break;
		case OTorch:
			for (auto const& y : x.second->GetObjectGroup())
			{
				Torch* torch = new Torch();
				torch->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				torch->SetItem(y.second->GetProperty("item"));
				objects.push_back(torch);
			}
			break;
		case ONextmap:
			break;
		case OPortal:
			for (auto const& y : x.second->GetObjectGroup())
			{
				Portal* portal = new Portal();
				portal->SetSize(y.second->GetWidth(), y.second->GetHeight());
				portal->SetPosition(y.second->GetX(), y.second->GetY());
				portal->setNextMapId(y.second->GetProperty("Map_ID"));
				objects.push_back(portal);
			}
			break;
		case OMoneyBag:
			break;
		case OCastle:
			break;
		case OCam:
			for (auto const& y : x.second->GetObjectGroup())
			{
				this->cameraBoder.left = y.second->GetX();
				this->cameraBoder.top = y.second->GetY();
				this->cameraBoder.right = y.second->GetX() + y.second->GetWidth();
				this->cameraBoder.bottom = y.second->GetY() + y.second->GetHeight();
			}
			break;
		case OSpawner:
			break;
		case OStair:
			for (auto const& y : x.second->GetObjectGroup())
			{
				Stair* stair = new Stair();
				stair->SetSize(y.second->GetWidth(), y.second->GetHeight());
				stair->SetPosition(y.second->GetX(), y.second->GetY());
				stair->SetDirection(y.second->GetProperty("direction"));
				objects.push_back(stair);
			}
			break;
		case OBirck:
			for (auto const& y : x.second->GetObjectGroup())
			{
				BreakWall* breakwall = new BreakWall();
				breakwall->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				breakwall->SetItem(y.second->GetProperty("item"));
				objects.push_back(breakwall);
			}
			break;
		case OCandle:
			for (auto const& y : x.second->GetObjectGroup())
			{
				Candle* candle = new Candle();
				candle->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				candle->SetItem(y.second->GetProperty("item"));
				objects.push_back(candle);
			}
			break;
		case OBridge:
			for (auto const& y : x.second->GetObjectGroup())
			{
				Bridge* bridge = new Bridge();
				bridge->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				objects.push_back(bridge);
			}
		case ODoor:
			break;
		case OBoss:
			break;
		case OBossBorder:
			break;
		case OBossTrigger:
			break;
		case OWater:
			break;
		default:
			break;
		}



	}
	CGame::GetInstance()->SetCamPos(0, 0);
	}

// dọn rác
void PlayScene::UnLoad()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();
	SIMON = NULL;

}

void PlayScene::Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	/// Thêm các object trong hàng đợi vào ds object

	while (!qObjects.empty()) // lập nếu queue còn phần tử
	{
		this->objects.push_back(qObjects.front());
		qObjects.pop();// thêm vào object rồi thì xóa object vừa thêm khỏi queue
	}

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	/// truyền playscene vào hàm update của các object
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, this, &coObjects);
	}

	if (SIMON==NULL)
	{
		return;
	}
	// Update camera to follow SIMON
	float cx, cy;
	float startpoint;
	SIMON->GetPosition(cx, cy);
	startpoint = SIMON->getStartPoint();
	startpoint -= SCREEN_WIDTH / 2;
	cx = cx- SCREEN_WIDTH / 2-SIMON_BBOX_WIDTH;
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

}

void PlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR2 cam = game->GetCamera();
	gameMap->Render(cam);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	SIMON->Render();
	if (SIMON->GetState() == SIMON_STATE_ENTERCASTLE)
	{
		gameMap->GetLayer("Mid")->Render(cam);
	}


}
void PlayScene::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] PRESS KEY DOWN: %d\n", KeyCode);
	if (SIMON->GetState() == SIMON_STATE_UPWHIP) return;
	if (SIMON->GetState() == SIMON_STATE_ENTERCASTLE) return;
	switch (KeyCode)
	{
	case DIK_SPACE:
		// ta cần kiểm tra
		if (SIMON->GetState() != SIMON_STATE_JUMP && SIMON->GetState() != SIMON_STATE_SIT && !SIMON->GetFightTime()&&!SIMON->CheckIsOnStair())
		{ // ngooif thi k cho nhay
			SIMON->SetState(SIMON_STATE_JUMP);
		}			
		break;

	case DIK_Z:
		if (!SIMON->GetFightTime())
		{
			SIMON->ResetSpawnSubWeapon();
			if (CGame::GetInstance()->IsKeyDown(DIK_UP) && SIMON->getCurrentSubweapon()!=0&& !SIMON->IsSpawnSubWeapon()&&!SIMON->CheckIsOnStair())
			{
				if (CGame::GetInstance()->IsKeyDown(DIK_DOWN))
					SIMON->SetState(SIMON_STATE_IDLE);
				SIMON->SpawnSubWeapon(true);
			}
			else
			{
				SIMON->SpawnSubWeapon(false);
			}

			if (SIMON->GetState() == SIMON_STATE_SIT)
			{
				SIMON->SetState(SIMON_STATE_FIGHT_SIT);
			}
			else if (SIMON->GetState()==SIMON_STATE_DOWNSTAIR_IDLE)
			{
				SIMON->SetState(SIMON_STATE_DOWNSTAIR_ATTACK);
			}
			else if (SIMON->GetState() == SIMON_STATE_UPSTAIR_IDLE)
			{
				SIMON->SetState(SIMON_STATE_UPSTAIR_ATTACK);
			}
			else
			{
				if(!SIMON->CheckIsOnStair())
					SIMON->SetState(SIMON_STATE_FIGHT_STAND);
			}

		}
		break;
	case DIK_A: // reset
		SIMON->SetState(SIMON_STATE_IDLE);
		SIMON->SetLevel(SIMON_LEVEL_BIG);
		SIMON->SetPosition(50.0f, 0.0f);
		SIMON->SetSpeed(0, 0);
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
	case DIK_Q:
		SIMON->y -= 200;
		break;
	case DIK_E:
		SIMON->y += 50;
		break;

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

	if (SIMON->GetFightTime() && GetTickCount() - SIMON->GetFightTime() > 350)
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
		SIMON->SetState(SIMON_STATE_IDLE);
	}

}
