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
#include"Entrance.h"
#include"Stair.h"
#include"define.h"

void CSIMON::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt, scene);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x)
		{
			x=cam.x;
		}
	//	else if (x > cam.x + SCREENSIZE::WIDTH - SIMON_BBOX_WIDTH)
	//	{
	//		x = cam.x + SCREENSIZE::WIDTH - SIMON_BBOX_WIDTH;
	//	}
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
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny <= 0) // ny lớn hơn 0 simon overlap với ground trong trường hợp simon va chạm heart theo ny
			y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				if (e->ny != 0) { // kiểm tra va chạm trục y có va chạm trục y nhảy vào đây
					if (GetState() == SIMON_STATE_JUMP && vy>=0) {
						SetState(SIMON_STATE_IDLE);
					}
					if (this->state == SIMON_STATE_FIGHT_STAND)
					{
						vx = 0;
					}
					if (ny != 0) vy = 0;
					// cần xét kỹ phương va chạm
					if (state != SIMON_STATE_ENTERCASTLE)
					{
						if (nx != 0) vx = 0;
					}

				}
				if (state == SIMON_STATE_ENTERCASTLE)
				{
					break;
				}
				// cần xét kỹ phương va chạm
			}
			else
			{
				if (dynamic_cast<Item*>(e->obj))
				{
					Item* item = dynamic_cast<Item*>(e->obj);
					if (!item->IsDestroy())
					{
						if (dynamic_cast<BigHeart*>(e->obj))
						{
						}
						if (dynamic_cast<WhipItem*>(e->obj))
						{
							this->SetState(SIMON_STATE_UPWHIP);
						}
						if (dynamic_cast<DaggerItem*>(e->obj))
						{
							currenSubWeapon = DAGGER;
						}
						item->Destroy();
					}

				}
				else if (dynamic_cast<Entrance*>(e->obj))
				{
					if (e->nx != 0) // va chạm chiều x
						x += dx;
					if (e->ny != 0)
						y += dy;
					auto entrance = dynamic_cast<Entrance*>(e->obj);
					CGame::GetInstance()->SwitchScene(entrance->GetNextMapId());

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



	if (this->fight_start!=0)
	{
		if (!this->spawnSubweapon)
		{
			if (this->state == SIMON_STATE_FIGHT_SIT)
			{
				whip->SetPosition(this->x - 1.5 * SIMON_BBOX_WIDTH, this->y + 0.25 * SIMON_BBOX_HEIGHT);
			}
			else
			{
				whip->SetPosition(this->x - 1.5 * SIMON_BBOX_WIDTH, this->y);
			}

			whip->SetNxDirection(this->nx);
			whip->Update(dt, scene, coObjects);
		}
		else if (!isSpawnSubweapon && this->currenSubWeapon!=0)
		{
			SubWeaponCollection* sub = new SubWeaponCollection();
			SubWeapon* subWeapon = sub->SpawnSubWeapon(currenSubWeapon);
			subWeapon->SetPosition(this->x, this->y);
			subWeapon->SetNx(this->nx);
			if (dynamic_cast<PlayScene*>(scene))
			{
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				pScene->SpawnObject(subWeapon);
			}
			if (!subWeapon->isDestroy)
			{
				this->isSpawnSubweapon = true;
			}
		}
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
	case SIMON_STATE_FIGHT_STAND:
		ani = SIMON_ANI_STAND_ATTACK;
		break;
	case SIMON_STATE_FIGHT_SIT:
		ani = SIMON_ANI_SIT_ATTACK;
		break;
	case SIMON_STATE_DIE:
		break;
	case SIMON_STATE_UPWHIP:
		ani = SIMON_ANI_UPWHIP;
		break;
	default:
		break;
	}
	
	if (this->fight_start != 0 && !this->spawnSubweapon)
	{
		whip->Render();
	}
	
	int alpha = 255;
	if (untouchable) alpha = 128;

	animations[ani]->Render(nx,x, y, alpha);

	//RenderBoundingBox();
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
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP: // nhảy rồi thì chắc ăn k chạm đất
		vy = -SIMON_JUMP_SPEED_Y;
		isSitting = true;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_FIGHT_STAND:
		vx = this->state == SIMON_STATE_IDLE || this->state == SIMON_STATE_WALKING_LEFT
			|| this->state == SIMON_STATE_WALKING_RIGHT ? 0:vx;
		this->fight_start = GetTickCount();
		whip->ResetWhip();
		break;
	case SIMON_STATE_FIGHT_SIT:
		vx = 0;
		isSitting = true;
		this->fight_start = GetTickCount();
		whip->ResetWhip();
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_SIT:
		isSitting = true;
		vx = 0; // vx vận tốc phương x
		//nx=0; k cần xét nx vì khi bấm trái phải đã set nx ở 2 state phía trên
		break;
	case SIMON_STATE_UPWHIP:
		whip->UpLevel();
		this->ResetFightAnimation();
		upgrade_start = GetTickCount();
		vx = 0;
		break;
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

