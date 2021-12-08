#pragma once
#include "Enemy.h"
#include "Utils.h"
#include "Define.h"
class LadyBird : public Enemy
{
public:
	LadyBird(int x0, int y0, int x, int y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
