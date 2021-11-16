#include "FrogBody.h"
FrogBody::FrogBody()
{
	this->SetState(FROG_BODY_DOWN_STATE_LEFT_RIGHT);
}
void FrogBody::Render()
{
	int ani = 0;
	switch (state)
	{
		case FROG_BODY_UP_STATE_TOP_RIGHT:
			ani = FROG_BODY_UP_ANI_TOP_RIGHT;
			break;
		case FROG_BODY_UP_STATE_BOT_LEFT:
			ani = FROG_BODY_UP_ANI_BOT_LEFT;
			break;
		case FROG_BODY_UP_STATE_STACTIC_LEFT:
			ani = FROG_BODY_UP_ANI_STACTIC_LEFT;
			break;
		case FROG_BODY_DOWN_STATE_LEFT_RIGHT:
			ani = FROG_BODY_DOWN_ANI_LEFT_RIGHT;
			break;
		case FROG_BODY_DOWN_STATE_TOP_BOT:
			ani = FROG_BODY_DOWN_ANI_TOP_BOT;
			break;
		case FROG_BODY_DOWN_STATE_TOP_LEFT:
			ani = FROG_BODY_DOWN_ANI_TOP_LEFT;
			break;
		case FROG_BODY_DOWN_STATE_BOT_RIGHT:
			ani = FROG_BODY_DOWN_ANI_BOT_RIGHT;
			break;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void FrogBody::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FROG_BODY_BBOX_WIDTH;
	b = y + FROG_BODY_BBOX_HEIGHT;
}
void FrogBody::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
		case FROG_BODY_UP_STATE_TOP_RIGHT:
			break;
		case FROG_BODY_UP_STATE_BOT_LEFT:
			break;
		case FROG_BODY_UP_STATE_STACTIC_LEFT:
			break;
		case FROG_BODY_DOWN_STATE_LEFT_RIGHT:
			break;
		case FROG_BODY_DOWN_STATE_TOP_BOT:
			break;
		case FROG_BODY_DOWN_STATE_TOP_LEFT:
			break;
		case FROG_BODY_DOWN_STATE_BOT_RIGHT:
			break;
	}
}
void FrogBody::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, float pX, float pY)
{
	switch (state)
	{
		case FROG_BODY_UP_STATE_TOP_RIGHT:
		{
			break;
		}

		case FROG_BODY_UP_STATE_BOT_LEFT:
		{
			break;
		}
		case FROG_BODY_UP_STATE_STACTIC_LEFT:
		{
			break;
		}
		case FROG_BODY_DOWN_STATE_LEFT_RIGHT:
		{
			break;
		}
		case FROG_BODY_DOWN_STATE_TOP_BOT:
		{
			break;
		}
		case FROG_BODY_DOWN_STATE_TOP_LEFT:
		{
			break;
		}
		case FROG_BODY_DOWN_STATE_BOT_RIGHT:
		{
			break;
		}
	}
	CGameObject::Update(dt, coObjects);
}