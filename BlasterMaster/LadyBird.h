#pragma once
#include "Enemy.h"
#include "Utils.h"
#define LADYBIRD_WALKING_SPEED 0.05f;
#define LADYBIRD_FLYING_UP_SPEED 0.05*0.4;

#define LADYBIRD_BBOX_WIDTH 16
#define LADYBIRD_BBOX_HEIGHT 16
#define LADYBIRD_BBOX_HEIGHT_DIE 9

#define LADYBIRD_STATE_WALKING_LEFT 100
#define LADYBIRD_STATE_WALKING_RIGHT 101
#define LADYBIRD_STATE_WALKING_UP 110
#define LADYBIRD_STATE_WALKING_DOWN 111
#define LADYBIRD_STATE_DIE 200

#define LADYBIRD_ANI_WALKING_LEFT 0
#define LADYBIRD_ANI_WALKING_RIGHT 1
#define LADYBIRD_ANI_DIE 2
class LadyBird : public Enemy
{
public:
	LadyBird(int x0, int y0, int x, int y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
