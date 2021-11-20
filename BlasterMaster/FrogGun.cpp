#include "FrogGun.h"
#include "PlayScence.h"
FrogGun::FrogGun()
{
	this->SetState(FROG_GUN_STATE_RIGHT);
}
void FrogGun::Render()
{
	int ani = 0;
	switch (state)
	{
	case FROG_GUN_STATE_LEFT:
		ani = FROG_GUN_ANI_LEFT;
		break;
	case FROG_GUN_STATE_RIGHT:
		ani = FROG_GUN_ANI_RIGHT;
		break;
	case FROG_GUN_STATE_UP:
		ani = FROG_GUN_ANI_UP;
		break;
	case FROG_GUN_STATE_LEFT_UP:
		ani = FROG_GUN_ANI_LEFT_UP;
		break;
	case FROG_GUN_STATE_RIGHT_UP:
		ani = FROG_GUN_ANI_RIGHT_UP;
		break;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void FrogGun::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FROG_GUN_BBOX_WIDTH;
	b = y + FROG_GUN_BBOX_HEIGHT;
}
void FrogGun::SetState(int state)
{
	this->state = state;
	/*switch (this->state)
	{
		case FROG_GUN_STATE_BOT_LEFT:
			break;
		case FROG_GUN_STATE_LEFT_RIGHT:
			break;
		case FROG_GUN_STATE_TOP_LEFT:
			break;
		case FROG_GUN_STATE_TOP_BOT:
			break;
	}*/
}

void FrogGun::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	FrogBody* bodyUp = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetBodyUp();
	switch (bodyUp->GetState())
	{
		case FROG_BODY_UP_STATE_LEFT:
		{
			this->x = bodyUp->x - FROG_GUN_BBOX_WIDTH;
			this->y = bodyUp->y + 0.5 * FROG_BODY_UP_BBOX_HEIGHT;
			this->SetState(FROG_GUN_STATE_LEFT);
			break;
		}
		case FROG_BODY_UP_STATE_RIGHT:
		{
			this->x = bodyUp->x - FROG_GUN_BBOX_WIDTH;
			this->y = bodyUp->y;
			break;
		}
		case FROG_BODY_UP_STATE_UP:
		{
			this->y = bodyUp->y + 0.5 * FROG_BODY_UP_BBOX_HEIGHT;
			this->SetState(FROG_GUN_STATE_LEFT);
			break;
		}
		case FROG_BODY_UP_STATE_LEFT_UP:
		{
			this->x = bodyUp->x - FROG_GUN_BBOX_WIDTH;			
			this->y = bodyUp->y + 0.5 * FROG_BODY_UP_BBOX_HEIGHT;
			this->SetState(FROG_GUN_STATE_LEFT);
			break;
		}
		case FROG_BODY_UP_STATE_RIGHT_UP:
		{
			this->x = bodyUp->x;
			this->y = bodyUp->y;
			this->SetState(FROG_GUN_STATE_RIGHT_UP);
			break;
		}
	}
}