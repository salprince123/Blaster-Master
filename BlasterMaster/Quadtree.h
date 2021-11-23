#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "GameObject.h"
#include "Define.h"
#include "LadyBird.h"
#include "Boom.h"
#include "Brick.h"
#include  "Background.h"
#include "Portal.h"
using namespace std;
class Rect
{
public: 
	double x;
	double y;
	float width;
	Rect() { this->x = 0; this->y = 0; this->width = MAX_WIDTH_OF_QUADTREE; }
	Rect(double x, double y) { this->x = x; this->y = y; this->width = MAX_WIDTH_OF_QUADTREE; }
	Rect(double x, double y, float width) { this->x = x; this->y = y; this->width = width; }
	
};
class Quadtree
{	
	vector<LPGAMEOBJECT> object;
	
	int level;
	Rect size;
public:
	Quadtree* topLeftTree;
	Quadtree* topRightTree;
	Quadtree* botLeftTree;
	Quadtree* botRightTree;
	Quadtree();
	Quadtree(int level,double x, double y, float width);
	Quadtree(LPCWSTR path);
	bool isConstain(float objX, float objY);
	void AddObject(LPGAMEOBJECT obj);
	void Split();
	void Clear();
	vector<LPGAMEOBJECT> search(double x, double y);
	bool inBoundary(double x, double y);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_SIZE(string line);
	vector<LPGAMEOBJECT> getAll() { return object; }
};

