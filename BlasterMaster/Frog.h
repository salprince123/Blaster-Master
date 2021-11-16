#pragma once
#include "GameObject.h"

#define FROG_WALKING_SPEED		0.15f 
#define FROG_JUMP_SPEED_Y		0.5f
#define FROG_JUMP_DEFLECT_SPEED 0.2f
#define FROG_GRAVITY			0.002f

#define FROG_STATE_IDLE			0
#define FROG_STATE_WALKING_RIGHT	100
#define FROG_STATE_WALKING_LEFT	200
#define FROG_STATE_JUMP			300
#define FROG_STATE_DIE				400

#define FROG_ANI_IDLE_RIGHT		1
#define FROG_ANI_IDLE_LEFT			2

#define FROG_ANI_WALKING_RIGHT			3
#define FROG_ANI_WALKING_LEFT			4

#define FROG_ANI_DIE				5

#define	FROG_LEVEL	1
#define	PRINCE_LEVEL	2

#define FROG_BBOX_WIDTH  15
#define FROG_BBOX_HEIGHT 27

#define FROG_UNTOUCHABLE_TIME 5000


class Frog : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	Frog(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

