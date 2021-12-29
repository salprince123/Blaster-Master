#pragma once
#pragma warning( disable : 4305 )
#include "Enemy.h"
#include "Utils.h"
#include "Define.h"
class SpecialBackground : public CGameObject
{
public:
	int ny;
	int nx;
	float t_active = 0;
	float pY0 = -99999999.99;
	SpecialBackground(int x0, int y0, int x, int y, int nx);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void Render();
};

