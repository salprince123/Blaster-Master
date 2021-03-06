#include "GuardLaser.h"
#include "PlayScence.h"
GuardLaser::GuardLaser(int x0, int y0, int x1, int y1, int nx)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vy = 0;
	this->nx = 1;
	this->ny = 0;
	this->SetState(GUARDLASER_STATE_ACTIVE);
}
void GuardLaser::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GUARDLASER_BBOX_WIDTH;
	bottom = y + GUARDLASER_BBOX_HEIGHT ;
	if (GetState() == GUARDLASER_STATE_DIE)
	{
		left = right = top = bottom = 0;
	}
}
void GuardLaser::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);	
	Enemy::Update(dt, coObjects);
	if (state == GUARDLASER_STATE_ACTIVE || state == GUARDLASER_STATE_FIRE)
	{		
		if ((y - pY) > 0 && (y - pY) < GUARDLASER_RANGE)
		{
			if(abs(x-pX)< GUARDLASER_BBOX_WIDTH/2)
			SetState(GUARDLASER_STATE_FIRE);
		}
		if (state == GUARDLASER_STATE_FIRE)
		{
			if (GetTickCount64() - tFire > 3000)
			{
				tFire = 0;
				SetState(GUARDLASER_STATE_ACTIVE);
			}
		}
	}
	vx = nx * GUARDLASER_WALIKNG_SPEED;
	vy = 0;
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx=0, ny;
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
				this->nx = -this->nx;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void GuardLaser::Render()
{
	int ani = GUARDLASER_ANI_DIE;
	int alpha = 255;
	if (isShoot != 0)
		alpha = 150;
	if (state == GUARDLASER_STATE_ACTIVE )
	{
		if (nx < 0)
			ani = GUARDLASER_ANI_IDLE_LEFT;
		else if (nx > 0)
			ani = GUARDLASER_ANI_IDLE_RIGHT;
	}
	else if (state == GUARDLASER_STATE_FIRE)
	{
		if (nx < 0)
			ani = GUARDLASER_ANI_FIRE_LEFT;
		else if (nx > 0)
			ani = GUARDLASER_ANI_FIRE_RIGHT;
	}
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void GuardLaser::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case GUARDLASER_STATE_FIRE:
		if (tFire == 0)
			tFire = GetTickCount64();
		break;
	case GUARDLASER_STATE_DIE:
		x = -1000;
		y = -1000;
		break;
	}
}