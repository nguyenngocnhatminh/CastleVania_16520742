#include "Enemy.h"
#include "define.h"

void Enemy::Render()
{
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void Enemy::SetIsAttack(bool x)
{
	this->isAttack = x;
}
bool Enemy::IsAttack()
{
	return this->isAttack;
}

void Enemy::SpawnItem()
{
	if (this->setDestroy) {

	}
}

void Enemy::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (this->IsAttack())
		{
			if (y < cam.y - 200 || y > cam.y + SCREENSIZE::HEIGHT - 100)
			{
				this->isDestroy = true;
			}
		}

	}
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (pScene->GetIsFreeze() == true)
		{
			vx = 0;
			vy = 0;
			if (!animations[0]->CheckLockAnimation())
			{
				animations[0]->LockAnimation(true);
			}
			return;
		}
		else
		{
			animations[0]->LockAnimation(false);
		}
	}

	if (this->isHurt == true)
	{
		if (this->time_hurt != 0 && GetTickCount() - time_hurt >= TIME_HURT)
		{
			this->isHurt = false;
			this->time_hurt = 0;

			animations[0]->LockAnimation(false);
		}
		else
		{
			vx = 0;
			vy = 0;
			if (!animations[0]->CheckLockAnimation())
			{
				animations[0]->LockAnimation(true);
			}
			return;
		}
	}

	if (this->isHurtByBom)
	{
		if (this->time_hurtbybom != 0 && GetTickCount() - time_hurtbybom >= TIME_HURT)
		{
			this->isHurtByBom = false;
			this->time_hurtbybom = 0;
		}
	}
	if (this->isHurtByBomReturn)
	{
		if (this->time_hurtbybom_return != 0 && GetTickCount() - time_hurtbybom_return >= TIME_HURT)
		{
			this->isHurtByBomReturn = false;
			this->time_hurtbybom_return = 0;
		}
	}

	if (isBurn == true)
	{
		if (time_burn != 0 && GetTickCount() - time_burn >= TIME_BURN)
		{
			this->isBurn = false;
			this->time_burn = 0;
		}
	}

	if (isDameByHolywater == true)
	{
		if (time_holywater != 0 && GetTickCount() - time_holywater >= TIME_HOLY)
		{
			this->isDameByHolywater = false;
			this->time_holywater = 0;
		}
	}
}