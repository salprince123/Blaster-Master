#include "BallBot.h"
#include "PlayScence.h"
BallBot::BallBot(int x0, int y0, int x1, int y1, int nx)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vy = 0;
	this->nx = nx;
	this->ny = -1;
	this->SetState(BALLCARRY_STATE_UNACTIVE);
}
void BallBot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y - 2;
	right = x + BALLBOT_BBOX_WIDTH;
	bottom = y + BALLBOT_BBOX_HEIGHT;
	if (GetState() == BALLBOT_STATE_DIE)
	{
		left = right = top = bottom = 0;
	}
}
void BallBot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);

	if ((y - pY) > 0 && (y - pY) < BALLBOT_RANGE && state == BALLBOT_STATE_UNACTIVE)
	{
		if (nx > 0 && pX >= x)
		{
			SetState(BALLBOT_STATE_FLY);
		}			
		else if (nx < 0 && pX <= x)
		{
			SetState(BALLBOT_STATE_FLY);
		}
		//else DebugOut(L"SOMETHING Wrong!\n");
	}
	else if (state == BALLBOT_STATE_FLY)
	{
		if ((y - pY) < 0 /*|| (y - pY) > BALLBOT_RANGE*/)
		{
			x = x0;
			y = y0;
			return;
		}
		
		dx = vx * dt;
		if (ny == -1)
			dy = -vx * sin(45) * dt;
		else
			dy = vx * sin(45) * dt;
		if (y0 - y > 20)
			ny = -1 * nx;
		if (y - y0 > 20)
			ny = 1 * nx;
		x += dx;		
		y += dy;
	}
	
}
void BallBot::Render()
{
	int ani = 0;
	switch (state)
	{
	case BALLBOT_STATE_FLY:case BALLBOT_STATE_ACTIVE:case BALLBOT_STATE_UNACTIVE:
		if (nx < 0)
			ani = BALLBOT_ANI_LEFT;
		else if (nx > 0)
			ani = BALLBOT_ANI_RIGHT;
		break;
	case BALLBOT_STATE_DIE:
		ani = BALLBOT_ANI_DIE;
	default:
		break;
	}
	int alpha = 255;
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void BallBot::SetState(int state)
{
	Enemy::SetState(state);	
	switch (state)
	{
	case BALLBOT_STATE_FLY:
		vx = nx * BALLBOT_WALKING_SPEED;

	}
}