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
	Frog* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int id = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetId();
	float maxX, minX, maxY, minY;
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
		switch (player->littleScene)
		{
		case 1:
			minX = 10;
			maxX = minX+width;
			maxY = 1735;
			minY = 0;
			break;
		case 2:
			minX = 0;
			maxX = 510;
			minY = 1800;
			maxY = 1800+height;
			break;
		case 3:
			minX = 260;
			maxX = 260+width;
			minY = 1277;
			maxY = 1732;
			break;
		case 4:
			minX = 260;
			maxX = 260 + width;
			minY = 1000;
			maxY = 1000+height;
			break;
		
		default:
			minX = 10;
			maxX = minX + width;
			maxY = 1735;
			minY = 0;
			break;
		}

		player_x -= width / 2;
		player_y -= height / 2;	
		if (player_x < minX)
			player_x = minX;
		else if (player_x + width > maxX)
			player_x = maxX - width;
		if (player->isChangeScene == 0)
		{			
			if (player_y < minY)
				player_y = minY;
			else if (player_y + height > maxY)
				player_y = maxY - height;
		}
	}
	SetCamPos(round(player_x), round(player_y));
}
