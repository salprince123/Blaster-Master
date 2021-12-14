#pragma once
#include "GameObject.h"
#include "Define.h"


class Background : public CGameObject
{
public:
	int isUpper = 0;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};