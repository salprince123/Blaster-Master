#include "FrogWheel.h"
FrogWheel::FrogWheel()
{
	this->SetState(FROG_WHEEL_STATE_2);
}
void FrogWheel::Render()
{
	int ani = 0;
	switch (state)
	{
	case FROG_WHEEL_STATE_1:
		ani = FROG_WHEEL_ANI_1;
		break;
	case FROG_WHEEL_STATE_2:
		ani = FROG_WHEEL_ANI_2;
		break;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void FrogWheel::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FROG_WHEEL_BBOX_WIDTH;
	b = y + FROG_WHEEL_BBOX_HEIGHT;
}
void FrogWheel::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case FROG_WHEEL_STATE_1:
		break;
	case FROG_WHEEL_STATE_2:
		break;
	}
}
void FrogWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, float pX, float pY)
{
	switch (state)
	{
		case FROG_WHEEL_STATE_1:
		{
			break;
		}
		case FROG_WHEEL_STATE_2:
		{
			break;
		}
	}
	CGameObject::Update(dt, coObjects);
}