#pragma once
#include "GameObject.h"
#include "Brick.h"

#include "Utils.h"
#define FROG_WALKING_SPEED		0.15f 
#define FROG_JUMP_SPEED_Y		0.5f
#define FROG_JUMP_DEFLECT_SPEED 0.2f
#define FROG_GRAVITY			0.002f

#define FROG_STATE_IDLE			100
#define FROG_STATE_WALKING_RIGHT	200
#define FROG_STATE_WALKING_LEFT	300
#define FROG_STATE_JUMP			400
#define FROG_STATE_JUMPING_UP	500
#define FROG_STATE_FALLING_DOWN	600
#define FROG_STATE_DIE				9000

#define	FROG_LEVEL	1
#define	PRINCE_LEVEL	2

#define FROG_BBOX_WIDTH  26
#define FROG_BBOX_HEIGHT 16

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

