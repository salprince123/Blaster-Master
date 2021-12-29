#pragma once
#include "GameObject.h"

class Enemy : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int x0 =0;
	int y0 = 0;
	int x1 = 0;
	int y1 = 0;
public:
	int health = 1;
	Enemy();
	Enemy(int x0, int y0, int x, int y);
	virtual void SetState(int state);
};
