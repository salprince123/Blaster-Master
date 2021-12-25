#include "Sensor.h"
#include "PlayScence.h"
Sensor::Sensor(int x0, int y0, int x1, int y1, int nx)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vy = 0;
	this->ny = -1;
	this->nx = nx;
	this->vy = 0;
	this->SetState(SENSOR_STATE_ACTIVE);
}
void Sensor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y - 2;
	right = x + SENSOR_BBOX_WIDTH;
	bottom = y + SENSOR_BBOX_HEIGHT;
}
void Sensor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);	

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
	if ((pY-y)*(pY0 - y) <0)
	{
		vx = -SENSOR_WALKING_SPEED;
		if ((pX - x) > 0)
			vx = SENSOR_WALKING_SPEED;
	}
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
		vx = 0;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	pY0 = pY;
}
void Sensor::Render()
{
	int ani = SENSOR_ANI_IDLE;
	int alpha = 255;
	if (vx != 0)
		ani = SENSOR_ANI_WALK;
	animation_set->at(ani)->Render(x, y, alpha);
}
void Sensor::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case SENSOR_STATE_DIE:
		x = -1000;
		y = -1000;
	default:
		break;
	}
}