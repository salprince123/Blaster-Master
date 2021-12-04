#include "Background.h"
void Background::Render()
{
	animation_set->at(0)->Render(x, yRender);
}

void Background::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BACKGROUND_BBOX_WIDTH;
	b = y + BACKGROUND_BBOX_HEIGHT;
}