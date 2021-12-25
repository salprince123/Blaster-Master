#pragma once
#include "Enemy.h"
#include "Utils.h"
#include "Define.h"
class GuardLaser : public Enemy
{
public:
	int ny;
	//set in txt file
	int nx;
	int active = 0;
	float tFire = 0;
	int fireX = 0;
	int fireY = 0;
	GuardLaser(int x0, int y0, int x, int y, int nx);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
