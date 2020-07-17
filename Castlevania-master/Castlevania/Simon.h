#pragma once
#include "GameObject.h"
#include"Whip.h"
#include "HiddenObject.h"
#include"Stair.h"
#include"SimonProperties.h"

#define SIMON_WALKING_SPEED		0.1f 
#define SIMON_AUTOWALKING_SPEED	0.05f 
#define SIMON_UPSTAIR_VELOCITY 0.04f
//0.1f
#define SIMON_JUMP_SPEED_Y		0.55f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_FALLDOWN_VY 0.8f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_HURT_SPEED_Y 0.35f
#define SIMON_HURT_SPEED_X 0.2f

#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING_RIGHT 1
#define SIMON_STATE_WALKING_LEFT 2
#define SIMON_STATE_SIT 3
#define SIMON_STATE_JUMP 4
#define SIMON_STATE_FIGHT_STAND 5
#define SIMON_STATE_FIGHT_SIT 6
#define SIMON_STATE_DIE 7
#define SIMON_STATE_UPWHIP 8
#define SIMON_STATE_ENTERCASTLE 9
#define SIMON_STATE_FALLDOWN 10

//len xuong cau thang
#define SIMON_STATE_UPSTAIR_IDLE 10
#define SIMON_STATE_UPSTAIR_RIGHT 11
#define SIMON_STATE_UPSTAIR_LEFT 12
#define SIMON_STATE_DOWNSTAIR_IDLE 13
#define SIMON_STATE_DOWNSTAIR_RIGHT 14
#define SIMON_STATE_DOWNSTAIR_LEFT 15
#define SIMON_STATE_UPSTAIR_ATTACK 16
#define SIMON_STATE_DOWNSTAIR_ATTACK 17
#define SIMON_STATE_HURT 18



#define SIMON_ANI_IDLE 0 
#define SIMON_ANI_WALKING 1  
#define SIMON_ANI_SIT 2 
#define SIMON_ANI_STAND_ATTACK				3
#define SIMON_ANI_SIT_ATTACK				4
#define SIMON_ANI_UPWHIP 5 
#define SIMON_ANI_DIE				6
#define SIMON_ANI_HURT 13


//len xuong cau thang
#define SIMON_ANI_IDLE_UPSTAIR          7
#define SIMON_ANI_STEP_UPSTAIR            8
#define SIMON_ANI_IDLE_DOWNSTAIR         9
#define SIMON_ANI_STEP_DOWNSTAIR            10
#define SIMON_ANI_UPSTAIR_ATTACK           11
#define SIMON_ANI_DOWNSTAIR_ATTACK         12


#define SIMON_ONSTAIR_DISTANCE_X 16 // quãng đường theo trục x mỗi lần lên xuống 1 bậc cầu thang
#define SIMON_ONSTAIR_DISTANCE_Y 16 // quãng đường theo trục y mỗi lần lên xuống 1 bậc cầu thang


// Hiệu số vị trí của stair trigger và vị trí simon khi bắt đầu bước lên
#define SIMON_UPSTAIR_RIGHT_OFFSET  12
#define SIMON_UPSTAIR_LEFT_OFFSET 12 // da giam 3px
#define SIMON_DOWNSTAIR_LEFT_OFFSET 10
#define SIMON_DOWNSTAIR_RIGHT_OFFET 18

#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BBOX_WIDTH  48
#define SIMON_BBOX_HEIGHT 63

#define SIMON_SMALL_BBOX_WIDTH  13
#define SIMON_SMALL_BBOX_HEIGHT 15

#define SIMON_UNTOUCHABLE_TIME 5000
#define SIMON_INVISIVLE_TIME 8000

#define Time_UpWhip 500

#define SIMON_HP 16

#define BIG_HEART 5
#define SMALL_HEART 1

#define DOUBLE_SHOT_STATE 2
#define TRIPLE_SHOT_STATE 3

class CSIMON : public CGameObject
{
	bool isInBridge;
	float startpoint;
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD fight_start;
	int state;
	Whip* whip;
	bool isSitting;
	DWORD upgrade_start;
	int currenSubWeapon;
	bool spawnSubweapon=false;
	bool isSpawnSubweapon = false;
	bool isSpawnWhip = true;

	//cau thang
	int lastState = -1;
	bool isAutoWalk = false;
	bool isOnStair =false;
	int StairDirection =-1; 
	bool startOnStair =false;
	bool isColliceWithStair =false;
	bool isFirstStepOnStair =false;
	D3DXVECTOR2 stairPos;
	D3DXVECTOR2 LastStepOnStairPos;
	void HandleFirstStepOnStair();
	void HandlePerStepOnStair();

	int Switch_scene;

	//properties
	int heart;
	int hp;
	int score;

	int ShootState;
	int CurrentShoot;

	bool isFightWithBoss;

	DWORD time_spawn_sub;  //thoi gian phong vu khi phu

