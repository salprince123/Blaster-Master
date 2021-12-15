#pragma once
#include "Enemy.h"
#include "Utils.h"
#include "Define.h"
class Sensor : public Enemy
{
public:
	int ny;
	int nx;
	int active = 0;
	float pY0=-99999999;
	Sensor(int x0, int y0, int x, int y, int nx);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};