#pragma once
#include "GameObject.h"

#define FROG_BODY_BBOX_WIDTH  7
#define FROG_BODY_BBOX_HEIGHT 7

#define FROG_BODY_UP_STATE_TOP_RIGHT 100
#define FROG_BODY_UP_STATE_BOT_LEFT 200
#define FROG_BODY_UP_STATE_STACTIC_LEFT 300
#define FROG_BODY_DOWN_STATE_LEFT_RIGHT 400
#define FROG_BODY_DOWN_STATE_TOP_BOT	500
#define FROG_BODY_DOWN_STATE_TOP_LEFT	600
#define FROG_BODY_DOWN_STATE_BOT_RIGHT	700

#define FROG_BODY_UP_ANI_TOP_RIGHT 0
#define FROG_BODY_UP_ANI_BOT_LEFT 1
#define FROG_BODY_UP_ANI_STACTIC_LEFT 2
#define FROG_BODY_DOWN_ANI_LEFT_RIGHT 3
#define FROG_BODY_DOWN_ANI_TOP_BOT	4
#define FROG_BODY_DOWN_ANI_TOP_LEFT	5
#define FROG_BODY_DOWN_ANI_BOT_RIGHT	6

class FrogBody : public CGameObject
{
public:
	FrogBody();
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, float pX, float pY);
};
