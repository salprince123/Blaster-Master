#include "Camera.h"
#include "Game.h"
#include "PlayScence.h"
void Camera::SetCamPos(float x, float y)
{
	cam_x = x; cam_y = y;
}
void Camera::SetSize(float w, float h)
{
	width = w; height = h;
}
float Camera::getCamPosY()
{
	return cam_y;
}
float Camera::getCamPosX()
{
	return cam_x;
}
void Camera::Update(float player_x, float player_y, float h)
{
	//player_y = h + 16 - player_y;
	//player_y = player_y + (-2 * player_y -16+h);
	if (player_y < 383 && player_x>=1380)
	{
		player_x = 1380;
		player_y -= height / 2;
	}
	else
	{
		
		player_x -= width / 2;
		player_y -= height / 2;
	}
	float _dy = abs(player_y - CGame::getCamera()->getCamPosY());	

	SetCamPos(round(player_x), round(player_y));
}
