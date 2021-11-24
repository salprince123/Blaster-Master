#include "LadyBird.h"
#include "PlayScence.h"
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
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);
	if (abs(x - pX) > 150) return;
	/*if (y - pY > 40)
	{
		Enemy::Update(dt, coObjects);
		x = -100, y = -100;
		return;
	}*/
	switch (state)
	{
		case LADYBIRD_STATE_WALKING_RIGHT:
		{
			if (y0 != y1)//di theo parapol
			{

			}
			else
			{
				vy = 0;
				if (vx > 0 && x > x1)
				{
					this->SetState(LADYBIRD_STATE_WALKING_LEFT);
					x = x1; vx = -LADYBIRD_WALKING_SPEED;
				}
			}
			
		}

		/*case LADYBIRD_STATE_WALKING_DOWN:
		{
			if (vy > 0 && y > y1)
			{
				this->SetState(LADYBIRD_STATE_WALKING_LEFT);
				y = y1; vy = 0; vx = -LADYBIRD_WALKING_SPEED;
			}

		}*/
		case LADYBIRD_STATE_WALKING_LEFT:
		{
			if (y0 != y1)//di theo parapol
			{

			}
			else
			{
				vy = 0;
				if (vx < 0 && x < x0 && y0 == y1)
				{
					this->SetState(LADYBIRD_STATE_WALKING_RIGHT);
					x = x0; vx = LADYBIRD_WALKING_SPEED; vy = 0;
				}
			}
			

		}
		/*case LADYBIRD_STATE_WALKING_UP:
		{
			if (vy < 0 && y < y0)
			{
				this->SetState(LADYBIRD_STATE_WALKING_RIGHT);
				y = y0; vy = 0; vx = LADYBIRD_WALKING_SPEED;
			}

		}*/
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
	else if (state == LADYBIRD_STATE_WALKING_RIGHT)
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