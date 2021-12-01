#pragma warning( disable : 26451 )
#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "LadyBird.h"
#include "Boom.h"

#include "Background.h"

using namespace std;
int _dy = 0;
CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	LPCWSTR path = ToLPCWSTR(tokens[0]);
	ifstream f;
	f.open(path);
	char str[MAX_QUAD_LINE];
	while (f.getline(str, MAX_QUAD_LINE))
	{
		//DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		string line(str); vector<string> tokens = split(line);
		if (line[0] == '#') continue;
		if (tokens.size() < 5) continue; // skip invalid lines

		int texID = atoi(tokens[0].c_str());
		wstring path = ToWSTR(tokens[1]);
		int R = atoi(tokens[2].c_str());
		int G = atoi(tokens[3].c_str());
		int B = atoi(tokens[4].c_str());

		CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
	}
	
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	LPCWSTR path = ToLPCWSTR(tokens[0]);
	ifstream f;
	f.open(path);
	char str[MAX_QUAD_LINE];
	while (f.getline(str, MAX_QUAD_LINE))
	{
		//DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		string line(str); 
		if (line[0] == '#') continue;
		vector<string> tokens = split(line, " ");

		if (tokens.size() < 6) continue; // skip invalid lines

		int ID = atoi(tokens[0].c_str());
		int l = atoi(tokens[1].c_str());
		int t = atoi(tokens[2].c_str());
		int r = atoi(tokens[3].c_str());
		int b = atoi(tokens[4].c_str());
		int texID = atoi(tokens[5].c_str());

		LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
		if (tex == NULL)
		{
			DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
			return; 
		}

		CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
	}
	

	
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	LPCWSTR path = ToLPCWSTR(tokens[0]);
	ifstream f;
	f.open(path);
	char str[MAX_QUAD_LINE];
	while (f.getline(str, MAX_QUAD_LINE))
	{
		//DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		string line(str);
		if (line[0] == '#') continue;
		vector<string> tokens = split(line, " ");

		if (tokens.size() < 3) continue; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

		//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

		LPANIMATION ani = new CAnimation();

		int ani_id = atoi(tokens[0].c_str());
		for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
		{
			int sprite_id = atoi(tokens[i].c_str());
			int frame_time = atoi(tokens[i + 1].c_str());
			ani->Add(sprite_id, frame_time);
		}

		CAnimations::GetInstance()->Add(ani_id, ani);
	}

	
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	LPCWSTR path = ToLPCWSTR(tokens[0]);
	ifstream f;
	f.open(path);
	char str[MAX_QUAD_LINE];
	while (f.getline(str, MAX_QUAD_LINE))
	{
		//DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		string line(str);
		vector<string> tokens = split(line, " ");
		if (line[0] == '#' || tokens.size() < 2) continue;

		int ani_set_id = atoi(tokens[0].c_str());

		LPANIMATION_SET s = new CAnimationSet();

		CAnimations* animations = CAnimations::GetInstance();

		for (int i = 1; i < tokens.size(); i++)
		{
			int ani_id = atoi(tokens[i].c_str());

			LPANIMATION ani = animations->Get(ani_id);
			s->push_back(ani);
		}

		CAnimationSets::GetInstance()->Add(ani_set_id, s);
	}

	
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line," ");

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	//DebugOut(L"STATIC OBJECT TYPE= %d\n", object_type);
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int height = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetHeight();
	int row = (height - y) / 16;
	y = (row - 1) * 16;
	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
		case OBJECT_TYPE_FROG:
		{
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			obj = new Frog(x, y);
			player = (Frog*)obj;
			DebugOut(L"[INFO] Player object created!\n");
			break;
		}	
		
		case OBJECT_TYPE_FROG_GUN:
		{			
			obj = new FrogGun();
			gun = (FrogGun*)obj;
			break;
		}
		case OBJECT_TYPE_FROG_BODY:
		{
			obj = new FrogBody();
			int type = atoi(tokens[4].c_str());
			dynamic_cast<FrogBody*>(obj)->SetType(type);
			if(type== FROG_BODY_TYPE_UP)
				bodyUp = (FrogBody*)obj;
			else bodyDown = (FrogBody*)obj;
			break;
		}
		case OBJECT_TYPE_FROG_WHEEL:
		{
			int type = atoi(tokens[4].c_str());
			obj = new FrogWheel(type);	
			if (type == FROG_WHEEL_TYPE_LEFT)
				wheelLeft = (FrogWheel*)obj;
			else wheelRight = (FrogWheel*)obj;
			break;
		}
		case OBJECT_TYPE_BULLET:
		{
			int id = atoi(tokens[4].c_str());
			obj = new Bullet(id);
			break;
		}
		case OBJECT_TYPE_BACKROUND: obj = new Background(); break;
		case OBJECT_TYPE_PORTAL:
			{	
				float r = atof(tokens[4].c_str());
				float b = atof(tokens[5].c_str());
				int scene_id = atoi(tokens[6].c_str());
				obj = new CPortal(x, y, r, b, scene_id);
			}
			break;
		default:
			DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
			return;
	}

	// General object setup
	if (obj != NULL)
	{
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		if (object_type == OBJECT_TYPE_BACKROUND)
			staticObjects.insert(staticObjects.begin(), obj);
		else
			staticObjects.push_back(obj);
	}	
}

