#include "Worm.h"
#include "PlayScence.h"
Worm::Worm(int x0, int y0, int x1, int y1, int nx)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vy = 0;
	this->nx = nx;
	this->ny = -1;
	this->SetState(WORM_STATE_UNACTIVE);
}
void Worm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x+5;
	top = y;
	right = x + WORM_BBOX_WIDTH;
	bottom = y + WORM_BBOX_HEIGHT;
	if (GetState() == WORM_STATE_DIE)
	{
		left = right = top = bottom = 0;
	}
}
void Worm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);
	if (enemyHandle != NULL && enemyHandle->state == BOOM_STATE_FIRE)
	{
		SetState(WORM_STATE_ACTIVE);
	}
	if (enemyHandle != NULL && enemyHandle->state == BOOM_STATE_DIE)
	{
		SetState(WORM_STATE_DIE);
	}
		
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	// turn off collision when die 
	//if (state != SENSOR_STATE_DIE)
	CalcPotentialCollisions(coObjects, coEvents);
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
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Worm::Render()
{
	int ani = WORM_ANI_DIE;
	int alpha = 255;
	if (state == WORM_STATE_ACTIVE)
	{
		if (vx < 0)
			ani = WORM_ANI_WALK_lEFT;
		else if (vx > 0)
			ani = WORM_ANI_WALK_RIGHT;
		else ani = WORM_ANI_WALK_RIGHT;
	}
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void Worm::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case WORM_STATE_DIE:
		x = -1000;
		y = -1000;
	case WORM_STATE_ACTIVE:
		vy = WORM_FLYING_UP_SPEED;
	}
}