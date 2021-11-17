#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Mario.h"
#define FROG_GUN_BBOX_WIDTH  7
#define FROG_GUN_BBOX_HEIGHT 7

#define FROG_GUN_STATE_LEFT 100
#define FROG_GUN_STATE_RIGHT 200
#define FROG_GUN_STATE_UP 300
#define FROG_GUN_STATE_LEFT_UP 400
#define FROG_GUN_STATE_RIGHT_UP 401

#define FROG_GUN_ANI_RIGHT_UP 0
#define FROG_GUN_ANI_LEFT 1
#define FROG_GUN_ANI_RIGHT 1
#define FROG_GUN_ANI_LEFT_UP 2
#define FROG_GUN_ANI_UP 3

class FrogGun : public CGameObject
{
	
public:
	FrogGun();
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
