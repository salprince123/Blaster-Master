#pragma once
#include "GameObject.h"
#include "Define.h"


class CBrick : public CGameObject
{
public:
	int type = 0;
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};