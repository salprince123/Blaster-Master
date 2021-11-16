#include "Frog.h"
Frog::Frog(float x, float y) : CGameObject()
{
	level = FROG_LEVEL;
	untouchable = 0;
	SetState(FROG_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void Frog::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += FROG_GRAVITY * dt;
	//if (x <= 0 && y> CGame::GetInstance()->GetScreenHeight() / 2) x = 0;
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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		/*for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		}*/
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Frog::Render()
{
	int ani = -1;
	if (state == FROG_STATE_DIE)
		ani = FROG_ANI_DIE;
	else
		if (level == FROG_LEVEL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = FROG_ANI_IDLE_RIGHT;
				else ani = FROG_ANI_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = FROG_ANI_WALKING_RIGHT;
			else ani = FROG_ANI_WALKING_LEFT;
		}
		else if (level == PRINCE_LEVEL)
		{
			/*if (vx == 0)
			{
				if (nx > 0) ani = FROG_ANI_SMALL_IDLE_RIGHT;
				else ani = FROG_ANI_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = FROG_ANI_SMALL_WALKING_RIGHT;
			else ani = FROG_ANI_SMALL_WALKING_LEFT;*/
			//render here
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

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
		break;
	case FROG_STATE_WALKING_LEFT:
		vx = -FROG_WALKING_SPEED;
		nx = -1;
		break;
	case FROG_STATE_JUMP:
		vy = -FROG_JUMP_SPEED_Y;
		break;
	case FROG_STATE_IDLE:
		vx = 0;
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
}

/*
	Reset Mario status to the beginning state of a scene
*/
void Frog::Reset()
{
	SetState(FROG_STATE_IDLE);
	SetLevel(FROG_LEVEL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}