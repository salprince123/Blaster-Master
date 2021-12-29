#include "BreakableBrick.h"
#include "Utils.h"
BreakableBrick::BreakableBrick()
{
	SetState(BREAKABLE_BRICK_STATE_ALIVE);
}
void BreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y+16;
	right = x + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = top + BREAKABLE_BRICK_BBOX_HEIGHT;		
}
void BreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	Enemy::Update(dt, coObjects);
}
void BreakableBrick::Render()
{
	int ani = BREAKABLE_BRICK_ANI_DIE;
	if (state == BREAKABLE_BRICK_STATE_ALIVE)
	{
		ani = BREAKABLE_BRICK_ANI_ALIVE;
	}
	int alpha = 255;
	if (isShoot != 0)
		alpha = 150;
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void BreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAKABLE_BRICK_STATE_ALIVE:
		break;
	case BREAKABLE_BRICK_STATE_DIE:
		x = -100;
		y = -100;
		break;
	}
}