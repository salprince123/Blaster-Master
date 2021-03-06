#include "Enemy.h"
#include "Utils.h"
Enemy::Enemy()
{
	this->ObjectType = OBJECT_TYPE_ENEMY;
}
Enemy::Enemy(int x0, int y0, int x1, int y1)
{
	this->ObjectType = OBJECT_TYPE_ENEMY; 
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
}

void Enemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt, coObjects);
	if (isShoot != 0)
	{
		if (time == 0)
			time = GetTickCount64();
		else if (GetTickCount64() - time > 200)
		{
			time = 0;
			isShoot = 0;
		}
	}
}

void Enemy::Render()
{
	
}

void Enemy::SetState(int state)
{
	CGameObject::SetState(state);
	
}