void CPlayScene::_ParseSection_QUAD(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	LPCWSTR path = ToLPCWSTR(tokens[0]);
	quadtree = new Quadtree(path);
	//this->objects = quadtree->getAll();
	quadtree->Split();
}
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[QUADTREE]") {
			section = SCENE_SECTION_QUAD; continue;
		}
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); DebugOut(L"STATIC OBJECT  \n") ; break;
			case SCENE_SECTION_QUAD: _ParseSection_QUAD(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}
void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	
	Camera* camera = CGame::getCamera();
	CGame* game = CGame::GetInstance();
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	float camX = camera->getCamPosX();
	float camY = camera->getCamPosY();
	float camWidth = game->GetScreenWidth();
	float camHeight = game->GetScreenHeight();
	//DebugOut(L"[CAMPOS] %f %f %f %f\n", camera->getCamPosX(), camera->getCamPosY(), player->x, player->y);
	//int row = (GetHeight() - camera->getCamPosY()) / 16;
	//int temp = (row ) * 16;
	//vector<LPGAMEOBJECT> topLeft = quadtree->search(player->x, player->y);
	vector<LPGAMEOBJECT> topLeft = quadtree->search(camX, camY);
	vector<LPGAMEOBJECT> topRight = quadtree->search((camX+camWidth), camY);
	vector<LPGAMEOBJECT> botLeft = quadtree->search(camX, (camY +camHeight));
	vector<LPGAMEOBJECT> botRight = quadtree->search((camX+camWidth), (camY +camHeight));

	//clear the same vector object 
	int topLeftLevel = quadtree->searchLevel(camX, camY);
	int topRightLevel = quadtree->searchLevel((camX + camWidth), camY);
	int botLeftLevel = quadtree->searchLevel(camX, (camY + camHeight));
	int botRightLevel = quadtree->searchLevel((camX + camWidth), (camY + camHeight));	
	if (topRightLevel == topLeftLevel)
		topRight.clear();
	if (botLeftLevel == topLeftLevel)
		botLeft.clear();
	if (botRightLevel == topLeftLevel)
		botRight.clear();

	if (botLeftLevel == topRightLevel)
		botLeft.clear();
	if (botRightLevel == topRightLevel)
		botRight.clear();

	if (botRightLevel == botLeftLevel)
		botRight.clear();
	//insert object from quadtree
	objects.clear();	
	objects.insert(objects.end(), topLeft.begin(), topLeft.end());
	objects.insert(objects.end(), topRight.begin(), topRight.end());
	objects.insert(objects.end(), botLeft.begin(), botLeft.end());
	objects.insert(objects.end(), botRight.begin(), botRight.end());

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	//DebugOut(L"HAVE %d LADYBIRD \n",temp);
	for (size_t i = 0; i < staticObjects.size(); i++)
	{
		staticObjects[i]->Update(dt, &coObjects);
		//DebugOut(L"type %f\n", staticObjects[0]->x);
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	camera->SetSize(game->GetScreenWidth(), game->GetScreenHeight());
	camera->Update(cx, cy,this->GetHeight());
	
}

void CPlayScene::Render()
{
	for (size_t i = 0; i < staticObjects.size(); i++)
		staticObjects[i]->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	Frog* frog = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if(frog->GetState() != FROG_STATE_FALLING_DOWN && frog->GetState() != FROG_STATE_JUMPING_UP)
			frog->SetState(FROG_STATE_JUMP);
		break;
	case DIK_A:
		{
			int oldState = frog->GetState();
			frog->SetState(FROG_STATE_FIRE);
			frog->SetMaxBullet(frog->GetMaxBullet() - 1);
			if (frog->GetMaxBullet() == 0)
				frog->SetMaxBullet(MAX_BULLET);
			frog->SetOldState(oldState);
			break;
		}
		
	case DIK_R: 
		frog->Reset();
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();
	Frog* frog = ((CPlayScene*)scence)->GetPlayer();
	// disable control key when Mario die 
	if (frog->GetState() == FROG_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		frog->SetState(FROG_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		frog->SetState(FROG_STATE_WALKING_LEFT);
	else
	{
		if(frog->GetState() != FROG_STATE_FALLING_DOWN && frog->GetState() != FROG_STATE_JUMPING_UP)
		//DebugOut(L"KEYSTATE %f \n", mario->vx);
			frog->SetState(FROG_STATE_IDLE);
	}
	//Camera* camera = CGame::getCamera();
	//camera->Update(camera->getCamPosX(), camera->getCamPosY(), ((CPlayScene*)scence) ->GetHeight());
		
}