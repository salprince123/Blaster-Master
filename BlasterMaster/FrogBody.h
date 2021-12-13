#pragma once
#include "GameObject.h"
#include "Define.h"
class FrogBody : public CGameObject
{
	int type;
public:
	FrogBody();
	virtual void Render();
	void SetState(int state);
	void SetType(int type);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
