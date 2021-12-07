#pragma once
class Camera
{
	float cam_x = 0.0f;
	float cam_y = 0.0f;
	float real_cam_y = 0.0f;
	float width;
	float height;
public:
	void SetSize(float w, float h);
	void SetCamPos(float x, float y);
	float getCamPosX();
	float getCamPosY();
	float getRealCamPosY() { return real_cam_y; }
	void setRealCamY(float y) { real_cam_y = y; }
	void Update(float player_x, float player_y, float height);
};

