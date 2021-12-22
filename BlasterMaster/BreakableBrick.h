#pragma once
#include "Enemy.h"
#include "Define.h"
class BreakableBrick : public Enemy
{
public:
	BreakableBrick();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
