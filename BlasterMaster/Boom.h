#pragma once
#include "Enemy.h"
#include "Utils.h"
#define BOOM_BBOX_WIDTH 16
#define BOOM_BBOX_HEIGHT 15
#define BOOM_BBOX_HEIGHT_DIE 0

#define BOOM_STATE_ALIVE 100
#define BOOM_STATE_DIE 200

#define BOOM_ANI_ALIVE 0
#define BOOM_ANI_DIE 1
class Boom : public Enemy
{
public:
	Boom();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
