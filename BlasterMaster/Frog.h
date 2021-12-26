#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Utils.h"
#include "Define.h"


class Frog : public CGameObject
{
	int level;
	
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	int maxBullet;
	int oldState;
	
public:
	int untouchable;
	int littleScene = 0;
	Frog(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetMaxBullet(int t) { maxBullet = t; }
	int GetMaxBullet() { return maxBullet; }
	void SetOldState(int t) { this->oldState = t; }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	int GetLevel() { return level; }
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

