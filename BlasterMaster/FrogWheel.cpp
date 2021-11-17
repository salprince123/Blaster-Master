#include "FrogWheel.h"
#include "Utils.h"
#include "PlayScence.h"
FrogWheel::FrogWheel()
{
	if(this->type== FROG_WHEEL_TYPE_LEFT)
		this->SetState(FROG_WHEEL_STATE_1);
	else if (this->type == FROG_WHEEL_TYPE_RIGHT)
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
	}
	animation_set->at(ani)->Render(x, y);
}
void FrogWheel::SetType(int type)
{
	this->type = type;
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
void FrogWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"[STATE WHEEL] %d\n", type);
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
	FrogBody* bodyDown = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetBodyDown();
	if (this->type == FROG_WHEEL_TYPE_LEFT)
	{		
		this->x = bodyDown->x - FROG_WHEEL_BBOX_WIDTH;
		this->y = bodyDown->y + 0.5 * FROG_BODY_DOWN_BBOX_HEIGHT;
	}
	else if (this->type == FROG_WHEEL_TYPE_RIGHT)
	{
		this->x = bodyDown->x + FROG_BODY_DOWN_BBOX_WIDTH;
		this->y = bodyDown->y + 0.5 * FROG_BODY_DOWN_BBOX_HEIGHT;
	}
	/*if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetState() == FROG_STATE_JUMP)
		this->y += 50;*/
	CGameObject::Update(dt, coObjects);
}