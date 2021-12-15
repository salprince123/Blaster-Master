#include "Frog.h"
#include "Boom.h"
#include "PlayScence.h"
Frog::Frog(float x, float y) : CGameObject()
{
	//level = FROG_LEVEL;
	int id = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetId();
	if (id == 1)
	{
		level = FROG_LEVEL;
		//level=LITTLE_PRINCE_LEVEL;
		SetState(FROG_STATE_IDLE);
	}		
	else
	{
		level = PRINCE_LEVEL;
		SetState(PRINCE_STATE_WALKING_DOWN);
	}
		
	untouchable = 0;
	
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	this->maxBullet = MAX_BULLET;
}

void Frog::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	// Calculate dx, dy 
	int id = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetId();
	CGameObject::Update(dt);
	if(x <= 0) x = 0;
	if (id == 1)
	{
		if (y > 384 && y < 385)
		{
			if (nx > 0)
			{
				if (x < 1357 && x > 1208)
				{
					x += 2;
					return;
				}
			}
			else
			{
				if (x < 1357 && x > 1208)
				{
					x -= 2;
					return;
				}
			}
		}
		else if (y > 128 && y < 129)
		{
			if (nx > 0)
			{
				if (x < 1357 && x > 1208)
				{
					x += 2;
					return;
				}
			}
			else
			{
				if (x < 1357 && x > 1208)
				{
					x -= 2;
					return;
				}
			}
		}
	}
	else if(id == 2)
	{
		if (y <= 340 && y >= 246 && x >= 112 && x <= 148)
			y -= 2;
		if (y <= 320 && y >= 224 && x >= 368 && x <= 400)
			y += 2;
	}
	//at small portal
	if (y > 384 && y < 385)
	{
		if (nx > 0)
		{
			if (x < 1357 && x > 1208)
			{
				x+=2;
				return;
			}
		}
		else
		{
			if (x < 1357 && x > 1208)
			{
				x-=2;
				return;
			}
		}
	}
	else if (y > 128 && y < 129)
	{
		if (nx > 0)
		{
			if (x < 1357 && x > 1208)
			{
				x += 2;
				return;
			}
		}
		else
		{
			if (x < 1357 && x > 1208)
			{
				x -= 2;
				return;
			}
		}
	}
	// Simple fall down
	if(id==1)
		vy += FROG_GRAVITY*dt ;
	//if (state == FROG_STATE_FIRE)
		//SetState(oldState);
	//Handle update state for Frog
	if (GetState() == FROG_STATE_JUMPING_UP)
	{
		if (vy <= 0)
			SetState(FROG_STATE_FALLING_DOWN);
	}
	//
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	// turn off collision when die 
	if (state != FROG_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > FROG_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
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
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (GetState() == FROG_STATE_FALLING_DOWN)
					SetState(FROG_STATE_IDLE);
				if (nx < 0)
					x-=3;
				else if (nx > 0)
					x += 3;
			}
			else if (dynamic_cast<Boom*>(e->obj))
			{
				if (dynamic_cast<Boom*>(e->obj)->GetState() == BOOM_STATE_ALIVE)
					 StartUntouchable();
			}
			else if (dynamic_cast<EyeLet*>(e->obj))
			{	
				if (dynamic_cast<EyeLet*>(e->obj)->GetState() == EYELET_STATE_COIN)
				{
					e->obj->SetState(EYELET_STATE_DIE);
				}
				else if(dynamic_cast<EyeLet*>(e->obj)->GetState() != EYELET_STATE_UNACTIVE) 
					StartUntouchable();
			}
			else if (dynamic_cast<LadyBird*>(e->obj))
			{
				if (dynamic_cast<LadyBird*>(e->obj)->GetState() == LADYBIRD_STATE_COIN)
				{
					e->obj->SetState(LADYBIRD_STATE_DIE);
				}
				else
					StartUntouchable();
			}
			else if (dynamic_cast<BallCarry*>(e->obj))
			{
				if (dynamic_cast<BallCarry*>(e->obj)->GetState() == BALLCARRY_STATE_COIN)
				{
					e->obj->SetState(BALLCARRY_STATE_DIE);
				}
				else if (dynamic_cast<BallCarry*>(e->obj)->GetState() != BALLCARRY_STATE_UNACTIVE)
					StartUntouchable();
			}
			else if (dynamic_cast<BallBot*>(e->obj))
			{
				if (dynamic_cast<BallCarry*>(e->obj)->GetState() != BALLBOT_STATE_UNACTIVE)
					StartUntouchable();
			}
			else if (dynamic_cast<Bullet*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
				{
					if (dynamic_cast<Bullet*>(e->obj)->enemyHandle != NULL)
						dynamic_cast<Bullet*>(e->obj)->SetState(BULLET_STATE_DIE);
					SetState(BULLET_STATE_DIE);
				}
				else StartUntouchable();
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				if(level==LITTLE_PRINCE_LEVEL && p->GetSceneId()==2)
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Frog::Render()
{	
	//int alpha = 255;
	//animation_set->at(0)->Render(x, y, alpha);
	int alpha = 255;
	if (untouchable) alpha = 128;
	if (level == PRINCE_LEVEL)
	{
		int ani = 1;		
		if (state == FROG_STATE_IDLE)
		{
			if (ny == 0)
			{
				if (nx < 0)
					ani = PRINCE_ANI_IDLE_LEFT;
				else ani = PRINCE_ANI_IDLE_RIGHT;
			}
			else
			{
				if (ny < 0)
					ani = PRINCE_ANI_IDLE_DOWN;
				else ani = PRINCE_ANI_IDLE_UP;
			}
		}			
		else if (state == FROG_STATE_WALKING_RIGHT || state == PRINCE_STATE_FIRE_RIGHT)
			ani = PRINCE_ANI_WALKING_RIGHT;
		else if (state == FROG_STATE_WALKING_LEFT || state == PRINCE_STATE_FIRE_LEFT)
			ani = PRINCE_ANI_WALKING_LEFT;
		else if (state == PRINCE_STATE_WALKING_DOWN || state == PRINCE_STATE_FIRE_DOWN)
			ani = PRINCE_ANI_WALKING_DOWN;
		else if (state == PRINCE_STATE_WALKING_UP || state == PRINCE_STATE_FIRE_UP)
			ani = PRINCE_ANI_WALKING_UP;
		animation_set->at(ani)->Render(x, y, alpha);
	}
	else if (level == LITTLE_PRINCE_LEVEL)
	{
		int ani = LITTLE_PRINCE_ANI_IDLE_LEFT;
		if (state == FROG_STATE_IDLE)
		{
			if (ny == 0)
			{
				if (nx < 0)
					ani = LITTLE_PRINCE_ANI_IDLE_LEFT;
				else ani = LITTLE_PRINCE_ANI_IDLE_RIGHT;
			}
		}
		else if (state == FROG_STATE_WALKING_RIGHT )
			ani = LITTLE_PRINCE_ANI_WALKING_RIGHT;
		else if (state == FROG_STATE_WALKING_LEFT )
			ani = LITTLE_PRINCE_ANI_WALKING_LEFT;
		animation_set->at(ani)->Render(x, y, alpha);
	}
	//RenderBoundingBox();
}

void Frog::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
		case FROG_STATE_WALKING_RIGHT:
			vx = FROG_WALKING_SPEED;
			nx = 1;
			ny = 0;
			break;
		case FROG_STATE_WALKING_LEFT:
			vx = -FROG_WALKING_SPEED;
			nx = -1;
			ny = 0;
			break;
		case PRINCE_STATE_WALKING_DOWN:
			vy = -FROG_WALKING_SPEED;
			ny = -1;
			nx = 0;
			break;
		case PRINCE_STATE_WALKING_UP:
			vy = FROG_WALKING_SPEED;
			ny = 1;
			nx = 0;
			break;
		case FROG_STATE_JUMP:
			vy = FROG_JUMP_SPEED_Y;
			SetState(FROG_STATE_JUMPING_UP);
			break;
		case FROG_STATE_JUMPING_UP:
			break;
		case FROG_STATE_FALLING_DOWN:
			break;
		case FROG_STATE_IDLE:
		{
			vx = 0;
			if(level==PRINCE_LEVEL)
				vy = 0;
			break;
		}	
		case FROG_STATE_FIRE:
			//SetState(oldState);
			break;
		case FROG_STATE_DIE:
			break;
	}
}

void Frog::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == FROG_LEVEL)
	{
		right = x + FROG_BBOX_WIDTH;
		bottom = y + FROG_BBOX_HEIGHT;
	}
	else if (level == PRINCE_LEVEL)
	{
		right = x + PRINCE_BBOX_WIDTH;
		bottom = y + PRINCE_BBOX_HEIGHT;
	}
	else if (level == LITTLE_PRINCE_LEVEL)
	{
		right = x + 8;
		bottom = y + 15;
	}
}

void Frog::Reset()
{
	SetState(FROG_STATE_IDLE);
	SetLevel(FROG_LEVEL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}