#include "Whip.h"
#include"Torch.h"
#include"debug.h"
#include "Effect.h"
#include"Spark.h"
#include"flame.h"
#include"PlayScene.h"
#include"ItemCollection.h"

void Whip::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	int ani = getCurrentAni();
	if (ani < 2)
	{
		if (animations[ani]->GetCurrentFrame() < animations[ani]->GetlastFrame())
		{
			return;
		}
	}
	else {
		if(animations[ani]->GetCurrentFrame()<8)
		{
			return;
		}
	}

	for (size_t i = 0; i < colliable_objects->size(); i++)
	{
		if (dynamic_cast<Torch*>(colliable_objects->at(i)))
		{
			Torch* torch = dynamic_cast<Torch*>(colliable_objects->at(i));
			if (this->isColliding(torch))
			{
				ItemCollection* itemcolection = new ItemCollection();
				Item* item = itemcolection->SpawnItem(torch->GetItem());
				if (dynamic_cast<PlayScene*>(scene)) 
				{
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					DebugOut(L"Va cham voi torch \n");
					float tx, ty;
					Effect* spark = new Spark();
					torch->GetPosition(tx, ty);
					spark->SetPosition(tx, ty);
					Effect* flame = new Flame();
					flame->SetPosition(tx + 5, ty + 10);
					item->SetPosition(tx, ty);
					pScene->SpawnObject(spark);
					pScene->SpawnObject(flame);
					pScene->SpawnObject(item);
					torch->SetDestroy();
					UpLevel();
				}
			}

	
		}

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
