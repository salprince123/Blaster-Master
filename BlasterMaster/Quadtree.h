#pragma once
#include <iostream>
#include <fstream>;
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
	double width;
	Rect() { this->x = 0; this->y = 0; this->width = WIDTH_OF_QUADTREE; }
	Rect(double x, double y) { this->x = x; this->y = y; this->width = WIDTH_OF_QUADTREE; }
};
class Quadtree
{	
	vector<LPGAMEOBJECT> object;
	Quadtree* topLeftTree;
	Quadtree* topRightTree;
	Quadtree* botLeftTree;
	Quadtree* botRightTree;
	Rect size;
public:
	Quadtree();
	Quadtree(double x, double y);
	Quadtree(LPCWSTR path);
	bool isConstain(float objX, float objY);
	void AddObject();
	void Split();
	void Clear();
	vector<LPGAMEOBJECT> search(double x, double y);
	bool inBoundary(double x, double y);
	void _ParseSection_OBJECTS(string line);
	vector<LPGAMEOBJECT> getAll() { return object; }
};

