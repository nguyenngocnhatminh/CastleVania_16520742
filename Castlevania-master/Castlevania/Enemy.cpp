#include "Enemy.h"
#include "define.h"

void Enemy::Render()
{
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
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

		if (y < cam.y || y > cam.y + SCREENSIZE::HEIGHT - 100)
		{
			this->isDestroy = true;
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
}