#pragma once
#include "GameObject.h"

#define FROG_GUN_BBOX_WIDTH  7
#define FROG_GUN_BBOX_HEIGHT 7

#define FROG_GUN_STATE_BOT_LEFT 100
#define FROG_GUN_STATE_LEFT_RIGHT 200
#define FROG_GUN_STATE_TOP_LEFT 300
#define FROG_GUN_STATE_TOP_BOT 400

#define FROG_GUN_ANI_BOT_LEFT 0
#define FROG_GUN_ANI_LEFT_RIGHT 1
#define FROG_GUN_ANI_TOP_LEFT 2
#define FROG_GUN_ANI_TOP_BOT 3

class FrogGun : public CGameObject
{
public:
	FrogGun();
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void UpdateWithPlayer(DWORD dt, vector<LPGAMEOBJECT>* coObjects, float pX, float pY);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
