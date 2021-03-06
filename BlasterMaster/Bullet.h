#pragma once
#pragma warning( disable : 4305 )

#include "GameObject.h"
#include "Define.h"

class Bullet : public CGameObject
{
public:
	LPGAMEOBJECT enemyHandle = NULL;
	int type = 1;
	int isCreate = 0;
	int left = 0;
	int right = 0;
	int id = 0;
	float x0, y0;
	int collideX = 0;
	DWORD lastTime;	
	float ballCarryTime=0;
	int count = 60;
	Bullet(int id);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandleStateUnFire();
	void SetEnemyHandle(LPGAMEOBJECT e) { this->enemyHandle = e; }
	void SetState(int state);
	void EnemyHandleStateFire(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void PlayerHandleStateFire(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	LPGAMEOBJECT CreateBullet(float x, float y, int direction, float vx, float vy);
};
