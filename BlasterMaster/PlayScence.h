#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Quadtree.h"
#include "Define.h"
#include "Frog.h"
#include "FrogGun.h"
#include "FrogBody.h"
#include "FrogWheel.h"
using namespace std;


class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 
	Frog* player1;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> staticObjects;
	Quadtree* quadtree;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_QUAD(string line);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; } 
	Frog* GetPlayer1() { return player1; }
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

