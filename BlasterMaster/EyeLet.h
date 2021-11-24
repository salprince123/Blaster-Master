#pragma once
#include "Enemy.h"
#include "Utils.h"
#define EYELET_WALKING_SPEED 0.05*0.5;
#define EYELET_FLYING_UP_SPEED 0.05*0.4;

#define EYELET_BBOX_WIDTH 16
#define EYELET_BBOX_HEIGHT 16
#define EYELET_BBOX_HEIGHT_DIE 9

#define EYELET_STATE_WALKING_LEFT 100
#define EYELET_STATE_WALKING_RIGHT 101
#define EYELET_STATE_DIE 200

#define EYELET_ANI_WALKING_LEFT 0
#define EYELET_ANI_WALKING_RIGHT 1
#define EYELET_ANI_WALKING_DIE 2
class EyeLet : public Enemy
{
public:
	int ny;
	int nx;
	int active = 0;
	EyeLet(int x0, int y0, int x, int y, int nx);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};

