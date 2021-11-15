#include "Quadtree.h"
Quadtree::Quadtree()
{
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
}
Quadtree::Quadtree(double x, double y)
{
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    this->size = Rect(x,y);
}
Quadtree::Quadtree(LPCWSTR path)
{
    
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    ifstream f;
    f.open(path);

    // current resource section flag
    int section = QUAD_SECTION_UNKNOWN;

    char str[MAX_QUAD_LINE];
    while (f.getline(str, MAX_QUAD_LINE))
    {
        string line(str);

        if (line[0] == '#') continue;	// skip comment lines	

        if (line == "[OBJECTS]") {
            section = QUAD_SECTION_OBJECTS; continue;
        }
        switch (section)
        {
            case QUAD_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
        }
    }
   
}
void Quadtree::_ParseSection_OBJECTS(string line)
{
    vector<string> tokens = split(line, " ");

    //DebugOut(L"--> %s\n",ToWSTR(line).c_str());
    
    if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

    int object_type = atoi(tokens[0].c_str());
    float x = atof(tokens[1].c_str());
    float y = atof(tokens[2].c_str());

    int ani_set_id = atoi(tokens[3].c_str());

    CAnimationSets* animation_sets = CAnimationSets::GetInstance();

    CGameObject* obj = NULL;

    switch (object_type)
    {
    
        case OBJECT_TYPE_LADYBIRD:
        {
            int x0 = atof(tokens[4].c_str());
            int y0 = atof(tokens[5].c_str());
            int x1 = atof(tokens[6].c_str());
            int y1 = atof(tokens[7].c_str());
            obj = new LadyBird(x0, y0, x1, y1);
            break;
        }
        case OBJECT_TYPE_BOOM: obj = new Boom(); break;
        case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
        case OBJECT_TYPE_BACKROUND: obj = new Background(); break;
            //case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
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
    obj->SetPosition(x, y);

    LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

    obj->SetAnimationSet(ani_set);
    
    this->object.push_back(obj);
    
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
vector<LPGAMEOBJECT> Quadtree::search(double x, double y)
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
