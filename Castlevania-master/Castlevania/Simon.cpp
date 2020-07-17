#include <algorithm>
#include "debug.h"
#include "MoneyTrigger.h"
#include "SIMON.h"
#include "Game.h"
#include "Ground.h"
#include "Torch.h"
#include "Item.h"
#include"ItemCollection.h"
#include"WhipItem.h"
#include"BigHeart.h"
#include"DaggerItem.h"
#include"SubWeaponCollection.h"
#include"SubWeapon.h"
#include"Portal.h"
#include"Stair.h"
#include"define.h"
#include"BreakWall.h"
#include"Boomerang.h"
#include"Bridge.h"
#include"HolyWaterItem.h"
#include"Enemy.h"
#include "Bat.h"
#include "SitTrigger.h"
#include "BossTrigger.h"
#include "DeathZone.h"

void CSIMON::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, scene);

	this->GetWhip()->SetDamage(this->ShootState);

	if (this->hp == 0)
		this->SetState(SIMON_STATE_DIE);

	if (this->GetState() == SIMON_STATE_DIE)
		return;
	if (this->fight_start!=0 && !this->isAutoWalk && this->isOnStair) {

		if (whip->CheckLastFrame()) {
			if (this->isOnStair)
			{
				if (this->StairDirection == STAIR_BOTTOM_RIGHT
					|| this->StairDirection == STAIR_BOTTOM_LEFT)
				{
					this->lastState = SIMON_STATE_UPSTAIR_ATTACK;
					SetState(SIMON_STATE_UPSTAIR_IDLE);
				}
				else if (this->StairDirection == STAIR_TOP_RIGHT
					|| this->StairDirection == STAIR_TOP_LEFT)
				{
					this->lastState = SIMON_STATE_DOWNSTAIR_ATTACK;
					SetState(SIMON_STATE_DOWNSTAIR_IDLE);
				}
			}
		}

	}
	if (this->startOnStair) {
		if (!this->isFirstStepOnStair)
			HandleFirstStepOnStair();
		else {
			if (this->StairDirection == STAIR_BOTTOM_RIGHT)
				SetState(SIMON_STATE_UPSTAIR_RIGHT);
			else if (this->StairDirection == STAIR_BOTTOM_LEFT)
			{
				SetState(SIMON_STATE_UPSTAIR_LEFT);
			}
			else if (this->StairDirection == STAIR_TOP_LEFT)
			{
				SetState(SIMON_STATE_DOWNSTAIR_LEFT);
			}
			else if (this->StairDirection == STAIR_TOP_RIGHT)
			{
				SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
			}
		}
	}
	this->HandlePerStepOnStair();

	// Simple fall down
	if (!this->startOnStair
		&& !this->isOnStair
		&& state != SIMON_STATE_UPSTAIR_IDLE
		&& state != SIMON_STATE_DOWNSTAIR_IDLE
		&& state != SIMON_STATE_UPSTAIR_ATTACK
		&& state != SIMON_STATE_DOWNSTAIR_ATTACK
		)
	{
		vy += SIMON_GRAVITY * dt;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (invisible == false)
	{
		if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
	}
	else
	{
		if (GetTickCount() - untouchable_start > SIMON_INVISIVLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
			invisible = false;
		}
	}

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x)
		{
			x=cam.x;
		}
	}



	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	
		// block 
		x += min_tx * dx + nx * 0.4f;		
		if (ny <= 0) 
			y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		
			if (dynamic_cast<Ground*>(e->obj)) {
				if (e->ny != 0)
				{ 
					if (GetState() == SIMON_STATE_JUMP || GetState()==SIMON_STATE_HURT) {
						SetState(SIMON_STATE_IDLE);
					}
					if (this->state == SIMON_STATE_FIGHT_STAND)
					{
						vx = 0;
					}
					if (this->isOnStair) {
						x += dx;
						y += dy;
					}
					if (ny != 0) vy = 0;
				}
				else if (e->nx != 0) {
					if (this->startOnStair || this->isOnStair)
					{
						x += dx;
						y += dy;
					}
					else {
						if (ny != 0) vy = 0;
					}
				}
			}
			else if (dynamic_cast<Portal*>(e->obj))
			{
				auto portal = dynamic_cast<Portal*>(e->obj);
				this->Switch_scene = portal->GetNextMapId();
			}
			else if (dynamic_cast<BreakWall*>(e->obj)) {
				if (e->ny != 0) { // kiểm tra va chạm trục y có va chạm trục y nhảy vào đây
					if (GetState() == SIMON_STATE_JUMP) {
						SetState(SIMON_STATE_IDLE);
					}
					if (this->state == SIMON_STATE_FIGHT_STAND)
					{
						vx = 0;
					}
					if (ny != 0) vy = 0;
					// cần xét kỹ phương va chạm
					if (nx != 0) vx = 0;


				}
				else if (e->ny > 0 && this->vy < 0) {
					y += dy;
					if (this->GetState() != SIMON_STATE_JUMP)
					{
						if (nx != 0) vx = 0;
					}
				}
				else if (e->nx != 0) {
					if (this->startOnStair || this->isOnStair)
					{
						x += dx;
						y += dy;
					}
					else {
						if (ny != 0) vy = 0;
					}
				}
				// cần xét kỹ phương va chạm
			}
			else if (dynamic_cast<Bridge*>(e->obj))
			{
				Bridge* bridge = dynamic_cast<Bridge*>(e->obj);
				if (e->ny != 0) { // kiểm tra va chạm trục y có va chạm trục y nhảy vào đây
					if (GetState() == SIMON_STATE_JUMP && vy >= 0) {
						SetState(SIMON_STATE_IDLE);
					}
					if (this->state == SIMON_STATE_FIGHT_STAND)
					{
						vx = 0;
					}
					if (ny != 0) vy = 0;
					this->x += bridge->dx * 2;

				}
			}
			else if (dynamic_cast<DeathZone*>(e->obj))
			{
				if (this->isOnStair == false && this->GetState()!= SIMON_STATE_DIE)
					this->SetState(SIMON_STATE_DIE);
			}
			else
			{
				if (dynamic_cast<Item*>(e->obj))
				{
					Item* item = dynamic_cast<Item*>(e->obj);
					if (!item->IsDestroy())
					{
						if (dynamic_cast<Heart*>(e->obj))
						{
							this->heart += SMALLHEART;
						}
						if (dynamic_cast<BigHeart*>(e->obj))
						{
							this->heart += BIG_HEART;
						}
						if (dynamic_cast<WhipItem*>(e->obj))
						{
							this->SetState(SIMON_STATE_UPWHIP);
						}
						if (dynamic_cast<DaggerItem*>(e->obj))
						{
							currenSubWeapon = DAGGER;
						}
						if (dynamic_cast<BoomerangItem*>(e->obj))
						{
							currenSubWeapon = BOOMERANG;
						}
						if (dynamic_cast<HolyWaterItem*>(e->obj))
						{
							currenSubWeapon = HOLYWATER;
						}
						if (dynamic_cast<AxeItem*>(e->obj))
						{
							currenSubWeapon = AXE;
						}
						if (dynamic_cast<DoubleShot*>(e->obj))
						{
							this->SetShootState(DOUBLE_SHOT_STATE);
							this->CurrentShoot = this->ShootState;
							this->ResetSpawnSubWeapon();
						}
						if (dynamic_cast<TripleShot*>(e->obj))
						{
							this->SetShootState(TRIPLE_SHOT_STATE);
							this->CurrentShoot = this->ShootState;
							this->ResetSpawnSubWeapon();

						}
						if (dynamic_cast<GoldPotion*>(e->obj))
						{
							invisible = true;
							StartUntouchable();
						}
						this->score += item->GetScore();
						item->Destroy();
					}

				}

				else if (dynamic_cast<MoneyTrigger*>(e->obj))
				{
					if (e->nx != 0) // va chạm chiều x
						x += dx;
					if (e->ny != 0)
						y += dy;
					auto trigger = dynamic_cast<MoneyTrigger*>(e->obj);
					trigger->SetDestroy();

					if (dynamic_cast<PlayScene*>(scene))
					{
						auto pScene = dynamic_cast<PlayScene*>(scene);
						pScene->SpawnObject(trigger->GetItem());
					}
				}
				else if (dynamic_cast<BossTrigger*>(e->obj))
				{
					auto trigger = dynamic_cast<BossTrigger*>(e->obj);
					trigger->Destroy();
					this->isFightWithBoss = true;
				}
				else if (dynamic_cast<SitTrigger*>(e->obj))
				{
					if (this->nx != 0)
						x += dx;
					if (e->ny != 0)
						y += dy;

					if (dynamic_cast<PlayScene*>(scene))
					{
						auto pScene = dynamic_cast<PlayScene*>(scene);
						if (this->GetState() == SIMON_STATE_SIT)
						{
							auto trigger = dynamic_cast<SitTrigger*>(e->obj);
							trigger->SetDestroy();
							pScene->SpawnObject(trigger->GetItem());
						}
					}
				}
				else if (dynamic_cast<Boomerang*>(e->obj))
				{
					Boomerang* bom= dynamic_cast<Boomerang*>(e->obj);
					bom->Destroy();
				}
				else if (dynamic_cast<Enemy*>(e->obj))
				{
					if (e->ny < 0)
						y += dy;
					Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
					if (dynamic_cast<Bat*>(e->obj))
					{
						Bat* bat = dynamic_cast<Bat*>(e->obj);
						bat->SubtractHP(1);
						if (bat->GetHP() == 0)
						{
							this->score += bat->GetScore();
							bat->SpawnItem();
							bat->Destroy();
						}
					}
					if (untouchable_start == 0)
					{
						if (untouchable != 1) {
							if (!this->isOnStair)
							{
								this->SetState(SIMON_STATE_HURT);
							}
							this->hp--;
							StartUntouchable();
						}
					}
				}
				else
				{
					if (e->nx != 0) // va chạm chiều x
						x += dx;
					if (e->ny != 0)
						y += dy;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	bool flagOnGround = false;
	for (std::size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<Ground*>(e) && !flagOnGround) // BUG khi đứng lên brick
		{
			Ground* f = dynamic_cast<Ground*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b + 15; // hehehe offset 5pixel
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				flagOnGround = true;
			}
		}

		if (dynamic_cast<BreakWall*>(e) && !flagOnGround) // BUG khi đứng lên brick
		{
			BreakWall* f = dynamic_cast<BreakWall*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b + 15; // hehehe offset 5pixel
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				flagOnGround = true;
			}
		}
		if (dynamic_cast<Item*>(e))
		{
			Item* f = dynamic_cast<Item*> (e);

			if (!f->GetIsHidden())
			{
				if (CGameObject::isColliding(f))
				{
					Item* item = dynamic_cast<Item*>(f);
					if (!item->IsDestroy())
					{
						if (dynamic_cast<Heart*>(f))
						{
							this->heart += SMALLHEART;
						}
						if (dynamic_cast<BigHeart*>(f))
						{
							this->heart += BIG_HEART;
						}
						if (dynamic_cast<WhipItem*>(f))
						{
							this->SetState(SIMON_STATE_UPWHIP);
						}
						if (dynamic_cast<DaggerItem*>(f))
						{
							currenSubWeapon = DAGGER;
						}
						if (dynamic_cast<BoomerangItem*>(f))
						{
							currenSubWeapon = BOOMERANG;
						}
						if (dynamic_cast<HolyWaterItem*>(f))
						{
							currenSubWeapon = HOLYWATER;
						}
						if (dynamic_cast<AxeItem*>(f))
						{
							currenSubWeapon = AXE;
						}
						if (dynamic_cast<DoubleShot*>(f))
						{
							this->SetShootState(DOUBLE_SHOT_STATE);
							this->CurrentShoot = this->ShootState;
							this->ResetSpawnSubWeapon();
						}
						if (dynamic_cast<TripleShot*>(f))
						{
							this->SetShootState(TRIPLE_SHOT_STATE);
							this->CurrentShoot = this->ShootState;
							this->ResetSpawnSubWeapon();
						}
						this->score += item->GetScore();
						item->Destroy();
					}
				}
			}
		}
		else if (dynamic_cast<Stair*>(e))
		{
			Stair* f = dynamic_cast<Stair*> (e);

			if (CGameObject::isColliding(f))
			{
				if (f->GetSpecial() == 1)
				{
					if (f->GetDirection() == STAIR_BOTTOM_RIGHT)
					{
						if (this->GetState() != SIMON_STATE_IDLE && this->GetState() != SIMON_STATE_UPSTAIR_LEFT)
						{
							return;
						}
					}
					if (f->GetDirection() == STAIR_BOTTOM_LEFT)
					{
						if (this->GetState() != SIMON_STATE_IDLE && this->GetState() != SIMON_STATE_UPSTAIR_RIGHT)
						{
							return;
						}
					
					}
					if (f->GetDirection() == STAIR_TOP_RIGHT)
					{
						if (this->GetState() != SIMON_STATE_IDLE && this->GetState() != SIMON_STATE_DOWNSTAIR_LEFT)
						{
							return;
						}

					}
					if (f->GetDirection() == STAIR_TOP_LEFT)
					{
						if (this->GetState() != SIMON_STATE_IDLE && this->GetState() != SIMON_STATE_DOWNSTAIR_RIGHT)
						{
							return;
						}
					}
				}
				if (!this->isColliceWithStair) {
					if (this->isOnStair) {
						SetState(SIMON_STATE_IDLE);
						this->isOnStair = false;
						this->startOnStair = false;
						this->isFirstStepOnStair = false;
						return;
					}
					this->isColliceWithStair = true;
					this->StairDirection = f->GetDirection();
					this->stairPos = { f->x,f->y };
					f->SetActive(true);
					return;
				}
			}
			else if (f->CheckActive())
			{
				f->SetActive(false);
				this->isColliceWithStair = false;
				if (!this->isOnStair)
					this->StairDirection = -1;
			}
		}
		else if (dynamic_cast<Enemy*>(e))
		{
			Enemy* f = dynamic_cast<Enemy*>(e);
			if (CGameObject::isColliding(f))
			{
				Enemy* enemy = dynamic_cast<Enemy*>(e);
				if (dynamic_cast<Bat*>(e))
				{
					Bat* bat = dynamic_cast<Bat*>(e);
					bat->SubtractHP(1);
					if (bat->GetHP() == 0)
					{
						bat->Destroy();
					}
				}
				if (untouchable_start == 0)
				{
					if (untouchable != 1) {
						if (!this->isOnStair)
						{
							this->SetState(SIMON_STATE_HURT);
						}
						this->hp--;
						StartUntouchable();
					}
				}
			}
		}
		else if (dynamic_cast<SitTrigger*>(e))
		{
			SitTrigger* trigger = dynamic_cast<SitTrigger*>(e);
			if (CGameObject::isColliding(trigger))
			{
				if (this->GetState() == SIMON_STATE_SIT)
				{
					if (dynamic_cast<PlayScene*>(scene))
					{
						auto pScene = dynamic_cast<PlayScene*>(scene);
						if (this->GetState() == SIMON_STATE_SIT)
						{
							auto trigger = dynamic_cast<SitTrigger*>(e);
							trigger->SetDestroy();
							pScene->SpawnObject(trigger->GetItem());
						}
					}
				}
			}
		}
	}
	if (!flagOnGround)
	{
		if (!isFirstStepOnStair && !isOnStair
			&& this->state != SIMON_STATE_JUMP
			&& this->state != SIMON_STATE_FIGHT_STAND
			&& this->state != SIMON_STATE_DIE
			&& this->state != SIMON_STATE_HURT
			&& this->state != SIMON_STATE_UPWHIP) {
			SetState(SIMON_STATE_IDLE);

		}

	}

	if (this->fight_start != 0)
	{
		if (!this->spawnSubweapon && fight_start > 0)
		{
			if (this->state == SIMON_STATE_FIGHT_SIT)
			{
				if (nx > 0)
				{
					whip->SetPosition(this->x - 1.65 * SIMON_BBOX_WIDTH, this->y + 0.25 * SIMON_BBOX_HEIGHT);
				}
				else
				{
					whip->SetPosition(this->x - 2 * SIMON_BBOX_WIDTH, this->y + 0.25 * SIMON_BBOX_HEIGHT);
				}
			}
			else
			{
				if (nx > 0)
				{
					whip->SetPosition(this->x - 1.65 * SIMON_BBOX_WIDTH, this->y);
				}
				else
					whip->SetPosition(this->x - 2*SIMON_BBOX_WIDTH, this->y);
			}

			whip->SetNxDirection(this->nx);
			whip->Update(dt, scene, coObjects);
		}
		else if (!isSpawnSubweapon && this->currenSubWeapon!=0)
		{
			if (time_spawn_sub != 0 )
			{
				SubWeaponCollection* sub = new SubWeaponCollection();
				SubWeapon* subWeapon = sub->SpawnSubWeapon(currenSubWeapon);
				if (this->heart - subWeapon->GetHeartCotst() >= 0)
				{
					if (nx > 0)
					{
						subWeapon->SetPosition(this->x + 0.15 * SIMON_BBOX_WIDTH, this->y + 0.1 * SIMON_BBOX_HEIGHT);
					}
					else
					{
						subWeapon->SetPosition(this->x + 0.3 * SIMON_BBOX_WIDTH, this->y + 0.1 * SIMON_BBOX_HEIGHT);
					}
					subWeapon->SetNx(this->nx);
					if (dynamic_cast<PlayScene*>(scene))
					{
						PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
						pScene->SpawnObject(subWeapon);
						this->fight_start = -1;
						this->CurrentShoot--;
					}
					if (this->CurrentShoot <= 1)
					{
						if (!subWeapon->isDestroy)
						{
							this->isSpawnSubweapon = true;
						}
					}
					this->heart -= subWeapon->GetHeartCotst();
				}
			}
		}
		else spawnSubweapon = false;
	}
}



