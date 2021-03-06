#include "FrogBody.h"
#include "PlayScence.h"
FrogBody::FrogBody()
{
	if(this->type == FROG_BODY_TYPE_UP)
		this->SetState(FROG_BODY_UP_STATE_RIGHT);
	else this->SetState(FROG_BODY_DOWN_STATE_LEFT_RIGHT);
}
void FrogBody::Render()
{
	Frog* frog = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (frog->GetLevel() == PRINCE_LEVEL)
	{
		animation_set->at(FROG_BODY_DOWN_ANI_HIDE)->Render(x, y);
		return;
	}
	int alpha = 255;
	if (frog->untouchable) alpha = 128;
	int ani = 0;
	switch (state)
	{
		case FROG_BODY_UP_STATE_LEFT_UP:
			ani = FROG_BODY_UP_ANI_LEFT_UP;
			break;
		case FROG_BODY_UP_STATE_RIGHT_UP:
			ani = FROG_BODY_UP_ANI_RIGHT_UP;
			break;
		case FROG_BODY_UP_STATE_LEFT:
			ani = FROG_BODY_UP_ANI_LEFT;
			break;
		case FROG_BODY_UP_STATE_RIGHT:
			ani = FROG_BODY_UP_ANI_RIGHT;
			break;
		case FROG_BODY_UP_STATE_UP_RIGHT:
			break;
		case FROG_BODY_UP_STATE_UP_LEFT:
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
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}

void FrogBody::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FROG_BODY_UP_BBOX_WIDTH;
	b = y + FROG_BODY_UP_BBOX_HEIGHT;
}
void FrogBody::SetType(int type)
{
	this->type = type;
}
void FrogBody::SetState(int state)
{
	CGameObject::SetState(state);

	/*switch (state)
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
	}*/
}
void FrogBody::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Frog* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetLevel() == LITTLE_PRINCE_LEVEL)
		return;
	if (type == FROG_BODY_TYPE_UP)
	{
		switch (mario->GetState())
		{
			case FROG_STATE_WALKING_LEFT:
			{				
				this->SetState(FROG_BODY_UP_STATE_LEFT);
				if (this->type == FROG_BODY_TYPE_DOWN)
					this->SetState(FROG_BODY_DOWN_STATE_LEFT_RIGHT);
				this->x = mario->x+FROG_GUN_BBOX_WIDTH - 0.5 * FROG_WHEEL_BBOX_WIDTH;
				break;
			}
			case FROG_STATE_WALKING_RIGHT:
			{
				this->SetState(FROG_BODY_UP_STATE_RIGHT);
				if (this->type == FROG_BODY_TYPE_DOWN)
					this->SetState(FROG_BODY_DOWN_STATE_LEFT_RIGHT);
				this->x = mario->x+0.5* FROG_WHEEL_BBOX_WIDTH;
				break;
			}	
			case FROG_STATE_UP_RIGHT:
			{
				this->SetState(FROG_BODY_UP_STATE_UP_RIGHT);
				if (this->type == FROG_BODY_TYPE_DOWN)
					this->SetState(FROG_BODY_DOWN_STATE_UP_RIGHT);
				this->x = mario->x + 0.5 * FROG_WHEEL_BBOX_WIDTH;
				break;
			}
			case FROG_STATE_UP_LEFT:
			{
				this->SetState(FROG_BODY_UP_STATE_UP_LEFT);
				if (this->type == FROG_BODY_TYPE_DOWN)
					this->SetState(FROG_BODY_DOWN_STATE_UP_LEFT);
				this->x = mario->x + 0.5 * FROG_WHEEL_BBOX_WIDTH;
				break;
			}
			case FROG_STATE_IDLE:
			{
				if (mario->nx < 0)
				{
					this->SetState(FROG_BODY_UP_STATE_LEFT);
					if (this->type == FROG_BODY_TYPE_DOWN)
						this->SetState(FROG_BODY_DOWN_STATE_LEFT_RIGHT);
					this->x = mario->x + FROG_GUN_BBOX_WIDTH - 0.5 * FROG_WHEEL_BBOX_WIDTH;
				}
				else
				{
					this->SetState(FROG_BODY_UP_STATE_RIGHT);
					if (this->type == FROG_BODY_TYPE_DOWN)
						this->SetState(FROG_BODY_DOWN_STATE_LEFT_RIGHT);
					this->x = mario->x + 0.5 * FROG_WHEEL_BBOX_WIDTH;
				}
				break;
			}
		}
		this->y = mario->y ;
		if (mario->GetState() == FROG_STATE_UP_LEFT || mario->GetState() == FROG_STATE_UP_RIGHT)
		{
			y += 3;
		}
	}
	else if (type == FROG_BODY_TYPE_DOWN)
	{
		FrogBody* bodyUp = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetBodyUp();
		this->x = bodyUp->x + 0.5 * FROG_BODY_UP_BBOX_WIDTH - 0.5 * FROG_BODY_DOWN_BBOX_WIDTH;
		this->y = bodyUp->y - FROG_BODY_DOWN_BBOX_HEIGHT;
	}
	
	
	CGameObject::Update(dt, coObjects);
}