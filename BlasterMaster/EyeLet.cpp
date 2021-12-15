#include "EyeLet.h"
#include "PlayScence.h"
EyeLet::EyeLet(int x0, int y0, int x1, int y1, int nx)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vx = nx*EYELET_WALKING_SPEED;
	this->vy = EYELET_FLYING_UP_SPEED;
	this->ny = -1;
	this->nx = nx;
	//this->vy = 0;
	this->SetState(EYELET_STATE_WALKING_RIGHT);
}
void EyeLet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y-8;
	right = x + EYELET_BBOX_WIDTH;
	bottom = y + EYELET_BBOX_HEIGHT;
	if (GetState() == EYELET_STATE_DIE)
	{
		left = right = top = bottom = 0;
	}
}
void EyeLet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);
	if (nx < 0 && (x - pX)>30 && abs(y-pY)<70)
	{
		this->SetState(LADYBIRD_STATE_WALKING_RIGHT);
		active = 1; 
	}
	else if (nx >0 && (pX - x) > 30 && abs(y - pY) < 70)
	{
		active = 1;	
		this->SetState(LADYBIRD_STATE_WALKING_RIGHT);
	}
	if (active == 0)
	{
		this->SetState(EYELET_STATE_UNACTIVE);
		return;
	}
	
	this->dt = dt;
	dx = vx*dt;
	if (y0 - y > 30)
		ny = -1*nx;
	if (y - y0 > 30)
		ny = 1* nx;
	if(ny==1)
		dy = -vx * sin(45) * dt;
	else 
		dy = vx * sin(45) * dt;
	x += dx;
	y += dy;
}
void EyeLet::Render()
{
	int ani = 0;
	if (state == EYELET_STATE_WALKING_LEFT)
	{
		ani = EYELET_ANI_WALKING_LEFT;
	}
	else if (state == EYELET_STATE_WALKING_RIGHT)
		ani = EYELET_ANI_WALKING_RIGHT;
	else if (state == EYELET_STATE_DIE || state == EYELET_STATE_UNACTIVE)
		ani = EYELET_ANI_DIE;
	else if (state == EYELET_STATE_COIN)
		ani = EYELET_ANI_COIN;
	int alpha = 255;

	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void EyeLet::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
		case EYELET_STATE_WALKING_LEFT:
			break;
		case EYELET_STATE_WALKING_RIGHT:
			break;
		case EYELET_STATE_DIE:
			y = -1000;
			break;
		case EYELET_STATE_COIN:
			vx = 0;
			vy = 0;
			break;
		case EYELET_STATE_UNACTIVE:
			break;
	}
}