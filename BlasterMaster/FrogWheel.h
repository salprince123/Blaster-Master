#pragma once
#include "GameObject.h"
#include "Define.h"

class FrogWheel : public CGameObject
{
	int type;
	DWORD lastTime ;
public:
	FrogWheel(int type);
	virtual void Render();
	void SetState(int state);
	void SetType(int type);
	void AutoChangeState();
	void AutoChangeStateWithTime(DWORD time);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