void CSIMON::Render()
{
	int ani=0; // mặc định để chặn lỗi do chưa có ani của state walking left
	switch (state)
	{	
	case SIMON_STATE_IDLE:
		ani = SIMON_ANI_IDLE;
		break;
	case SIMON_STATE_ENTERCASTLE:
	case SIMON_STATE_WALKING_RIGHT:
		ani = SIMON_ANI_WALKING;
		break;			
	case SIMON_STATE_WALKING_LEFT:
		ani = SIMON_ANI_WALKING;
		break;
	case SIMON_STATE_SIT:
		ani = SIMON_ANI_SIT;
		break;
	case SIMON_STATE_JUMP:
		ani = SIMON_ANI_SIT;
		break;
	case SIMON_STATE_HURT:
		ani = SIMON_ANI_HURT;
		break;
	case SIMON_STATE_FIGHT_STAND:
		ani = SIMON_ANI_STAND_ATTACK;
		break;
	case SIMON_STATE_FIGHT_SIT:
		ani = SIMON_ANI_SIT_ATTACK;
		break;
	case SIMON_STATE_DIE:
		ani = SIMON_ANI_DIE;
		break;
	case SIMON_STATE_UPWHIP:
		ani = SIMON_ANI_UPWHIP;
		break;
	case SIMON_STATE_UPSTAIR_IDLE:
		ani = SIMON_ANI_IDLE_UPSTAIR;
		break;
	case SIMON_STATE_DOWNSTAIR_IDLE:
		ani = SIMON_ANI_IDLE_DOWNSTAIR;
		break;
	case SIMON_STATE_DOWNSTAIR_RIGHT:
		ani = SIMON_ANI_STEP_DOWNSTAIR;
		break;
	case SIMON_STATE_DOWNSTAIR_LEFT:
		ani = SIMON_ANI_STEP_DOWNSTAIR;
		break;
	case SIMON_STATE_UPSTAIR_RIGHT:
		ani = SIMON_ANI_STEP_UPSTAIR;
		break;
	case SIMON_STATE_UPSTAIR_LEFT:
		ani = SIMON_ANI_STEP_UPSTAIR;
		break;
	case SIMON_STATE_UPSTAIR_ATTACK:
		ani = SIMON_ANI_UPSTAIR_ATTACK;
		break;
	case SIMON_STATE_DOWNSTAIR_ATTACK:
		ani = SIMON_ANI_DOWNSTAIR_ATTACK;
		break;
	default:
		break;
	}
	
	if (this->fight_start > 0 && !this->spawnSubweapon && this->isSpawnWhip) 
	{
		whip->Render();
	}
	
	int alpha = 255;
	if (untouchable) alpha = 128;

	animations[ani]->Render(nx,x, y, alpha);

	RenderBoundingBox();
}

