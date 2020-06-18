#include "Whip.h"
#include"Torch.h"
#include"debug.h"
#include "Effect.h"
#include"Spark.h"
#include"flame.h"
#include"PlayScene.h"
#include"ItemCollection.h"
#include"EffectCollection.h"
#include"Candle.h"
#include"BreakWall.h"
#include "Enemy.h"


bool Whip::CheckLastFrame()
{
	int ani = getCurrentAni();
	if (ani < 2) 
	{
		if (animations[ani]->GetCurrentFrame() < animations[ani]->GetlastFrame())
		{
			return false;
		}
	}
	else {
		if (animations[ani]->GetCurrentFrame() < 8) 
		{
			return false;
		}
	}
	return true;
}
void Whip::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	int ani = getCurrentAni();
	if (ani < 2)
	{
		if (animations[ani]->GetCurrentFrame() < animations[ani]->GetlastFrame())
		{
			hitObject = false;
			return;
		}
	}
	else {
		if (animations[ani]->GetCurrentFrame() < 8)
		{
			hitObject = false;
			return;
		}
	}

	CGameObject::Update(dt, scene);

	if (!collideOneTime)
	{
		for (size_t i = 0; i < colliable_objects->size(); i++)
		{
			LPGAMEOBJECT e = colliable_objects->at(i);
			if (CGameObject::isColliding(e))
			{
				if (dynamic_cast<Torch*>(e))
				{
					Torch* torch = dynamic_cast<Torch*>(e);
					hitObject = true;
					if (this->isColliding(torch))
					{
						ItemCollection* itemcollection = new ItemCollection();
						Item* item = itemcollection->SpawnItem(torch->GetItem(),e->x);
						EffectCollection* effectcollection = new EffectCollection();
						Effect* spark = effectcollection->SpawnEffect(SPARK);	//1: id spark
						Effect* flame = effectcollection->SpawnEffect(FLAME);	//2: id flame
						if (dynamic_cast<PlayScene*>(scene))
						{
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							DebugOut(L"Va cham voi torch \n");
							float tx, ty;
							torch->GetPosition(tx, ty);
							spark->SetPosition(tx, ty + 8);
							flame->SetPosition(tx + 5, ty + 10);
							item->SetPosition(tx, ty);
							pScene->SpawnObject(spark);
							pScene->SpawnObject(flame);
							pScene->SpawnObject(item);
							torch->SetDestroy();
						}
					}
				}
				else if (dynamic_cast<Candle*>(e))
				{
					Candle* candle = dynamic_cast<Candle*>(e);
					hitObject = true;
					if (this->isColliding(candle))
					{
						ItemCollection* itemcollection = new ItemCollection();
						Item* item = itemcollection->SpawnItem(candle->GetItem(),e->x);
						EffectCollection* effectcollection = new EffectCollection();
						Effect* spark = effectcollection->SpawnEffect(SPARK);	//1: id spark
						Effect* flame = effectcollection->SpawnEffect(FLAME);	//2: id flame
						if (dynamic_cast<PlayScene*>(scene))
						{
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							DebugOut(L"Va cham voi nen \n");
							float tx, ty;
							candle->GetPosition(tx, ty);
							spark->SetPosition(tx, ty + 8);
							flame->SetPosition(tx + 5, ty + 10);
							item->SetPosition(tx, ty);
							pScene->SpawnObject(spark);
							pScene->SpawnObject(flame);
							pScene->SpawnObject(item);
							candle->Destroy();
						}
					}
				}
				else if (dynamic_cast<BreakWall*>(e))
				{
					BreakWall* breakwall = dynamic_cast<BreakWall*>(e);
					hitObject = true;
					if (this->isColliding(breakwall))
					{
						ItemCollection* itemcollection = new ItemCollection();
						Item* item = itemcollection->SpawnItem(breakwall->GetItem(),e->x);
						if (dynamic_cast<PlayScene*>(scene))
						{
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							DebugOut(L"Va cham voi gach \n");
							float tx, ty;
							breakwall->GetPosition(tx, ty);
							if (breakwall->GetItem() != 0)
							{
								item->SetPosition(tx, ty);
								breakwall->SetState(BREAKWALL_STATE_BREAK);
								breakwall->SetDestroy();
								pScene->SpawnObject(item);
							}
							else
							{
								breakwall->SetState(BREAKWALL_STATE_BREAK);
								breakwall->SetDestroy();
							}
						}

					}
				}
				else if (dynamic_cast<Enemy*>(e)) {
					Enemy* f = dynamic_cast<Enemy*> (e);
					hitObject = true;
					EffectCollection* effectcollection = new EffectCollection();
					Effect* spark = effectcollection->SpawnEffect(SPARK);
					if (!f->IsDestroy())
					{
						if (dynamic_cast<PlayScene*>(scene))
						{
							spark->SetPosition(f->x, f->y);
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							pScene->SpawnObject(spark);
						}
						f->SubtractHP(this->damage);
						if (f->GetHP() == 0)
						{
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								pScene->GetSimon()->SetScore(pScene->GetSimon()->GetScore() + f->GetScore());
							}

							ItemCollection* itemcollection = new ItemCollection();
							Item* item = itemcollection->SpawnRandomItem(f->x);
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								float tx, ty;
								f->GetPosition(tx, ty);
								item->SetPosition(tx, ty);
								pScene->SpawnObject(item);
							}
							f->Destroy();
						}

					}
					this->Destroy();
				}
			}
		}
		this->collideOneTime = true;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 

		CalcPotentialCollisions(colliable_objects, coEvents);


		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{


			DebugOut(L"Swept aabb \n");
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


			for (UINT i = 0; i < coEvents.size(); i++)
			{
				LPCOLLISIONEVENT e = coEvents[i];
				if (dynamic_cast<Torch*>(e->obj)) {
					Torch* torch = dynamic_cast<Torch*>(e->obj);
					if (this->isColliding(torch))
					{
						ItemCollection* itemcollection = new ItemCollection();
						Item* item = itemcollection->SpawnItem(torch->GetItem(),torch->x);
						EffectCollection* effectcollection = new EffectCollection();
						Effect* spark = effectcollection->SpawnEffect(SPARK);	//1: id spark
						Effect* flame = effectcollection->SpawnEffect(FLAME);	//2: id flame
						if (dynamic_cast<PlayScene*>(scene))
						{
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							DebugOut(L"Va cham voi torch \n");
							float tx, ty;
							torch->GetPosition(tx, ty);
							spark->SetPosition(tx, ty + 8);
							flame->SetPosition(tx + 5, ty + 10);
							item->SetPosition(tx, ty);
							pScene->SpawnObject(spark);
							pScene->SpawnObject(flame);
							pScene->SpawnObject(item);
							torch->SetDestroy();
						}
					}
				}
				else if (dynamic_cast<BreakWall*>(e->obj))
				{
					BreakWall* breakwall = dynamic_cast<BreakWall*>(e->obj);
					if (this->isColliding(breakwall))
					{
						ItemCollection* itemcollection = new ItemCollection();
						Item* item = itemcollection->SpawnItem(breakwall->GetItem(),breakwall->x);
						if (dynamic_cast<PlayScene*>(scene))
						{
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							DebugOut(L"Va cham voi gach \n");
							float tx, ty;
							breakwall->GetPosition(tx, ty);
							if (breakwall->GetItem() != 0)
							{
								item->SetPosition(tx, ty);
								breakwall->SetState(BREAKWALL_STATE_BREAK);
								breakwall->SetDestroy();
								pScene->SpawnObject(item);
							}
							else
							{
								breakwall->SetState(BREAKWALL_STATE_BREAK);
								breakwall->SetDestroy();
							}
						}

					}
				}

				else if (dynamic_cast<Candle*>(e->obj))
				{
					Candle* candle = dynamic_cast<Candle*>(colliable_objects->at(i));
					if (this->isColliding(candle))
					{
						ItemCollection* itemcollection = new ItemCollection();
						Item* item = itemcollection->SpawnItem(candle->GetItem(),candle->x);
						EffectCollection* effectcollection = new EffectCollection();
						Effect* spark = effectcollection->SpawnEffect(SPARK);	//1: id spark
						Effect* flame = effectcollection->SpawnEffect(FLAME);	//2: id flame
						if (dynamic_cast<PlayScene*>(scene))
						{
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							DebugOut(L"Va cham voi nen \n");
							float tx, ty;
							candle->GetPosition(tx, ty);
							spark->SetPosition(tx, ty + 8);
							flame->SetPosition(tx + 5, ty + 10);
							item->SetPosition(tx, ty);
							pScene->SpawnObject(spark);
							pScene->SpawnObject(flame);
							pScene->SpawnObject(item);
							candle->Destroy();
						}
					}
				}
				else if (dynamic_cast<Enemy*>(e->obj)) {
					Enemy* f = dynamic_cast<Enemy*> (e->obj);
					hitObject = true;
					EffectCollection* effectcollection = new EffectCollection();
					Effect* spark = effectcollection->SpawnEffect(SPARK);
					if (!f->IsDestroy())
					{
						f->SubtractHP(this->damage);
						if (f->GetHP() == 0)
						{
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								pScene->GetSimon()->SetScore(pScene->GetSimon()->GetScore() + f->GetScore());
							}
							ItemCollection* itemcollection = new ItemCollection();
							Item* item = itemcollection->SpawnRandomItem(f->x);
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								float tx, ty;
								f->GetPosition(tx, ty);
								item->SetPosition(tx, ty);
								pScene->SpawnObject(item);
							}

							f->Destroy();;
						}

					}
				}
				else {
					x += dx;
					y += dy;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

int Whip::getCurrentAni()
{
	int ani = 0;
	switch (state)
	{
		case WHIP_STATE_NORMAL:
			ani = WHIP_ANI_NORMAL;
			break;
		case WHIP_STATE_CHAIN:
			ani = WHIP_ANI_CHAIN;
			break;
		case WHIP_STATE_MORNINGSTAR:
			ani = WHIP_ANI_MORNINGSTAR;
			break;
	}
	return ani;

}

void Whip::Render()
{
	int ani = getCurrentAni();
	
	animations[ani]->Render(nx,x,y);
	RenderBoundingBox();
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (nx >0) {
		l = x + 60 * 2 + 12;
		t = y + 12;
	}
	else if (nx < 0 ) {
		if (state != WHIP_STATE_MORNINGSTAR)
			l = x + 55 - 4;
		else
			l = x + 55 - 30;
		t = y + 12;
	}


	switch (this->state)
	{
	case WHIP_STATE_NORMAL: {
		r = l + WHIP_BBOX_NORMAL_WIDTH;
		b = t + WHIP_BBOX_NORMAL_HEIGHT;
		break;
	}
	case WHIP_STATE_CHAIN: {
		r = l + WHIP_BBOX_CHAIN_WIDTH;
		b = t + WHIP_BBOX_CHAIN_HEIGHT;
		break;

	}
	case WHIP_STATE_MORNINGSTAR: {
		r = l + WHIP_BBOX_MORNINGSTAR_WIDTH;
		b = t + WHIP_BBOX_MORNINGSTAR_HEIGHT;
		break;
	}
	}
	
}

void Whip::ResetWhip() {
	switch (state) {
	case WHIP_STATE_NORMAL:
		animations[WHIP_ANI_NORMAL]->ResetFrame();
	case WHIP_STATE_CHAIN:
		animations[WHIP_ANI_CHAIN]->ResetFrame();
	case WHIP_STATE_MORNINGSTAR:
		animations[WHIP_ANI_MORNINGSTAR]->ResetFrame();
	}
	
}

void Whip::UpLevel() {
	this->state++;
	if (this->state >= 2) {
		this->state = WHIP_STATE_MORNINGSTAR;
	}
	DebugOut(L"Whip state=%d", this->state);
}
