#pragma once
#include "Enemy.h"
#include "Define.h"
class Enemy1 : public Enemy
{
public:
	Enemy1();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};