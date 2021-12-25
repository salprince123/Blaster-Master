#include "Bullet.h"
#include "PlayScence.h"
Bullet::Bullet(int id)
{
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	this->id = id;
	this->SetState(BULLET_STATE_NOT_FIRE);
	this->type = BULLET_TYPE_2;
	if (player != NULL)
	{
		y0 = player->y;
		x0 = player->x;
	}
}

void Bullet::Render()
{
	int ani = 0;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (player->GetLevel() == PRINCE_LEVEL)
	{
		switch (state)
		{
		case BULLET_STATE_NOT_FIRE:
			ani = BULLET_ANI_NOT_FIRE;
			break;
		case BULLET_STATE_FIRE_LEFT:
			ani = BULLET_ANI_TYPE_2_LEFT;
			break;
		case BULLET_STATE_FIRE_RIGHT:
			ani = BULLET_ANI_TYPE_2_RIGHT;
			break;
		case BULLET_STATE_DIE:
			ani = BULLET_ANI_DIE;
			break;
		default:
			if (vy < 0) ani = BULLET_ANI_TYPE_2_DOWN;
			else if (vy > 0) ani = BULLET_ANI_TYPE_2_UP;
			break;
		}
	}
	else
	{
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
			ani = BULLET_ANI_NOT_FIRE;
			break;
		default:
			break;
		}
	}
	
	animation_set->at(ani)->Render(x, y);
}

void Bullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	/*if (type == 0)
	{
		r = x + BULLET_BBOX_WIDTH_HORIZONTAL;
		b = y + BULLET_BBOX_HEIGHT_HORIZONTAL;
	}
	else i
	else
	{
		r = x + BULLET_BBOX_WIDTH_HORIZONTAL;
		b = y + BULLET_BBOX_HEIGHT_HORIZONTAL;
	}*/
	r = x + BULLET_BBOX_WIDTH_HORIZONTAL;
	b = y + BULLET_BBOX_WIDTH_HORIZONTAL;
	
}
LPGAMEOBJECT Bullet::CreateBullet(float x, float y, int direction, float vx, float vy)
{
	//DebugOut(L"state %d\n", state);
	Bullet* up = new Bullet(id);
	up->SetPosition(x, y);
	up->SetAnimationSet(animation_set);
	up->isCreate = direction;
	up->SetState(state);
	up->vx = vx;
	up->vy = vy;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
	return up;
}
void Bullet::EnemyHandleStateFire(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//update bullet for enemy here 
	if (type == OBJECT_TYPE_BALLCARRY)
	{
		BallCarry* ball = dynamic_cast<BallCarry*>(enemyHandle);

		switch (ball->state)
		{
		case BALLCARRY_STATE_UNACTIVE:
		{
			vx = vy = 0;
			x = ball->x + BALLCARRY_BBOX_WIDTH / 4;
			y = ball->y;
			break;
		}
		case BALLCARRY_STATE_FIRE:
		{
			if (state != BULLET_STATE_FIRE_RIGHT)
				SetState(BULLET_STATE_FIRE_RIGHT);

			if ((y - ball->y) > 10)
			{
			}
			else
			{
				ballCarryTime = GetTickCount64();
				vy += -0.001;
			}
			if (y < ball->y - BALLCARRY_BBOX_HEIGHT + 8)
			{
				y = ball->y - BALLCARRY_BBOX_HEIGHT + 8;
				vy = 0;
			}
			dx = ball->nx * 0.1 * id;
			break;
		}
		}
		if (ballCarryTime != 0)
		{
			if ((GetTickCount64() - ballCarryTime) > 1500)
			{
				SetState(BULLET_STATE_DIE);
				ballCarryTime = 0;
			}
		}
	}
}
void Bullet::PlayerHandleStateFire(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Frog* frog = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (frog->GetLevel() == 1)
		this->type = BULLET_TYPE_1;
	if (state == BULLET_STATE_NOT_FIRE)
	{
		if (frog->GetState() == FROG_STATE_FIRE && frog->GetMaxBullet() == this->id)
		{
			SetState(frog->nx * BULLET_STATE_FIRE_RIGHT);
			this->vx = frog->nx * BULLET_VX;
			this->vy = 0;
			if (type == BULLET_TYPE_2)
			{
				if (left == 0 && isCreate == 0)
				{
					CreateBullet(x, y, 1, vx, vy);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					CreateBullet(x, y, -1, vx, vy);
					right = 1;
				}
			}
		}
		else if (frog->GetState() == FROG_STATE_FIRE_UP && frog->GetMaxBullet() == this->id)
		{

			SetState(BULLET_STATE_FIRE_UP);
			this->vy = BULLET_VY;
			this->vx = 0;
			if (type == BULLET_TYPE_2)
			{
				if (left == 0 && isCreate == 0)
				{
					CreateBullet(x, y, 1, vx, vy);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					CreateBullet(x, y, -1, vx, vy);
					right = 1;
				}
			}
		}
		else if (frog->GetState() == PRINCE_STATE_FIRE_UP && frog->GetMaxBullet() == this->id)
		{

			SetState(BULLET_STATE_FIRE_UP);
			this->vy = BULLET_VY;
			this->vx = 0;
			if (type == BULLET_TYPE_2)
			{
				if (left == 0 && isCreate == 0)
				{
					CreateBullet(x, y, 1, vx, vy);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					CreateBullet(x, y, -1, vx, vy);
					right = 1;
				}
			}
		}
		else if (frog->GetState() == PRINCE_STATE_FIRE_DOWN && frog->GetMaxBullet() == this->id)
		{
			SetState(BULLET_STATE_FIRE_UP);
			this->vy = -BULLET_VY;
			this->vx = 0;
			if (type == BULLET_TYPE_2)
			{
				if (left == 0 && isCreate == 0)
				{
					CreateBullet(x, y, 1, vx, vy);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					CreateBullet(x, y, -1, vx, vy);
					right = 1;
				}
			}
		}
		else if (frog->GetState() == PRINCE_STATE_FIRE_LEFT && frog->GetMaxBullet() == this->id)
		{
			SetState(BULLET_STATE_FIRE_LEFT);
			this->vx = -BULLET_VX;
			this->vy = 0;
			if (type == BULLET_TYPE_2)
			{
				if (left == 0 && isCreate == 0)
				{
					CreateBullet(x, y, 1, vx, vy);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					CreateBullet(x, y, -1, vx, vy);
					right = 1;
				}
			}

		}
		else if (frog->GetState() == PRINCE_STATE_FIRE_RIGHT && frog->GetMaxBullet() == this->id)
		{
			SetState(BULLET_STATE_FIRE_RIGHT);
			this->vx = BULLET_VX;
			this->vy = 0;
			if (type == BULLET_TYPE_2)
			{
				if (left == 0 && isCreate == 0)
				{
					CreateBullet(x, y, 1, vx, vy);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					CreateBullet(x, y, -1, vx, vy);
					right = 1;
				}
			}
		}

	}


	switch (state)
	{
	case BULLET_STATE_DIE:
		if (GetTickCount64() - lastTime > 100)
		{
			SetState(BULLET_STATE_NOT_FIRE);
			lastTime = 0;
		}
		else return;
		break;
	case BULLET_STATE_FIRE_LEFT:case BULLET_STATE_FIRE_RIGHT:
	{
		lastTime = 0;
		if (abs(x - x0) > BULLET_RANGE)
		{
			x0 = x;
			SetState(BULLET_STATE_DIE);
		}
		else
		{

			if (isCreate == 1)
			{
				dy = -50 * sin(count);
				dx = state / BULLET_STATE_FIRE_RIGHT;

			}
			else if (isCreate == -1)
			{
				dy = 50 * sin(count);
				dx = state / BULLET_STATE_FIRE_RIGHT;
			}
			else
				CGameObject::Update(dt, coObjects);
			count += 60;
			break;
		}
	}
	case BULLET_STATE_FIRE_UP:
	{
		lastTime = 0;
		if (abs(y - y0) > BULLET_RANGE)
		{
			y0 = y;
			SetState(BULLET_STATE_DIE);
		}
		else
		{
			if (isCreate == 1)
			{
				dx = -50 * sin(count);
				if (vy < 0)
					dy = -1;
				else if (vy > 0) dy = 1;
				else dy = 0;
			}
			else if (isCreate == -1)
			{
				dx = 50 * sin(count);
				if (vy < 0)
					dy = -1;
				else if (vy > 0) dy = 1;
				else dy = 0;
			}
			else
				CGameObject::Update(dt, coObjects);
			count += 60;
			break;
		}
	}
	case BULLET_STATE_NOT_FIRE:
		lastTime = 0;
		HandleStateUnFire();
		break;
	default:
		break;
	}
}
void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (enemyHandle != NULL)
		EnemyHandleStateFire(dt, coObjects);
	else
		PlayerHandleStateFire(dt, coObjects);	
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
			lastTime = GetTickCount64();
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{				
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
				{
					if (e->ny != 0) 
					y -= 16;
					if(!dynamic_cast<BallCarry*>(enemyHandle))
						SetState(BULLET_STATE_DIE);
				}		
			}
			else if (dynamic_cast<Boom*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
				{
					dynamic_cast<Boom*>(e->obj)->SetState(BOOM_STATE_DIE);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<Worm*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
				{
					dynamic_cast<Worm*>(e->obj)->SetState(WORM_STATE_DIE);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<BreakableBrick*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
				{
					dynamic_cast<BreakableBrick*>(e->obj)->SetState(BREAKABLE_BRICK_STATE_DIE);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<LadyBird*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
				{
					dynamic_cast<LadyBird*>(e->obj)->SetState(LADYBIRD_STATE_COIN);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<EyeLet*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
				{
					dynamic_cast<EyeLet*>(e->obj)->SetState(EYELET_STATE_COIN);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<BallCarry*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE && enemyHandle==NULL)
				{
					dynamic_cast<BallCarry*>(e->obj)->SetState(BALLCARRY_STATE_COIN);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<BallBot*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE && enemyHandle == NULL)
				{
					dynamic_cast<BallBot*>(e->obj)->SetState(BALLBOT_STATE_DIE);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<GX680*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE && enemyHandle == NULL)
				{
					dynamic_cast<GX680*>(e->obj)->SetState(GX680_STATE_DIE);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<Sensor*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE && enemyHandle == NULL)
				{
					dynamic_cast<Sensor*>(e->obj)->SetState(SENSOR_STATE_DIE);
					SetState(BULLET_STATE_DIE);
				}
			}
			else if (dynamic_cast<Bullet*>(e->obj))
			{
				if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE && enemyHandle == NULL)
				{
					if (dynamic_cast<Bullet*>(e->obj)->enemyHandle != NULL)
					{
						dynamic_cast<Bullet*>(e->obj)->SetState(BULLET_STATE_DIE);
						SetState(BULLET_STATE_DIE);
					}						
				}
			}
			else
			{				
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
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	if (player->GetLevel() == FROG_LEVEL)
	{
		switch (bodyUp->GetState())
		{
		case FROG_BODY_UP_STATE_LEFT:
		{
			this->x = bodyUp->x;
			this->y = bodyUp->y;
			break;
		}
		case FROG_BODY_UP_STATE_RIGHT:
		{
			this->x = bodyUp->x;
			this->y = bodyUp->y;
			break;
		}
		case FROG_BODY_UP_STATE_UP_RIGHT:
		{
			this->x = bodyUp->x + 0.5 * FROG_BODY_UP_BBOX_WIDTH;
			this->y = bodyUp->y - FROG_GUN_BBOX_HEIGHT;
			break;
		}
		case FROG_BODY_UP_STATE_UP_LEFT:
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
	else
	{
		switch (player->GetState())
		{			
			case FROG_STATE_IDLE:
			{
				if (player->ny == 0)
				{					
					if (player->nx < 0)
					{						
						this->x = player->x -10;
						this->y = player->y - 8;
					}
					else
					{
						this->x = player->x + PRINCE_BBOX_WIDTH +8 ;
						this->y = player->y - 8;
					}
				}
				else
				{
					if (player->ny < 0)
					{
						this->x = player->x -5;
						this->y = player->y - PRINCE_BBOX_HEIGHT+3;
					}
					else
					{
						this->x = player->x+PRINCE_BBOX_WIDTH/2;
						this->y = player->y +5;
					}
				}
				break;
			}
			default: 
				this->x = player->x - 5;
				this->y = player->y - PRINCE_BBOX_HEIGHT + 3;
				break;
		}
	}	
}
void Bullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_DIE:
	{
		if (enemyHandle != 0)
			x = y = -1000;
		else
		{
			vx = vy = 0;
		}
		break;
	}
	case BULLET_STATE_FIRE_RIGHT:
		if (dynamic_cast<BallCarry*>(enemyHandle))
		{
			vy = 0.01;
			vx = -0.025;
		}			
		break;
	}
}