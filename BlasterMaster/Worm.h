#pragma once
#include "Enemy.h"
#include "Utils.h"
#include "Define.h"
class Worm : public Enemy
{
public:
	int ny;
	int nx;
	int active = 0;
	LPGAMEOBJECT enemyHandle = NULL;
	Worm(int x0, int y0, int x, int y, int nx);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetEnemyHandle(LPGAMEOBJECT e) { this->enemyHandle = e; }
	void Render();
	void SetState(int state);
};


