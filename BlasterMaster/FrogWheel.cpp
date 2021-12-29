#include "FrogWheel.h"
#include "Utils.h"
#include "PlayScence.h"
FrogWheel::FrogWheel(int type)
{
	this->SetType(type);
	if(type == FROG_WHEEL_TYPE_LEFT)
		this->SetState(FROG_WHEEL_STATE_LEFT);
	else if (type == FROG_WHEEL_TYPE_RIGHT)
		this->SetState(FROG_WHEEL_STATE_UP_RIGHT);
}
void FrogWheel::Render()
{
	Frog* frog = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (frog->GetLevel() == PRINCE_LEVEL)
	{
		animation_set->at(FROG_WHEEL_ANI_HIDE)->Render(x, y);
		return;
	}
	int alpha = 255;
	if (frog->untouchable) alpha = 128;
	int ani = FROG_WHEEL_ANI_UP_RIGHT;
	switch (state)
	{
		case FROG_WHEEL_STATE_UP_RIGHT:
			ani = FROG_WHEEL_ANI_UP_RIGHT;
			break;
		case FROG_WHEEL_STATE_LEFT:
			ani = FROG_WHEEL_ANI_LEFT;
			break;
		case FROG_WHEEL_STATE_UP:
			ani = FROG_WHEEL_ANI_UP;
			break;
		case FROG_WHEEL_STATE_UP_LEFT:
			ani = FROG_WHEEL_ANI_UP_LEFT;
			break;
	}
	//ani = FROG_WHEEL_ANI_UP_LEFT;
	animation_set->at(ani)->Render(x, y, alpha);
}
void FrogWheel::AutoChangeStateWithTime(DWORD time)
{
	DWORD now = GetTickCount64();
	DWORD deltaT = now - lastTime;
	if (deltaT > time)
	{
		lastTime = now;
		switch (state)
		{
		case FROG_WHEEL_STATE_UP_RIGHT:
			SetState(FROG_WHEEL_STATE_LEFT);
			break;
		case FROG_WHEEL_STATE_LEFT:
			SetState(FROG_WHEEL_STATE_UP_LEFT);
			break;
		case FROG_WHEEL_STATE_UP_LEFT:
			SetState(FROG_WHEEL_STATE_UP);
			break;
		case FROG_WHEEL_STATE_UP:
			SetState(FROG_WHEEL_STATE_UP_RIGHT);
			break;
		default:
			break;
		}
	}
}
void FrogWheel::AutoChangeState()
{
	switch (state)
	{
		case FROG_WHEEL_STATE_UP_RIGHT:
			SetState(FROG_WHEEL_STATE_LEFT);
			break;
		case FROG_WHEEL_STATE_LEFT:
			SetState(FROG_WHEEL_STATE_UP_LEFT);
			break;
		case FROG_WHEEL_STATE_UP_LEFT:
			SetState(FROG_WHEEL_STATE_UP);
			break;
		case FROG_WHEEL_STATE_UP:
			SetState(FROG_WHEEL_STATE_UP_RIGHT);
			break;
		default:
			break;
	}
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
}
void FrogWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	FrogBody* bodyDown = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetBodyDown();
	if (this->type == FROG_WHEEL_TYPE_LEFT)
	{		
		this->x = bodyDown->x - FROG_WHEEL_BBOX_WIDTH;
		this->y = bodyDown->y - 0.5 * FROG_BODY_DOWN_BBOX_HEIGHT;
	}
	else if (this->type == FROG_WHEEL_TYPE_RIGHT)
	{
		this->x = bodyDown->x + FROG_BODY_DOWN_BBOX_WIDTH;
		this->y = bodyDown->y - 0.5 * FROG_BODY_DOWN_BBOX_HEIGHT;
	}
	Frog* frog = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//DebugOut(L"PLAYER STATE %d \n", frog->GetState());
	if (frog->GetState() == FROG_STATE_WALKING_LEFT || frog->GetState() == FROG_STATE_WALKING_RIGHT)
	{
		if (lastTime == 0)
		{
			lastTime = GetTickCount64();	
			AutoChangeState();
		}		
		this->AutoChangeStateWithTime(200);
	}
	else this->lastTime = 0;

	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetState() == FROG_STATE_JUMPING_UP)
		this->y -= 2;
	else if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetState() == FROG_STATE_FALLING_DOWN)
		this->y += 3;
	if (frog->GetState() == FROG_STATE_UP_LEFT || frog->GetState() == FROG_STATE_UP_RIGHT)
	{
		y -= 3;
		if (this->type == FROG_WHEEL_TYPE_LEFT)
			x += 2;
		else if (this->type == FROG_WHEEL_TYPE_RIGHT)
			x -= 2;
	}
	CGameObject::Update(dt, coObjects);
}