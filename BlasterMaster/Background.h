#pragma once
#include "GameObject.h"

#define BACKGROUND_BBOX_WIDTH  16
#define BACKGROUND_BBOX_HEIGHT 16

class Background : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};