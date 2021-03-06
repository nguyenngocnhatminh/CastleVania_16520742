#include "Hub.h"
#include "define.h"
#include"SubWeaponCollection.h"

int Hub::BossHP = 0;

void Hub::Update()
{
	this->playerHeart = scene->GetSimon()->GetHeart();
	string heart_ = playerHeart < 10 ? "0" + std::to_string(playerHeart) : std::to_string(playerHeart);
	this->playerHP = scene->GetSimon()->GetHp();

	unsigned int score_ = scene->GetSimon()->GetScore();
	string score;
	if (score_ < 10)
	{
		score = "00000" + std::to_string(score_);
	}
	else if (score_ < 100)
	{
		score = "0000" + std::to_string(score_);
	}
	else if (score_ < 1000) {
		score = "000" + std::to_string(score_);
	}
	else if (score_ < 10000)
	{
		score = "00" + std::to_string(score_);
	}
	else if (score_ < 100000)
	{
		score = "0" + std::to_string(score_);
	}
	else {
		score = std::to_string(score_);
	}


	_UIinfo = "SCORE-" + score + " TIME 0" + std::to_string(scene->GetTime()) + " STAGE 0" + std::to_string(this->scene->GetStageID()) + "\n";
	_UIinfo = _UIinfo + "PLAYER                  -" + heart_ + "\n";
	_UIinfo += "ENEMY                   -02\n";
}

void Hub::Render()
{
	CSprites::GetInstance()->Get("BLACKBOARD_UI_SPRITE")->DrawUI(0, 290, 32, 255, false);
	string SubWeapon;
	switch (scene->GetSimon()->getCurrentSubweapon())
	{
	case AXE:
		SubWeapon = "AXE_UI_SPRITE";
		break;
	case DAGGER:
		SubWeapon = "KNIFE_UI_SPRITE";
		break;
	case HOLYWATER:
		SubWeapon = "HOLY_WATER_UI_SPRITE";
		break;
	case BOOMERANG:
		SubWeapon = "BOOMERANG_UI_SPRITE";
		break;
	case STOPWATCH:
		SubWeapon = "STOP_WATCH_UI_SPRITE";
		break;
	}
	if (SubWeapon != "")
	{
		CSprites::GetInstance()->Get(SubWeapon)->DrawUI(0, 300, 40, 255, false);
	}
	Game->DrawUIText(this->_UIinfo, bound,Game->GetCamera());
	for (size_t i = 0; i < this->playerHP; i++)
	{
		CSprites::GetInstance()->Get("PLAYER_HP_SPRITE")->DrawUI(0, 105 + i * 9, 32, 255, false);
	}
	for (size_t i = 0; i < BossHP; i++)
	{
		CSprites::GetInstance()->Get("BOSS_HP_SPRITE")->DrawUI(0, 105 + i * 9, 50, 255, false);
	}
	for (size_t i = this->playerHP; i < 16; i++)
	{
		CSprites::GetInstance()->Get("NOHP_UI_SPRITE")->DrawUI(0, 105 + i * 9, 32, 255, false);
	}
	for (size_t i = this->BossHP; i < 16; i++)
	{
		CSprites::GetInstance()->Get("NOHP_UI_SPRITE")->DrawUI(0, 105 + i * 9, 50, 255, false);
	}

	if (scene->GetSimon()->GetShootState() == DOUBLE_SHOT_STATE)
	{
		CSprites::GetInstance()->Get("DOUBLE_SHOOT_UI_SPRITE")->DrawUI(0, 440, 30, 255, false);
	}
	if (scene->GetSimon()->GetShootState() == TRIPLE_SHOT_STATE)
	{
		CSprites::GetInstance()->Get("TRIPLE_SHOOT_UI_SPRITE")->DrawUI(0, 440, 30, 255, false);
	}

}

Hub::Hub(PlayScene* scene)
{
	this->scene = scene;
	SetRect(&bound, 0, 15, SCREENSIZE::WIDTH, 80);
	this->BossHP = 16;
	Game = CGame::GetInstance();
	_UIinfo = "SCORE-000000 TIME 0000 STAGE 0" + std::to_string(this->state) + "\n";
	_UIinfo += "PLAYER                  -00\n";
	_UIinfo += "ENEMY                   -00\n";
}

Hub::~Hub()
{
}
