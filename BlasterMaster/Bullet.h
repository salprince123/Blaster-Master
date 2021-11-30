#pragma once
#include "GameObject.h"
#define BULLET_BBOX_WIDTH_VERTICAL  6
#define BULLET_BBOX_HEIGHT_VERTICAL 22
#define BULLET_BBOX_WIDTH_HORIZONTAL  22
#define BULLET_BBOX_HEIGHT_HORIZONTAL 6

#define BULLET_STATE_NOT_FIRE	100
#define BULLET_STATE_FIRE_LEFT	-200
#define BULLET_STATE_FIRE_RIGHT	200
#define BULLET_STATE_FIRE_UP	400
#define BULLET_STATE_DIE		500

#define BULLET_ANI_SMALL_LEFT		0
#define BULLET_ANI_SMALL_UP			1
#define BULLET_ANI_BIG_LEFT			2
#define BULLET_ANI_BIG_UP			3
#define BULLET_ANI_SMALL_RIGHT		4
#define BULLET_ANI_BIG_RIGHT		5
#define BULLET_ANI_NOT_FIRE			6
#define BULLET_ANI_DIE				7

#define BULLET_VX 0.15

class Bullet : public CGameObject
{
public:
	int type = 0;
	int id = 0;
	float x0, y0;
	Bullet(int id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandleStateUnFire();
};
