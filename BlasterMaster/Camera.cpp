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
	
	int id = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetId();

	if (id == 1)
	{
		if (player_x >= 1307)
		{
			player_x = 1421 - width / 2;
			player_y -= height / 2;
		}
		else
		{
			player_x -= width / 2;
			player_y -= height / 2;
		}
		if (player_x < 0)
			player_x = 0;
		else if (player_x > 1576)
			player_x = 1576;
		if (player_y + height > 784)
			player_y = 784 - height;
		float _dy = abs(player_y - CGame::getCamera()->getCamPosY());
	}
	else
	{
		player_x -= width / 2;
		player_y -= height / 2;
	}

	SetCamPos(round(player_x), round(player_y));
}
