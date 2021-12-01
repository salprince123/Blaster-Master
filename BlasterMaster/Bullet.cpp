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
			ani = BULLET_ANI_BIG_LEFT;
			break;
		case BULLET_STATE_FIRE_RIGHT:
			ani = BULLET_ANI_BIG_RIGHT;
			break;
		case BULLET_STATE_DIE:
			ani = BULLET_ANI_DIE;
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
	Frog* frog = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (frog->GetState() == FROG_STATE_FIRE && frog->GetMaxBullet() == this->id)
	{		
		SetState(frog->nx * BULLET_STATE_FIRE_RIGHT);
		this->vx = frog->nx*BULLET_VX;
	}
	switch (state)
	{
		case BULLET_STATE_DIE:
			//DebugOut(L"HERE\n");
			x += 0.1;
			if (abs(x - x0) > 20)
			{
				SetState(BULLET_STATE_NOT_FIRE);
			}
			break;
		case BULLET_STATE_FIRE_LEFT:case BULLET_STATE_FIRE_RIGHT: case BULLET_STATE_FIRE_UP:
		{
			if (abs(x - x0) > BULLET_RANGE)
			{
				x0 = x;
				SetState(BULLET_STATE_DIE);
			}
			else
			{
				CGameObject::Update(dt,coObjects);
				break;
			}				
		}			
		case BULLET_STATE_NOT_FIRE:			
			HandleStateUnFire();
			break;
		default:
			break;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	// turn off collision when die 
	if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
		CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				///DebugOut(L"COLLISS %d\n",id);
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
					SetState(BULLET_STATE_DIE);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Bullet::HandleStateUnFire()
{
	x0 = x;
	y0 = y;
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