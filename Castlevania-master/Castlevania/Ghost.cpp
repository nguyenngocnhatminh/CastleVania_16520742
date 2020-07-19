#include "Ghost.h"
#include "define.h"

void Ghost::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (this->isHidden == false)
	{
		l = x;
		t = y;
		r = x + GHOST_BBOX_WIDTH;
		b = y + GHOST_BBOX_HEIGHT;
	}

}

void Ghost::Render()
{
	if (this->isHidden)
		return;
	animations[0]->Render(nx, x, y);
}

void Ghost::SetStartDirection(int dir)
{
	this->start_direction = dir;
}

int Ghost::GetStartDirection()
{
	return this->start_direction;
}

void Ghost::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (this->IsDestroy())
		return;

	Enemy::Update(dt, scene, colliable_objects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colliable_objects, coEvents);

	if (this->isHidden)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			D3DXVECTOR2 cam = pScene->GetCamera();
			if(cam.x != 0)
			{
				if(this->start_direction==GHOST_DIRECTION_LEFT)
				{
					if (this->x + GHOST_BBOX_WIDTH > cam.x + SCREENSIZE::WIDTH)
					{
						this->isHidden = false;
						this->nx = GHOST_DIRECTION_LEFT;
					}
				}
				if (this->start_direction == GHOST_DIRECTION_RIGHT)
				{
					if (this->x > cam.x)
					{
						this->isHidden = false;
						this->nx = GHOST_DIRECTION_RIGHT;
					}
				}
			}
		}
	}

	float velocity = GHOST_SPEED_VX;

	if (!this->isHidden)
	{
		CGameObject::Update(dt, scene);
		if (dynamic_cast<PlayScene*>(scene))
		{
			if (!start_attack)
			{

				auto pScene = dynamic_cast<PlayScene*>(scene);
				float l, t, r, b;
				float ml, mt, mr, mb;
				this->GetBoundingBox(ml, mt, mr, mb);

				pScene->GetSimon()->GetBoundingBox(l, t, r, b);
				D3DXVECTOR2 simonPos;

				simonPos.x = l + (r - l) / 2;
				simonPos.y = t + (b - t) / 2;



				D3DXVECTOR2 bPos;

				bPos.x = ml + (mr - ml) / 2;
				bPos.y = mt + (mb - mt) / 2;


				if (bPos.x > simonPos.x)
				{
					nx = -1;
					int min = l - 60;
					int max = l;
					vx = -velocity;
					targer.x = rand() % (max + 1 - min) + min;
				}
				else
				{
					nx = 1;
					int min = r;
					int max = r + 60;
					targer.x = rand() % (max + 1 - min) + min;
					vx = velocity;
				}


				if (bPos.y > simonPos.y)
				{
					int min = t;
					int max = t + 60;
					vy = -velocity;
					targer.y = rand() % (max + 1 - min) + min;
				}
				else
				{
					int min = b;
					int max = b + 60;
					targer.y = rand() % (max + 1 - min) + min;
					vy = velocity;
				}



				auto tx = abs(targer.x - bPos.x) / velocity;
				auto ty = abs(targer.y - bPos.y) / velocity;

				minTime = tx < ty ? tx : ty;

				auto sinValue = abs(targer.y - bPos.y) / sqrt(pow(abs(bPos.x - targer.x), 2) + pow(abs(targer.y - bPos.y), 2));
				if (sinValue > 1)
				{
					sinValue = 1;
				}
				auto angle = asin(sinValue);
				this->angle = angle / PI * 180;
				start_attack = GetTickCount();
				DebugOut(L"Start \n");

			}

			if (start_attack != 0)
			{
				if (GetTickCount() - start_attack > minTime)
				{
					this->start_attack = 0;
					DebugOut(L"Stop\n");
				}
				else
				{
					x += dx * cos(this->angle * PI / 180);
					y += dy * sin(this->angle * PI / 180);
				}

			}
		}
	}

}

	