void CSIMON::HandleFirstStepOnStair()
{
	if (StairDirection == -1)
	{
		return;
	}
	this->vx = 0;
	this->vy = 0;

	if (StairDirection == STAIR_BOTTOM_RIGHT)
	{
		if (stairPos.x - this->x > SIMON_UPSTAIR_RIGHT_OFFSET)
		{
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else if (stairPos.x - this->x < SIMON_UPSTAIR_RIGHT_OFFSET - 5)
		{
			this->isAutoWalk = false;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else
		{
			if (state == SIMON_STATE_WALKING_LEFT)
			{
				if (nx == -1)nx = 1;
				else if (nx == 1) nx = -1;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos.x = this->x;
			this->LastStepOnStairPos.y = this->y;
			this->SetState(SIMON_STATE_UPSTAIR_RIGHT);
		}
	}
	else if (StairDirection == STAIR_BOTTOM_LEFT)
	{
		if (stairPos.x - this->x < SIMON_UPSTAIR_LEFT_OFFSET) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else if (stairPos.x - this->x > SIMON_UPSTAIR_LEFT_OFFSET + 5) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else {
			if (state == SIMON_STATE_WALKING_RIGHT) {
				if (nx == -1) nx = 1;
				else if (nx ==1) nx = -1;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos.x = this->x;
			this->LastStepOnStairPos.y = this->y;
			this->SetState(SIMON_STATE_UPSTAIR_RIGHT);
		}
	}
	else if (StairDirection == STAIR_TOP_LEFT)
	{
		if (stairPos.x - this->x < SIMON_DOWNSTAIR_LEFT_OFFSET) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else if (stairPos.x - this->x > SIMON_DOWNSTAIR_LEFT_OFFSET + 5) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else {
			if (state == SIMON_STATE_WALKING_RIGHT) {
				if (nx == -1) nx = 1;
				else if (nx == 1) nx = -1;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos.x = this->x;
			this->LastStepOnStairPos.y = this->y;
			this->SetState(SIMON_STATE_DOWNSTAIR_LEFT);
		}
	}
	else if (StairDirection == STAIR_TOP_RIGHT)
	{
		if (stairPos.x - this->x > SIMON_DOWNSTAIR_RIGHT_OFFET) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else if (stairPos.x - this->x < SIMON_DOWNSTAIR_RIGHT_OFFET - 5) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else {
			if (state == SIMON_STATE_WALKING_LEFT) {
				if (nx == -1) nx = 1;
				else if (nx == 1) nx = -1;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos.x = this->x;
			this->LastStepOnStairPos.y = this->y;
			this->SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
		}
	}
}

void CSIMON::HandlePerStepOnStair()
{
	if (this->state == SIMON_STATE_UPSTAIR_RIGHT) {
		DebugOut(L"Up right \n ");
		if (this->x - LastStepOnStairPos.x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y > SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y - SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x + SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_UPSTAIR_IDLE);
				this->isOnStair = true;
				DebugOut(L"Up right \n ");
			}

		}
	}
	else if (this->state == SIMON_STATE_UPSTAIR_LEFT) {
		if (this->x - LastStepOnStairPos.x < SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y > SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y - SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x - SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_UPSTAIR_IDLE);
				this->isOnStair = true;
				//	DebugOut(L" x=%f y=%f \n", this->x, this->y);
			}

		}
	}
	else if (this->state == SIMON_STATE_DOWNSTAIR_LEFT)
	{
		if (LastStepOnStairPos.x - this->x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y < SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y + SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x - SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_DOWNSTAIR_IDLE);
				this->isOnStair = true;
				DebugOut(L" DOWN left x=%f y=%f \n", this->x, this->y);
			}

		}
	}
	else if (this->state == SIMON_STATE_DOWNSTAIR_RIGHT)
	{
		if (this->x - LastStepOnStairPos.x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y < SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y + SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x + SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_DOWNSTAIR_IDLE);
				this->isOnStair = true;
				DebugOut(L" DOWN Right x=%f y=%f \n", this->x, this->y);
			}

		}
	}
}


