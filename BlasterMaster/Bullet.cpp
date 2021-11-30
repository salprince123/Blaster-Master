#include "Bullet.h"
#include "PlayScence.h"
Bullet::Bullet(int id)
{
	this->id = id;
	this->SetState(BULLET_STATE_NOT_FIRE);
}

void Bullet::Render()
{
	int ani = 0;
	switch (state)
	{
		case BULLET_STATE_NOT_FIRE:
			ani = BULLET_ANI_NOT_FIRE;
			break;
		case BULLET_STATE_FIRE_LEFT:
			ani = BULLET_ANI_FIRE_LEFT;
			break;
		case BULLET_STATE_DIE:
			ani = BULLET_ANI_FIRE_DIE;
			break;
		default:
			break;
	}
	animation_set->at(ani)->Render(x, y);
}

void Bullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (type == 0)
	{
		r = x + BULLET_BBOX_WIDTH_HORIZONTAL;
		b = y + BULLET_BBOX_HEIGHT_HORIZONTAL;
	}
	else
	{
		r = x + BULLET_BBOX_WIDTH_HORIZONTAL;
		b = y + BULLET_BBOX_HEIGHT_HORIZONTAL;
	}
}
void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*switch (state)
	{
		case BULLET_STATE_DIE:
			HandleStateDie();
			break;
		case BULLET_STATE_FIRE_LEFT:case BULLET_STATE_FIRE_RIGHT: case BULLET_STATE_FIRE_UP:
			HandleStateFire(dt,coObjects);
			break;
		case BULLET_STATE_NOT_FIRE:
			HandleStateUnFire();
			break;
		default:
			break;
	}*/
	//DebugOut(L"STATE: %d  ID %d\n", this->state, this->id);
}
void Bullet::HandleStateDie()
{
	FrogBody* bodyUp = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetBodyUp();
	switch (bodyUp->GetState())
	{
	case FROG_BODY_UP_STATE_LEFT:
	{
		this->x = bodyUp->x - FROG_GUN_BBOX_WIDTH;
		this->y = bodyUp->y + 0.5 * FROG_BODY_UP_BBOX_HEIGHT;
		break;
	}
	case FROG_BODY_UP_STATE_RIGHT:
	{
		this->x = bodyUp->x + FROG_BODY_UP_BBOX_WIDTH * 0.6 + FROG_GUN_BBOX_WIDTH;
		this->y = bodyUp->y + 0.5 * FROG_BODY_UP_BBOX_HEIGHT;
		break;
	}
	case FROG_BODY_UP_STATE_UP:
	{
		this->x = bodyUp->x + 0.5 * FROG_BODY_UP_BBOX_WIDTH;
		this->y = bodyUp->y - FROG_GUN_BBOX_HEIGHT;
		break;
	}
	case FROG_BODY_UP_STATE_LEFT_UP:
	{
		this->x = bodyUp->x - FROG_GUN_BBOX_WIDTH;
		this->y = bodyUp->y - FROG_GUN_BBOX_HEIGHT;
		break;
	}
	case FROG_BODY_UP_STATE_RIGHT_UP:
	{
		this->x = bodyUp->x + FROG_GUN_BBOX_WIDTH + FROG_BODY_UP_BBOX_WIDTH;
		this->y = bodyUp->y;
		break;
	}
	}
}
void Bullet::HandleStateFire(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Frog* frog = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (frog->GetState() == FROG_STATE_FIRE)
	{
		DebugOut(L"FROG STATE %d  \n", frog->state);
		this->vx = BULLET_VX;
		CGameObject::Update(dt, coObjects);
	}
}
void Bullet::HandleStateUnFire()
{
	FrogBody* bodyUp = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetBodyUp();
	switch (bodyUp->GetState())
	{
		case FROG_BODY_UP_STATE_LEFT:
		{
			this->x = bodyUp->x - FROG_GUN_BBOX_WIDTH;
			this->y = bodyUp->y + 0.5 * FROG_BODY_UP_BBOX_HEIGHT;
			break;
		}
		case FROG_BODY_UP_STATE_RIGHT:
		{
			this->x = bodyUp->x + FROG_BODY_UP_BBOX_WIDTH * 0.6 + FROG_GUN_BBOX_WIDTH;
			this->y = bodyUp->y + 0.5 * FROG_BODY_UP_BBOX_HEIGHT;
			break;
		}
		case FROG_BODY_UP_STATE_UP:
		{
			this->x = bodyUp->x + 0.5 * FROG_BODY_UP_BBOX_WIDTH;
			this->y = bodyUp->y - FROG_GUN_BBOX_HEIGHT;
			break;
		}
		case FROG_BODY_UP_STATE_LEFT_UP:
		{
			this->x = bodyUp->x - FROG_GUN_BBOX_WIDTH;
			this->y = bodyUp->y - FROG_GUN_BBOX_HEIGHT;
			break;
		}
		case FROG_BODY_UP_STATE_RIGHT_UP:
		{
			this->x = bodyUp->x + FROG_GUN_BBOX_WIDTH + FROG_BODY_UP_BBOX_WIDTH;
			this->y = bodyUp->y;
			break;
		}
	}
}