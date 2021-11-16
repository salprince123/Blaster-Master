#include "FrogGun.h"
#include "Utils.h"
FrogGun::FrogGun()
{
	this->SetState(FROG_GUN_STATE_TOP_BOT);
}
void FrogGun::Render()
{
	int ani = 0;
	switch (state)
	{
		case FROG_GUN_STATE_BOT_LEFT:
			ani = FROG_GUN_ANI_BOT_LEFT;
			break;
		case FROG_GUN_STATE_LEFT_RIGHT:
			ani = FROG_GUN_ANI_LEFT_RIGHT;
			break;
		case FROG_GUN_STATE_TOP_LEFT:
			ani = FROG_GUN_ANI_TOP_LEFT;
			break;
		case FROG_GUN_STATE_TOP_BOT:
			ani = FROG_GUN_ANI_TOP_BOT;
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
	switch (this->state)
	{
		case FROG_GUN_STATE_BOT_LEFT:
			break;
		case FROG_GUN_STATE_LEFT_RIGHT:
			break;
		case FROG_GUN_STATE_TOP_LEFT:
			break;
		case FROG_GUN_STATE_TOP_BOT:
			break;
	}
}
void FrogGun::UpdateWithPlayer(DWORD dt, vector<LPGAMEOBJECT>* coObjects, float pX, float pY)
{	
	switch (state)
	{
	case FROG_GUN_STATE_BOT_LEFT:
	{
		break;
	}
	case FROG_GUN_STATE_LEFT_RIGHT:
	{
		break;
	}
	case FROG_GUN_STATE_TOP_LEFT:
	{
		break;
	}
	case FROG_GUN_STATE_TOP_BOT:
	{
		break;
	}
	}
	this->x = pX;
	this->y = pY;
	DebugOut(L"GUN GOU %f %f\n", pX, pY);
	CGameObject::Update(dt, coObjects);
}
void FrogGun::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOut(L"STATE %d\n", state);
	switch (state)
	{
	case FROG_GUN_STATE_BOT_LEFT:
	{
		break;
	}
	case FROG_GUN_STATE_LEFT_RIGHT:
	{
		break;
	}
	case FROG_GUN_STATE_TOP_LEFT:
	{
		break;
	}
	case FROG_GUN_STATE_TOP_BOT:
	{
		break;
	}
	}
	this->x += 1;
	CGameObject::Update(dt, coObjects);
}