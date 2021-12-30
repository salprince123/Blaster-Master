#include "Enemy1.h"
#include "Utils.h"
Enemy1::Enemy1()
{
}
void Enemy1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 16;
	right = x + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = top + BREAKABLE_BRICK_BBOX_HEIGHT;
}
void Enemy1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	Enemy::Update(dt, coObjects);
}
void Enemy1::Render()
{
	int ani = 0;
	animation_set->at(ani)->Render(x, y, 255);
}
void Enemy1::SetState(int state)
{
	Enemy1::SetState(state);	
}