#pragma once
#include "GameObject.h"

#define FROG_WHEEL_BBOX_WIDTH  7
#define FROG_WHEEL_BBOX_HEIGHT 7

#define FROG_WHEEL_TYPE_LEFT	10
#define FROG_WHEEL_TYPE_RIGHT	20

#define FROG_WHEEL_STATE_UP_RIGHT 100
#define FROG_WHEEL_STATE_LEFT  200
#define FROG_WHEEL_STATE_RIGHT  500
#define FROG_WHEEL_STATE_UP_LEFT  300
#define FROG_WHEEL_STATE_UP  400

#define FROG_WHEEL_ANI_UP_RIGHT 0
#define FROG_WHEEL_ANI_LEFT  1
#define FROG_WHEEL_ANI_UP_LEFT  2
#define FROG_WHEEL_ANI_UP  3

class FrogWheel : public CGameObject
{
	int type;
	DWORD lastTime ;
public:
	FrogWheel(int type);
	virtual void Render();
	void SetState(int state);
	void SetType(int type);
	void AutoChangeState();
	void AutoChangeStateWithTime(DWORD time);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

