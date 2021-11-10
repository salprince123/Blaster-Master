#include "LadyBird.h"
#include "Utils.h"
LadyBird::LadyBird(int x0, int y0, int x1, int y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vx = LADYBIRD_WALKING_SPEED;
	this->vy = LADYBIRD_FLYING_UP_SPEED;
	this->SetState(LADYBIRD_STATE_WALKING);
}
void LadyBird::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + LADYBIRD_BBOX_WIDTH;

	if (state == LADYBIRD_STATE_DIE)
		bottom = y + LADYBIRD_BBOX_HEIGHT_DIE;
	else
		bottom = y + LADYBIRD_BBOX_HEIGHT;
}
void LadyBird::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	Enemy::Update(dt,coObjects);
	//DebugOut(L"[LADYBIRD] %d %d %d %d \n", x0, y0, x1, y1);
	x += dx;
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
	}
}
void LadyBird::Render()
{
	int ani = LADYBIRD_ANI_DIE;
	if (state == LADYBIRD_STATE_WALKING)
	{
		if(vx>0) 
			ani = LADYBIRD_ANI_WALKING_RIGHT;
		else ani = LADYBIRD_ANI_WALKING_LEFT;
	}
	int alpha = 255;

	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void LadyBird::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
		case LADYBIRD_STATE_WALKING:
			break;
		case LADYBIRD_STATE_DIE:
			break;
	}
}
