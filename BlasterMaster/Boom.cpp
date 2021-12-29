#include "Boom.h"
#include "Utils.h"
#include "PlayScence.h"
Boom::Boom()
{
	SetState(BOOM_STATE_ALIVE);
	health = 3;
}
void Boom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x+5;
	top = y-8;
	right = x + BOOM_BBOX_WIDTH;

	if (state == BOOM_STATE_DIE)
		bottom = y + BOOM_BBOX_HEIGHT_DIE;
	else
		bottom = y + BOOM_BBOX_HEIGHT;
}
void Boom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float pX = player->x; float pY = player->y;
	if (abs(x - pX) < 20 && (y - pY) > 10)
		SetState(BOOM_STATE_FIRE);
	Enemy::Update(dt, coObjects);
	if (isShoot != 0)
	{
		if (time == 0)
			time = GetTickCount64();
		else if (GetTickCount64() - time > 200)
		{
			time = 0;
			isShoot = 0;
		}
	}
}
void Boom::Render()
{
	int ani = BOOM_ANI_DIE;
	if (state == BOOM_STATE_ALIVE || state == BOOM_STATE_FIRE)
	{
		ani = BOOM_ANI_ALIVE;
	}
	int alpha = 255;
	if (isShoot != 0)
		alpha = 150;
	animation_set->at(ani)->Render(x, y, alpha);
}
void Boom::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case BOOM_STATE_ALIVE:
		break;
	case BOOM_STATE_DIE:
		x = -100;
		y = -100;
		break;
	}
}
