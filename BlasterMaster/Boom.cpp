#include "Boom.h"
#include "Utils.h"
Boom::Boom()
{
	SetState(BOOM_STATE_ALIVE);
}
void Boom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOOM_BBOX_WIDTH;

	if (state == BOOM_STATE_DIE)
		bottom = y + BOOM_BBOX_HEIGHT_DIE;
	else
		bottom = y + BOOM_BBOX_HEIGHT;
}
void Boom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	Enemy::Update(dt, coObjects);
	//DebugOut(L"[LADYBIRD] %d %d %d %d \n", x0, y0, x1, y1);
	/*x += dx;
	y += dy;
	if (vx < 0 && x < x0) {
		x = x0; vx = -vx;
	}
	if (vx > 0 && x > x1) {
		x = x1; vx = -vx;
	}
	if (vy < 0 && y < y0) {
		y = y0; vy = -vy;
	}
	if (vy > 0 && y > y1) {
		y = y1; vy = -vy;
	}*/
}
void Boom::Render()
{
	int ani = BOOM_ANI_DIE;
	if (state == BOOM_STATE_ALIVE)
	{
		ani = BOOM_ANI_ALIVE;
	}
	int alpha = 255;

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
		break;
	}
}