void CSIMON::SetState(int state)
{
	isSitting = false;
	switch (state)
	{
	case SIMON_STATE_ENTERCASTLE:
		this->ResetFightAnimation();
		nx = 1;
		vx = SIMON_WALKING_SPEED / 2;
		break;
	case SIMON_STATE_WALKING_RIGHT:
		if (this->isAutoWalk)
		{
			vx = SIMON_AUTOWALKING_SPEED;
		}
		else
		{ 
			vx = SIMON_WALKING_SPEED;
		}
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (this->isAutoWalk)
		{
			vx = -SIMON_AUTOWALKING_SPEED;
		}
		else
		{
			vx = -SIMON_WALKING_SPEED;
		}
		nx = -1;
		break;
	case SIMON_STATE_JUMP: 
		vy = -SIMON_JUMP_SPEED_Y;
		isSitting = true;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		vx = 0;
		break;
	case SIMON_STATE_HURT:
		if (this->fight_start>0)
		{
			ResetFightTime();
		}
		this->vy = -SIMON_HURT_SPEED_Y;
		if (nx > 0)
		{
			this->vx = -SIMON_HURT_SPEED_X;
		}
		else
		{
			this->vx = SIMON_HURT_SPEED_X;
		}
		break;
	case SIMON_STATE_FIGHT_SIT:
		vx = 0;
		isSitting = true;
		if (!this->spawnSubweapon)
		{
			this->fight_start = GetTickCount();
		}
		else this->fight_start = -1;
		whip->ResetWhip();
		whip->StartCalculatorCollice();
		break;
	case SIMON_STATE_FIGHT_STAND:
		vx = this->state == SIMON_STATE_IDLE || this->state == SIMON_STATE_WALKING_LEFT
			|| this->state == SIMON_STATE_WALKING_RIGHT ? 0:vx;
		if (!this->spawnSubweapon)
		{
			this->fight_start = GetTickCount();
		}
		else this->fight_start = -1;
		whip->ResetWhip();
		whip->StartCalculatorCollice();
		break;
	case SIMON_STATE_DIE:
		this->hp = 0;
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_UPWHIP:
		whip->UpLevel();
		this->ResetFightAnimation();
		upgrade_start = GetTickCount();
		vx = 0;
		break;
	case SIMON_STATE_SIT:
		isSitting = true;
		vx = 0; // vx vận tốc phương x
		//nx=0; k cần xét nx vì khi bấm trái phải đã set nx ở 2 state phía trên
		break;

		//CAU THANG
	case SIMON_STATE_UPSTAIR_RIGHT:
	{
		vy = -SIMON_UPSTAIR_VELOCITY;
		vx = SIMON_UPSTAIR_VELOCITY;
		nx = 1;
		break;
	}
	case SIMON_STATE_UPSTAIR_LEFT:
	{
		vy = -SIMON_UPSTAIR_VELOCITY;
		vx = -SIMON_UPSTAIR_VELOCITY;
		nx = -1;
		break;
	}
	case SIMON_STATE_DOWNSTAIR_LEFT:
	{
		vy = SIMON_UPSTAIR_VELOCITY;
		vx = -SIMON_UPSTAIR_VELOCITY;
		nx = -1;
		break;
	}
	case SIMON_STATE_DOWNSTAIR_RIGHT:
	{
		vy = SIMON_UPSTAIR_VELOCITY;
		vx = SIMON_UPSTAIR_VELOCITY;
		nx = 1;
		break;
	}
	case SIMON_STATE_DOWNSTAIR_IDLE:
	{
		this->isOnStair = true;
		this->isFirstStepOnStair = true;
		this->startOnStair = false;
		if (nx == 1)
		{
			this->StairDirection = STAIR_TOP_RIGHT;
		}
		else if (nx == -1)
		{
			this->StairDirection = STAIR_TOP_LEFT;
		}
		if (this->lastState != SIMON_STATE_UPSTAIR_ATTACK && this->lastState != SIMON_STATE_DOWNSTAIR_ATTACK)
		{
			this->LastStepOnStairPos.x = this->x;
			this->LastStepOnStairPos.y = this->y;
		}
		else
		{
			this->lastState = -1;
		}
		vx = 0;
		vy = 0;
		break;
	}
	case SIMON_STATE_UPSTAIR_IDLE: {
		this->isOnStair = true;
		this->isFirstStepOnStair = true; 
		this->startOnStair = false; 
		if (nx == 1)
		{
			this->StairDirection = STAIR_BOTTOM_RIGHT;
		}
		else if (nx == -1)
		{
			this->StairDirection = STAIR_BOTTOM_LEFT;
		}
		if (this->lastState != SIMON_STATE_DOWNSTAIR_ATTACK
			&& this->lastState != SIMON_STATE_UPSTAIR_ATTACK)
		{
			this->LastStepOnStairPos.x = this->x;
			this->LastStepOnStairPos.y = this->y;
		}
		else
		{
			this->lastState = -1;
		}
		vx = 0;
		vy = 0;
		break;
	}
	case SIMON_STATE_UPSTAIR_ATTACK:
	{
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->vx = 0;
		this->vy = 0;
		this->fight_start = GetTickCount();
		whip->ResetWhip();
		whip->StartCalculatorCollice();
		break;
	}
	case SIMON_STATE_DOWNSTAIR_ATTACK: {
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->vx = 0;
		this->vy = 0;
		this->fight_start = GetTickCount();
		whip->ResetWhip();
		whip->StartCalculatorCollice();
		break;
	}
	}
	this->state = state;
}

void CSIMON::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	

	if (isSitting==true)
	{
		left = x+13;
		top = y+20;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;

	}
	else{
		left = x+13;
		top = y;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;

	}

}

void CSIMON::SetlastState(SimonProperties* prop)
{
	this->whip->SetState(prop->GetWhip());
	this->currenSubWeapon = prop->GetCurrentSub();
	this->heart = prop->GetHeart();
	this->hp = prop->GetHp();
	this->score = prop->GetScore();
}

