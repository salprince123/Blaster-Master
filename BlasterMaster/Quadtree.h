#pragma once
#include <iostream>
#include "Utils.h"
#include "GameObject.h"
#define WIDTH_OF_QUADTREE 200
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
	/*Note: 1 quad tree cần có:
	* Các quadtree con
	* vector<object> (chỉ quadtree cấp nhỏ nhất có, các cấp lớn hơn là null)
	* Hàm kiểm tra vị trí đối tượng (x,y) có thuộc quadtree đang gọi hay không (include)
	* Hàm bỏ đối tượng vô quadtree nếu include(nếu gọi đệ quy đúng thì đối tượng sẽ đc chuyển từ quad trê lớn sang quadtree nhỏ nhất,
		cuối cùng chỉ có quadtree nhỏ nhất là danh sách đối tượng NOT NULL)
	* Hàm Clear: giải phóng bộ nhớ 
	* hàm chia quadtree lớn thành quadtree nhỏ hơn (gọi đệ quy đến DIEUKIENDUNG)
	* DIEUKIENDUNG: khi kích thước quadtree =1/2 màn hình
	* Kích thước quad tree : có thể kahi báo dạng x,y width (chỉ cso width vì mình lấy theo hình vuông)
	*	hoặc typedef 1 kiểu SQUARE lưu x,y,width 
	*/
	vector<CGameObject> object;
	Quadtree* topLeftTree;
	Quadtree* topRightTree;
	Quadtree* botLeftTree;
	Quadtree* botRightTree;
	Rect size;
public:
	Quadtree();
	Quadtree(double x, double y);
	bool isConstain(float objX, float objY);
	void AddObject();
	void Split();
	void Clear();
	vector<CGameObject> search(double x, double y);
	bool inBoundary(double x, double y);
};

