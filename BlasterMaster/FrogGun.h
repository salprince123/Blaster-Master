#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Define.h"

class FrogGun : public CGameObject
{
	
public:
	FrogGun();
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
