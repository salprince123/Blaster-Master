#include "LadyBird.h"
LadyBird::LadyBird(int x0, int y0, int x1, int y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vx = LADYBIRD_WALKING_SPEED;
	this->vy = LADYBIRD_FLYING_UP_SPEED;
	//this->vy = 0;
	this->SetState(LADYBIRD_STATE_WALKING_RIGHT);
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
	
	DebugOut(L"[LADYBIRD] %d %d %d %d \n", x0, y0, x1, y1);
	
	/*if (vx < 0 && x < x0) {
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
	switch (state)
	{
		case LADYBIRD_STATE_WALKING_RIGHT:
		{
			/*if (vx > 0 && x > x1)
			{
				this->SetState(LADYBIRD_STATE_WALKING_DOWN);
				x = x1; vx = 0; vy = LADYBIRD_FLYING_UP_SPEED;
			}*/
				
		}
		
		case LADYBIRD_STATE_WALKING_DOWN:
		{
			if (vy > 0 && y > y1)
			{
				this->SetState(LADYBIRD_STATE_WALKING_LEFT);
				y = y1; vy = 0; vx = -LADYBIRD_WALKING_SPEED;
			}
				
		}
		case LADYBIRD_STATE_WALKING_LEFT:
		{
			if (vx < 0 && x < x0)
			{
				this->SetState(LADYBIRD_STATE_WALKING_UP);
				x = x0; vx = 0; vy = -LADYBIRD_FLYING_UP_SPEED;
			}
				
		}
		case LADYBIRD_STATE_WALKING_UP:
		{
			if (vy < 0 && y < y0)
			{
				this->SetState(LADYBIRD_STATE_WALKING_RIGHT);
				y = y0; vy = 0; vx = LADYBIRD_WALKING_SPEED;
			}
				
		}
	}
	Enemy::Update(dt, coObjects);
}
void LadyBird::Render()
{
	int ani = LADYBIRD_ANI_DIE;
	if (state == LADYBIRD_STATE_WALKING_LEFT)
	{
		ani = LADYBIRD_ANI_WALKING_LEFT;
	}
	else if(state == LADYBIRD_STATE_WALKING_RIGHT)
		ani = LADYBIRD_ANI_WALKING_RIGHT;
	int alpha = 255;

	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void LadyBird::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
		case LADYBIRD_STATE_WALKING_LEFT:
			break;
		case LADYBIRD_STATE_WALKING_RIGHT:
			break;
		case LADYBIRD_STATE_WALKING_UP:
			break;
		case LADYBIRD_STATE_WALKING_DOWN:
			break;
		case LADYBIRD_STATE_DIE:
			break;
	}
}