	bool invisible;
	bool isInSpecialStair;
public: 
	CSIMON() : CGameObject()
	{
		Switch_scene = -1;
		currenSubWeapon = 0;
		isInBridge = false;
		isSitting = false;
		level = SIMON_LEVEL_BIG;
		untouchable = 0;
		this->upgrade_start = 0;
		this->fight_start = 0;
		state = SIMON_STATE_IDLE; // trạng thái ban đầu cần khai báo khi tạo object
		whip = new Whip();
		heart = 0;
		score = 0;
		hp = 16;
		ShootState = 1;
		CurrentShoot = 1;
		time_spawn_sub = 0;
		isFightWithBoss = false;
		this->AddAnimation("SIMON_ANI_IDLE");		
		this->AddAnimation("SIMON_ANI_WALKING");	
		this->AddAnimation("SIMON_ANI_SIT");
		this->AddAnimation("SIMON_ANI_STAND_ATTACK");
		this->AddAnimation("SIMON_ANI_SIT_ATTACK");
		this->AddAnimation("SIMON_ANI_IDLE_UPWHIP");
		this->AddAnimation("SIMON_ANI_DIE");
		this->AddAnimation("SIMON_ANI_IDLE_UPSTAIR");    //7
		this->AddAnimation("SIMON_ANI_STEP_UPSTAIR");    //8
		this->AddAnimation("SIMON_ANI_IDLE_DOWNSTAIR");    //9
		this->AddAnimation("SIMON_ANI_STEP_DOWNSTAIR");    //10
		this->AddAnimation("SIMON_ANI_UPSTAIR_ATTACK");    //11
		this->AddAnimation("SIMON_ANI_DOWNSTAIR_ATTACK"); //12
		this->AddAnimation("SIMON_ANI_HURT");
		this->invisible = false;
		this->isInSpecialStair = false;
	}
	~CSIMON() { delete whip; }
	void ResetFightAnimation()
	{
		this->animations[SIMON_ANI_STAND_ATTACK]->ResetFrame();
		this->animations[SIMON_ANI_SIT_ATTACK]->ResetFrame();
		this->fight_start = 0;
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	Whip* GetWhip() { return whip; };
	void SetState(int state);
	void SetDirection(int nx) { this->nx = nx; }
	DWORD GetFightTime()
	{
		return this->fight_start;	
	}

	DWORD GetTimeSpawnSub()
	{
		return this->time_spawn_sub;
	}

	void ResetFightTime()
	{
		this->fight_start = 0;
	}

	void ResetTimeSpawnSub()
	{
		this->time_spawn_sub = 0;
	}

	int GetCurrentShoot()
	{
		return this->CurrentShoot;
	}

	int GetSwitchScene()
	{
		return this->Switch_scene;
	}

	void SetSwitchScene(int id)
	{
		this->Switch_scene = id;
	}

	DWORD GetUpgrageTime() { return this->upgrade_start; }
	void ResetUpgrageTime() { this->upgrade_start = 0; }

	int GetState() {
		return this->state;
	}
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void ResetSpawnSubWeapon() { this->isSpawnSubweapon = false; }

	void ResetSpawnWhip() { this->isSpawnWhip = true; }

	void SetIsSpawnWhip(bool flag)
	{
		this->isSpawnWhip = flag;
	}

	bool IsSpawnSubWeapon() {
		return spawnSubweapon;
	};
	void SpawnSubWeapon(bool flag) { 
		this->spawnSubweapon = flag;
	};

	int getCurrentSubweapon() { return this->currenSubWeapon; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void setStartPoint(float x) { this->startpoint = x; }
	float getStartPoint() { return this->startpoint; }

	//CAU THANG
	void StartOnStair(bool flag) {
		this->startOnStair = flag;
	}
	bool CheckStairOnStair() {
		return this->startOnStair;
	}
	void SetAutoWalk(bool flag) {
		this->isAutoWalk = flag;
	}
	bool CheckCanStepUp() {
		if (this->StairDirection == STAIR_BOTTOM_LEFT || this->StairDirection == STAIR_BOTTOM_RIGHT)
			return true;
		return false;
	}
	bool CheckCanStepDown() {
		if (this->StairDirection == STAIR_TOP_RIGHT || this->StairDirection == STAIR_TOP_LEFT)
			return true;
		return false;
	}
	bool CheckIsOnStair() {
		return this->isOnStair;
	}
	bool CheckCollideWithStair() {
		return this->isColliceWithStair;
	}
	void SetStartStepOnStair() {
		this->startOnStair = true;
	}
	bool CheckAutoWalk() {
		return this->isAutoWalk;
	}
	void SetLastState(int state) {
		this->lastState = state;
	}
	int CheckStepOnStairDirection() {
		return this->StairDirection;
	}
	void SetStepOnStairDirection(int dir) {
		this->StairDirection = dir;
	}

	int GetScore()
	{
		return this->score;
	}
	void SetScore(int x)
	{
		this->score = x;
	}

	void AddScore(int x)
	{
		this->score += x;
	}

	bool GetIsOnStair()
	{
		return this->isOnStair;
	}

	void SetIsOnStair(bool flag)
	{
		this->isOnStair = flag;
	}

	int GetHeart()
	{
		return this->heart;
	}

	int GetHp()
	{
		return this->hp;
	}

	void SetHp(int x)
	{
		this->hp = x;
	}

	void SetlastState(SimonProperties* prop);

	int GetShootState()
	{
		return this->ShootState;
	}

	void SetShootState(int state)
	{
		this->ShootState = state;
		this->CurrentShoot = state;
	}

	bool GetIsFightWithBoss()
	{
		return this->isFightWithBoss;
	}

	void SetIsFightWithBoss(int flag)
	{
		this->isFightWithBoss = flag;
	}

	void UpCurrentShoot()
	{
		this->CurrentShoot++;
	}

	void UpHeart()
	{
		this->heart += 10;
	}

	bool EqualShot()
	{
		if (this->CurrentShoot >= ShootState)
		{
			return false;
		}
		else return true;
	}

	void SetTimeSpawnSub(DWORD flag)
	{
		this->time_spawn_sub = flag;
	}
};