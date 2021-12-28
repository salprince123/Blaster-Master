#include "SpecialBackground.h"
#include "PlayScence.h"
SpecialBackground::SpecialBackground(int x0, int y0, int x1, int y1, int nx)
{	
	this->vy = 0;
	this->ny = -1;
	this->nx = nx;
	this->vy = 0;
	this->SetState(SPECIAL_BACKGROUND_STATE_ACTIVE);
}
void SpecialBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left =top=right=bottom= 0;
}
void SpecialBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);
	if(pY <= 860 && pY >= 737 && pX >= 368 && pX <= 400)
		t_active = GetTickCount64();
	if (t_active != 0)
		if (GetTickCount64() - t_active > 3000)
			SetState(SPECIAL_BACKGROUND_STATE_DIE);
}
void SpecialBackground::Render()
{	
	animation_set->at(0)->Render(x, y, 255);
	//RenderBoundingBox();
}
void SpecialBackground::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case SPECIAL_BACKGROUND_STATE_DIE:
		x = -1000;
		y = -1000;
	default:
		break;
	}
}