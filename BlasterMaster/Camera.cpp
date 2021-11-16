#include "Camera.h"
#include "Game.h"
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
void Camera::Update(float player_x, float player_y)
{
	player_x -= width / 2;
	player_y -= height / 2;
	float _dy = abs(player_y - CGame::getCamera()->getCamPosY());

	/*if (player_x <= 10 && player_y < CGame::GetInstance()->GetScreenHeight() / 2) CGame::getCamera()->SetCamPos(0, 0.0f);
	else if (_dy > CGame::GetInstance()->GetScreenHeight() * 2 / 3) CGame::getCamera()->SetCamPos(round(player_x), CGame::GetInstance()->getCamPosY() + 100);
	else */CGame::getCamera()->SetCamPos(round(player_x), round(player_y));
}
