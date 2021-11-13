#include "Quadtree.h"
Quadtree::Quadtree()
{
    object = vector<CGameObject>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
}
Quadtree::Quadtree(double x, double y)
{
    object = vector<CGameObject>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    this->size = Rect(x,y);
}
bool Quadtree::isConstain(float objX, float objY)
{

	return false;
}
void Quadtree::AddObject()
{
	
}
void Quadtree::Split()
{

}
void Quadtree::Clear()
{

}
bool Quadtree::inBoundary(double x, double y)
{
    return (x >= this->size.x &&
        x <= this->size.x+ this->size.width &&
        y >= this->size.y &&
        y <= this->size.y+this->size.width);
}
vector<CGameObject> Quadtree::search(double x, double y)
{
    Rect botRight(size.x + size.width, size.y + size.width);
    // Current quad cannot contain it
    if (!inBoundary(x,y))
        return {};

    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (object.size()>0)
        return object;

    if ((size.x + botRight.x) / 2 >= x)
    {
        // Indicates topLeftTree
        if ((size.y + botRight.y) / 2 >= y)
        {
            if (topLeftTree == NULL)
                return {};
            return topLeftTree->search(x,y);
        }

        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                return {};
            return botLeftTree->search(x,y);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((size.y + botRight.y) / 2 >= y)
        {
            if (topRightTree == NULL)
                return {};
            return topRightTree->search(x,y);
        }

        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                return {};
            return botRightTree->search(x,y);
        }
    }
};
