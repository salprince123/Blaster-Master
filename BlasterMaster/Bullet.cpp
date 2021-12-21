#include "Bullet.h"
#include "PlayScence.h"
Bullet::Bullet(int id)
{
	this->id = id;
	this->SetState(BULLET_STATE_NOT_FIRE);
	this->type = BULLET_TYPE_2;
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
	else if (enemyHandle != NULL)
	{
		r = x + BULLET_BBOX_WIDTH_HORIZONTAL;
		b = y + BULLET_BBOX_WIDTH_HORIZONTAL;
	}
	else
	{
		r = x + BULLET_BBOX_WIDTH_HORIZONTAL;
		b = y + BULLET_BBOX_HEIGHT_HORIZONTAL;
	}*/
	r = x + BULLET_BBOX_WIDTH_HORIZONTAL*2;
	b = y + BULLET_BBOX_WIDTH_HORIZONTAL*2;
}
void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (enemyHandle!=NULL)
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
				SetState(BULLET_STATE_FIRE_RIGHT);
				if (y > ball->y - BALLCARRY_BBOX_HEIGHT+5)
				{
					//vx = ball->nx * BULLET_VX / 10 * id;
					//vy = 0.045 - 0.0035 * dt;
					x += ball->nx*0.051 * id;
					y -= 0.1;
				}				
				else
				{
					ballCarryTime = GetTickCount64();
					vx = vy = 0;
				}

				CGameObject::Update(dt, coObjects);
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
	else
	{		
		Frog* frog = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (state == BULLET_STATE_NOT_FIRE)
		{
			if (frog->GetState() == FROG_STATE_FIRE && frog->GetMaxBullet() == this->id)
			{
				SetState(frog->nx * BULLET_STATE_FIRE_RIGHT);
				this->vx = frog->nx * BULLET_VX;
				this->vy = 0;

			}
			else if (frog->GetState() == FROG_STATE_FIRE_UP && frog->GetMaxBullet() == this->id)
			{
				SetState(BULLET_STATE_FIRE_UP);
				this->vy = BULLET_VY;
				this->vx = 0;
			}
			else if (frog->GetState() == PRINCE_STATE_FIRE_UP && frog->GetMaxBullet() == this->id)
			{
				SetState(BULLET_STATE_FIRE_UP);
				this->vy = BULLET_VY;
				this->vx = 0;
				if (left == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = 1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = -1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					right = 1;
				}
			}
			else if (frog->GetState() == PRINCE_STATE_FIRE_DOWN && frog->GetMaxBullet() == this->id)
			{
				SetState(BULLET_STATE_FIRE_UP);
				this->vy = -BULLET_VY;
				this->vx = 0;
				if (left == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = 1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = -1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					right = 1;
				}
			}
			else if (frog->GetState() == PRINCE_STATE_FIRE_LEFT && frog->GetMaxBullet() == this->id)
			{
				SetState(BULLET_STATE_FIRE_LEFT);
				this->vx = -BULLET_VX;
				this->vy = 0;
				if (left == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x - 5, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = 1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x - 5, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = -1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					right = 1;
				}

			}
			else if (frog->GetState() == PRINCE_STATE_FIRE_RIGHT && frog->GetMaxBullet() == this->id)
			{
				SetState(BULLET_STATE_FIRE_RIGHT);
				this->vx = BULLET_VX;
				this->vy = 0;
				if (left == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x + 5, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = 1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					left = 1;
				}
				if (right == 0 && isCreate == 0)
				{
					Bullet* up = new Bullet(id);
					up->SetPosition(x + 5, y);
					up->SetAnimationSet(animation_set);
					up->isCreate = -1;
					up->SetState(state);
					((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->createObject.push_back(up);
					right = 1;
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
					dy = -20 * sin(dt);
					dx = state/ BULLET_STATE_FIRE_RIGHT;
					
				}
				else if (isCreate == -1)
				{
					dy = 20 * sin(dt);
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
					dx = -20 * sin(dt);
					dy = vy * dt;
				}
				else if (isCreate == -1)
				{
					dx = 20 * sin(dt);
					dy = vy * dt;
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
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	// turn off collision when die 
	if (state != BULLET_STATE_DIE && state != BULLET_STATE_NOT_FIRE)
		CalcPotentialCollisions(coObjects, coEvents);
	//if (type == OBJECT_TYPE_BALLCARRY)
		//DebugOut(L"%d\n", coEvents.size());
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
		//DebugOut(L"PRINCE LEVEL %d %d %d\n", player->GetState(), player->nx, player->ny);
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
	}
}