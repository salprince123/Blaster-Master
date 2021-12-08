#pragma once
#include "GameObject.h"
#include "Define.h"

class Bullet : public CGameObject
{
public:
	int type = 0;
	int id = 0;
	float x0, y0;
	DWORD lastTime;
	Bullet(int id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandleStateUnFire();
};
