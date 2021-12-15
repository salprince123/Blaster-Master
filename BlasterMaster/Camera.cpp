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
	//DebugOut(L"%f %f %f %f\n", player_x, player_y, player_x+width, player_y + height);
	if (id == 1)
	{
		
		if (player_x > SMALL_SCENE_1_1_X ) player_x = SMALL_SCENE_1_1_X+ width / 2;
		player_x -= width / 2;
		player_y -= height / 2;
		if (player_x < 0) player_x = 0;
		if (player_x +width > SCENE1_MAX_X) player_x = SCENE1_MAX_X - width;
		if (player_y  < 0) player_y = 0;
		if (player_y  +height > SCENE1_MAX_Y) player_y = SCENE1_MAX_Y-height;
		float _dy = abs(player_y - CGame::getCamera()->getCamPosY());
	}
	else
	{
		//DebugOut(L"%f\n", player_y);
		if (player_x < width/2 || player_x < 204)
		{
			player_x = 10;			
		}	
		else
		{
			player_x -= width / 2;			
		}
		if (player_y  < 95)
		{
			player_y =0;
		}
		else
		{
			player_y -= height / 2;
		}
		if (player_x < 0) player_x = 0;
		if (player_x + width > SCENE2_MAX_X) player_x = SCENE2_MAX_X - width;
	}
	SetCamPos(round(player_x), round(player_y));
}
