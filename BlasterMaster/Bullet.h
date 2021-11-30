#pragma once
#include "GameObject.h"
#define BULLET_BBOX_WIDTH_VERTICAL  6
#define BULLET_BBOX_HEIGHT_VERTICAL 22
#define BULLET_BBOX_WIDTH_HORIZONTAL  22
#define BULLET_BBOX_HEIGHT_HORIZONTAL 6

#define BULLET_STATE_NOT_FIRE	100
#define BULLET_STATE_FIRE_LEFT	200
#define BULLET_STATE_FIRE_RIGHT	300
#define BULLET_STATE_FIRE_UP	400
#define BULLET_STATE_DIE		500

#define BULLET_ANI_NOT_FIRE		0
#define BULLET_ANI_FIRE_LEFT	3
#define BULLET_ANI_FIRE_RIGHT	1
#define BULLET_ANI_FIRE_UP		4
#define BULLET_ANI_FIRE_DIE		5

#define BULLET_VX 0.15

class Bullet : public CGameObject
{
public:
	int type = 0;
	int id = 0;
	Bullet(int id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandleStateDie();
	void HandleStateFire(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandleStateUnFire();
};
