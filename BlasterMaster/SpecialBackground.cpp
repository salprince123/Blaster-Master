#include "SpecialBackground.h"
#include "PlayScence.h"
SpecialBackground::SpecialBackground(int x0, int y0, int x1, int y1, int nx)
{	
	this->vy = 0;
	this->ny = -1;
	this->nx = nx;
	this->vy = 0;
	this->SetState(SENSOR_STATE_ACTIVE);
}
void SpecialBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SENSOR_BBOX_WIDTH;
	bottom = y + SENSOR_BBOX_HEIGHT;
}
void SpecialBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);

}
void SpecialBackground::Render()
{
	int ani = SENSOR_ANI_IDLE;
	int alpha = 255;
	if (vx != 0)
		ani = SENSOR_ANI_WALK;
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void SpecialBackground::SetState(int state)
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