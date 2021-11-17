#pragma once
#include "GameObject.h"

#define FROG_WHEEL_BBOX_WIDTH  7
#define FROG_WHEEL_BBOX_HEIGHT 7

#define FROG_WHEEL_TYPE_LEFT	10
#define FROG_WHEEL_TYPE_RIGHT	20

#define FROG_WHEEL_STATE_1 100
#define FROG_WHEEL_STATE_2 200

#define FROG_WHEEL_ANI_1 0
#define FROG_WHEEL_ANI_2 1

class FrogWheel : public CGameObject
{
	int type;
public:
	FrogWheel();
	virtual void Render();
	void SetState(int state);
	void SetType(int type);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

