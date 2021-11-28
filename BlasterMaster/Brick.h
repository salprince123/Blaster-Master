#pragma once
#include "GameObject.h"
#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 16
#define BRICK_BBOX_TYPE1_WIDTH  16
#define BRICK_BBOX_TYPE1_HEIGHT 48


class CBrick : public CGameObject
{
public:
	int type = 0;
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};