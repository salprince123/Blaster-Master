#pragma once
#include "Enemy.h"
#include "Utils.h"
#include "Define.h"
class BallBot : public Enemy
{
public:
	int ny;
	//set in txt file
	int nx;
	int active = 0;
	BallBot(int x0, int y0, int x, int y, int nx);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
