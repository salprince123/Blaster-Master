#include "BreakableBrick.h"
#include "Utils.h"
BreakableBrick::BreakableBrick()
{
	SetState(BREAKABLE_BRICK_STATE_ALIVE);
}
void BreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y - 8;
	right = x + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = y + BREAKABLE_BRICK_BBOX_HEIGHT;		
}
void BreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt, coObjects);
}
void BreakableBrick::Render()
{
	int ani = BREAKABLE_BRICK_ANI_DIE;
	if (state == BREAKABLE_BRICK_STATE_ALIVE)
	{
		ani = BREAKABLE_BRICK_ANI_ALIVE;
	}
	int alpha = 255;

	animation_set->at(ani)->Render(x, y, alpha);
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