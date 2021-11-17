#pragma once
#include "GameObject.h"

#define FROG_BODY_UP_BBOX_WIDTH  16
#define FROG_BODY_UP_BBOX_HEIGHT 8
#define FROG_BODY_DOWN_BBOX_WIDTH  7
#define FROG_BODY_DOWN_BBOX_HEIGHT 7

#define FROG_BODY_TYPE_UP	1
#define FROG_BODY_TYPE_DOWN	2

#define FROG_BODY_UP_STATE_LEFT_UP 100
#define FROG_BODY_UP_STATE_RIGHT_UP 200
#define FROG_BODY_UP_STATE_LEFT 300
#define FROG_BODY_UP_STATE_RIGHT 400
#define FROG_BODY_UP_STATE_UP 4001

#define FROG_BODY_DOWN_STATE_LEFT_RIGHT 500
#define FROG_BODY_DOWN_STATE_TOP_BOT	600
#define FROG_BODY_DOWN_STATE_TOP_LEFT	700
#define FROG_BODY_DOWN_STATE_BOT_RIGHT	800

#define FROG_BODY_UP_ANI_LEFT_UP 0
#define FROG_BODY_UP_ANI_RIGHT_UP 1
#define FROG_BODY_UP_ANI_UP 1
#define FROG_BODY_UP_ANI_LEFT 2
#define FROG_BODY_UP_ANI_RIGHT 3

#define FROG_BODY_DOWN_ANI_LEFT_RIGHT 4
#define FROG_BODY_DOWN_ANI_TOP_BOT	5
#define FROG_BODY_DOWN_ANI_TOP_LEFT	6
#define FROG_BODY_DOWN_ANI_BOT_RIGHT	7

#define DISTANCE_FROM_FROG_TOP_RIGHT_X_UP	10
#define DISTANCE_FROM_FROG_BOT_LEFT_X_UP	10
#define DISTANCE_FROM_FROG_STATIC_LEFT_X_UP 10
#define DISTANCE_FROM_FROG_TOP_RIGHT_Y_UP	10
#define DISTANCE_FROM_FROG_BOT_LEFT_Y_UP	10
#define DISTANCE_FROM_FROG_STATIC_LEFT_Y_UP 10

//THIS IS THE WHEEL UNDER THE BODY
#define DISTANCE_FROM_FROG_LEFT_RIGHT_X_DOWN	10
#define DISTANCE_FROM_FROG_TOP_BOT_X_DOWN	10
#define DISTANCE_FROM_FROG_TOP_LEFT_X_DOWN	10
#define DISTANCE_FROM_FROG_BOT_RIGHT_X_DOWN	10
#define DISTANCE_FROM_FROG_LEFT_RIGHT_Y_DOWN	10
#define DISTANCE_FROM_FROG_TOP_BOT_Y_DOWN	10
#define DISTANCE_FROM_FROG_TOP_LEFT_Y_DOWN	10
#define DISTANCE_FROM_FROG_BOT_RIGHT_Y_DOWN	10
class FrogBody : public CGameObject
{
	int type;
public:
	FrogBody();
	virtual void Render();
	void SetState(int state);
	void SetType(int type);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
