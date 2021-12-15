#include "BallCarry.h"
#include "PlayScence.h"
BallCarry::BallCarry(int x0, int y0, int x1, int y1, int nx)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;	
	this->vy = 0;
	this->ny = -1;
	this->nx = nx;
	this->vy = -1;
	this->SetState(BALLCARRY_STATE_UNACTIVE);
}
void BallCarry::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y - 2;
	right = x + BALLCARRY_BBOX_WIDTH;
	bottom = y + BALLCARRY_BBOX_HEIGHT;
	if (GetState() == BALLCARRY_STATE_DIE)
	{
		left = right = top = bottom = 0;
	}
}
void BallCarry::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);
	
	if ((pX - x) < BALLCARRY_RANGE && (pX - x) >0 && state==BALLCARRY_STATE_UNACTIVE && abs(y-pY)<10)
	{
		SetState(BALLCARRY_STATE_FIRE);
		nx = 1;
	}
	else if( (x-pX) < BALLCARRY_RANGE && (x - pX)>0 && state == BALLCARRY_STATE_UNACTIVE && abs(y - pY) < 10)
	{
		SetState(BALLCARRY_STATE_FIRE);
		nx = -1;
	}
	if (state == BALLCARRY_STATE_FIRE)
	{
		if ((GetTickCount64() - t_fire0) > 2000)
		{
			DebugOut(L"OUT OF TIME\n");
			SetState(nx * BALLCARRY_STATE_WALKING_LEFT);
		}
	}
	else
	{
		t_fire0 = GetTickCount64();
	}
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	// turn off collision when die 
	if (state != BALLCARRY_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	
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
				//DebugOut(L"TURN BACK %f %f\n",nx,ny);
				if (nx != 0)
				{
					SetState(-state);
				}
					
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void BallCarry::Render()
{
	int ani = 0;
	if (state == BALLCARRY_STATE_WALKING_LEFT)
	{
		ani = BALLCARRY_ANI_WALKING_LEFT;
	}
	else if (state == BALLCARRY_STATE_WALKING_RIGHT)
		ani = BALLCARRY_ANI_WALKING_RIGHT;
	else if (state == BALLCARRY_STATE_DIE )
		ani = BALLCARRY_ANI_DIE;
	else if (state == BALLCARRY_STATE_UNACTIVE)
		ani = BALLCARRY_ANI_SLEEP;
	else if (state == BALLCARRY_STATE_COIN)
		ani = BALLCARRY_ANI_COIN;
	else if (state == BALLCARRY_STATE_FIRE)
		ani = BALLCARRY_ANI_FIRE;
	int alpha = 255;

	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void BallCarry::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case BALLCARRY_STATE_WALKING_LEFT:
		vx = -BALLCARRY_WALKING_SPEED;
		break;
	case BALLCARRY_STATE_WALKING_RIGHT:
		vx = BALLCARRY_WALKING_SPEED;
		break;
	case BALLCARRY_STATE_DIE:
		y = -1000;
		break;
	case BALLCARRY_STATE_COIN:
		vx = 0;
		vy = 0;
		break;
	case BALLCARRY_STATE_FIRE:
		break;
	case BALLCARRY_STATE_UNACTIVE:
		break;
	}
}