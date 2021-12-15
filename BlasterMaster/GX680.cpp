#include "GX680.h"
#include "PlayScence.h"
GX680::GX680(int x0, int y0, int x1, int y1, int nx)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
	this->vy = 0;
	this->nx = nx;
	this->ny = -1;
	this->SetState(GX680_STATE_ACTIVE);
}
void GX680::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y - 2;
	right = x + GX680_BBOX_WIDTH;
	bottom = y + GX680_BBOX_HEIGHT;
	if (GetState() == GX680_STATE_DIE)
	{
		left = right = top = bottom = 0;
	}
}
void GX680::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float pX, pY;
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	player->GetPosition(pX, pY);
	
	if ( (abs(x - pX) < GX680_RANGE || abs(y - pY) < GX680_RANGE)&& state == GX680_STATE_UNACTIVE)
	{
		SetState(GX680_STATE_ACTIVE);
	}
	
	if (state == GX680_STATE_ACTIVE)
	{		
		if (abs(x - pX) > GX680_RANGE || abs(y - pY) > GX680_RANGE)
		{
			SetState(GX680_STATE_UNACTIVE);
			x = x0;
			y = y0;
			//DebugOut(L"UNACTIVE\n");
		}
		if ((pX - x) > 0) x+=0.2;
		else if ((pX - x) < 0) x-=0.2;
		if ((pY - y) > 0) y+=0.2;
		else if ((pY - y) < 0) y-=0.2;

	}
}
void GX680::Render()
{
	int ani = GX680_ANI_DIE;
	int alpha = 255;
	if (state == GX680_STATE_ACTIVE)
	{
		if (vx < 0)
			ani = GX680_ANI_WALK_lEFT;
		else if (vx > 0)
			ani = GX680_ANI_WALK_RIGHT;
		else ani = GX680_ANI_WALK_RIGHT;
	}
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox();
}
void GX680::SetState(int state)
{
	Enemy::SetState(state);
	switch (state)
	{
	case GX680_STATE_DIE:
		x = -1000;
		y = -1000;
	}
}