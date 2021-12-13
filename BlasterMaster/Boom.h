#pragma once
#include "Enemy.h"
#include "Define.h"
class Boom : public Enemy
{
public:
	Boom();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};
