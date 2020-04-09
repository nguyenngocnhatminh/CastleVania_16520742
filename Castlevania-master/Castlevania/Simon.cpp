#include <algorithm>
#include "debug.h"

#include "SIMON.h"
#include "Game.h"
#include "Brick.h"
#include "Torch.h"

void CSIMON::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT> *coObjects)
{
	

	// Calculate dx, dy 
	CGameObject::Update(dt, scene);

	// Simple fall down
	vy += SIMON_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			 if (dynamic_cast<HiddenObject*>(e->obj)) {
				if (e->ny != 0) { // kiểm tra va chạm trục y có va chạm trục y nhảy vào đây
					if (GetState() == SIMON_STATE_JUMP) {
						SetState(SIMON_STATE_IDLE);
					}
					if (this->state == SIMON_STATE_FIGHT_STAND)
					{
						vx = 0;
					}

				}
				
				// cần xét kỹ phương va chạm

			}
			else
			{
				x += dx;
			//	if (ny != 0) y += dy;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];



	if (this->fight_start!=0)
	{
		if (this->state == SIMON_STATE_FIGHT_SIT)
		{
			whip->SetPosition(this->x - 1.5 * SIMON_BIG_BBOX_WIDTH, this->y+0.25* SIMON_BIG_BBOX_HEIGHT);
		}
		else
		{
			whip->SetPosition(this->x - 1.5 * SIMON_BIG_BBOX_WIDTH, this->y);
		}

		whip->SetNxDirection(this->nx);
		whip->Update(dt,scene, coObjects);
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
		whip->Render();
		break;
	case SIMON_STATE_FIGHT_SIT:
		ani = SIMON_ANI_SIT_ATTACK;
		whip->Render();
		break;
	case SIMON_STATE_DIE:
		break;

	default:
		break;
	}
	
	
	int alpha = 255;
	if (untouchable) alpha = 128;

	animations[ani]->Render(nx,x, y, alpha);

	/*RenderBoundingBox();*/
}

void CSIMON::SetState(int state)
{


	switch (state)
	{
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
		this->fight_start = GetTickCount();
		whip->ResetWhip();
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_SIT:
		vx = 0; // vx vận tốc phương x
		//nx=0; k cần xét nx vì khi bấm trái phải đã set nx ở 2 state phía trên
		break;
	}
	this->state = state;

}

void CSIMON::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 


	right = x + SIMON_BIG_BBOX_WIDTH;
	bottom = y + SIMON_BIG_BBOX_HEIGHT;

}

