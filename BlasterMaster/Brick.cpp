#include "Brick.h"

void CBrick::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (type == 1)
	{
		r = x + BRICK_BBOX_TYPE1_WIDTH;
		b = y + BRICK_BBOX_TYPE1_WIDTH;
	}
	else
	{
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
}