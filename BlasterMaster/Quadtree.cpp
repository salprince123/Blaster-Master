#include "Quadtree.h"
#include "PlayScence.h"
Quadtree::Quadtree()
{
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    level = QUAD_MIN_LEVEL;
}
Quadtree::Quadtree(int level, double x, double y, float width)
{
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    this->size = Rect(x,y);
    this->level = level;
    this->size = Rect(x, y, width);
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
        if (line == "[SIZE]") {
            section = QUAD_SECTION_SIZE; continue;
        }
        switch (section)
        {
            case QUAD_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
            case QUAD_SECTION_SIZE: _ParseSection_SIZE(line); break;
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
    /*int height = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetHeight();
    int row = (height - y) / 16;
    y = (row - 1) * 16;*/
    //DebugOut(L"INFOR %f %f \n", x, y);
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
        case OBJECT_TYPE_EYELET:
        {
            int nx = atof(tokens[4].c_str());
            obj = new EyeLet(x, y, x, y,nx);
            break;
        }
        case OBJECT_TYPE_BALLCARRY:
        {
            int nx = atof(tokens[4].c_str());
            obj = new BallCarry(x, y, x, y, nx);
            break;
        }
        case OBJECT_TYPE_BOOM: obj = new Boom(); break;
        case OBJECT_TYPE_BRICK:
        {
            obj = new CBrick();
            if (tokens.size() == 5)
            {
                int type = atof(tokens[4].c_str());
                dynamic_cast<CBrick*>(obj)->type = type;
            }               
            //DebugOut(L"%d\n", dynamic_cast<CBrick*>(obj)->type);
            break;
        }
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
        case OBJECT_TYPE_BULLET:
        {
            int id = atoi(tokens[4].c_str());
            
            obj = new Bullet(id);
            if (tokens.size() == 6)
            {
                int type= atoi(tokens[5].c_str());
                dynamic_cast<Bullet*>(obj)->type = type;
                CGameObject* preObj = object[object.size() - 1];
                if(dynamic_cast<BallCarry*>(preObj))
                    dynamic_cast<Bullet*>(obj)->SetEnemyHandle(preObj);
                else if (dynamic_cast<Bullet*>(preObj))
                    dynamic_cast<Bullet*>(obj)->SetEnemyHandle(dynamic_cast<Bullet*>(preObj)->enemyHandle);
            }
            break;
        }
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
void Quadtree::_ParseSection_SIZE(string line)
{
    vector<string> tokens = split(line, " ");

    if (tokens.size() < 1) return; 

    int maxWidth = atoi(tokens[0].c_str());
    int maxHeight = atoi(tokens[1].c_str());
    DebugOut(L"[QUAD SIZE] %d %d\n", maxWidth, maxHeight);
    ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->SetHeight(maxHeight);
    ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->SetWidth(maxWidth);
    if(maxHeight> maxWidth)
        this->size.width = maxHeight;
    else 
        this->size.width = maxWidth;
}
    
bool Quadtree::isConstain(float objX, float objY)
{
	return false;
}
bool Quadtree::AddObject(LPGAMEOBJECT obj)
{
    if (!inBoundary(obj->x, obj->y))
        return false;
    this->object.push_back(obj);
    return true;
}
void Quadtree::Split()
{
    double pX = this->size.x;
    double pY = this->size.y;
    DebugOut(L"CHILDNODE LEVEL %d SIZE %d %f\n", this->level, this->object.size(), this->size.width);    
    if (this->object.size() == 0) return;
    float width = this->size.width / 2;    
    if (width <= MIN_WIDTH_OF_QUADTREE) return;
    topLeftTree = new Quadtree(this->level*10 + 1, pX, pY, width);
    topRightTree= new Quadtree(this->level * 10 + 2, pX+width, this->size.y, width);
    botLeftTree= new Quadtree(this->level * 10 + 3, pX, pY+width, width);
    botRightTree= new Quadtree(this->level * 10 + 4, pX+width, pY+width, width);
    for (int i = 0; i < object.size(); i++)
    {
        if(topLeftTree->AddObject(object[i])) continue;
        else if(topRightTree->AddObject(object[i])) continue;
        else if (botLeftTree->AddObject(object[i])) continue;
        else if (botRightTree->AddObject(object[i])) continue;
    }
    this->object.clear();
    topLeftTree->Split();
    topRightTree->Split();
    botLeftTree->Split();
    botRightTree->Split();
    
    
    DebugOut(L"CHILDDDDD LEVEL %d SIZE %d %f\n", this->topLeftTree->level, this->topLeftTree->object.size(), this->topLeftTree->size.width);
    
    
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
    //DebugOut(L"YOU ARE IN SEARCH      %d\n", this->level);
    Rect botRight(size.x + size.width, size.y + size.width);
    // Current quad cannot contain it
    if (!inBoundary(x,y))
        return {};

    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (object.size() > 0)
    {
       // DebugOut(L"THIS IS LEVEL %d SIZE %d %f %f\n", this->level, this->object.size(), this->size.x, this->size.y);
        //LPGAMEOBJECT temp = object[0];
        //temp->SetPosition(this->level, this->level);
        //object.push_back(temp);
        return object;
    }
        

    if ((size.x + botRight.x) / 2 >= x)
    {
        // Indicates topLeftTree
        if ((size.y + botRight.y) / 2 >= y)
        {
            //DebugOut(L"YOU ARE IN TOP LEFT      %d\n", this->level);
            if (topLeftTree == NULL)
                return {};
            return topLeftTree->search(x,y);
        }

        // Indicates botLeftTree
        else
        {
            //DebugOut(L"YOU ARE IN BOT LEFT      %d\n", this->level);
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
           // DebugOut(L"YOU ARE IN TOP RIGHT      %d\n", this->level);
            if (topRightTree == NULL)
                return {};
            return topRightTree->search(x,y);
        }

        // Indicates botRightTree
        else
        {
           // DebugOut(L"YOU ARE IN BOT RIGHT      %d\n", this->level);
            if (botRightTree == NULL)
                return {};
            return botRightTree->search(x,y);
        }
    }
};
int Quadtree::searchLevel(double x, double y)
{
    //DebugOut(L"YOU ARE IN SEARCH      %d\n", this->level);
    Rect botRight(size.x + size.width, size.y + size.width);
    // Current quad cannot contain it
    if (!inBoundary(x, y))
        return -1;

    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (object.size() > 0)
    {
        return level;
    }


    if ((size.x + botRight.x) / 2 >= x)
    {
        // Indicates topLeftTree
        if ((size.y + botRight.y) / 2 >= y)
        {
            //DebugOut(L"YOU ARE IN TOP LEFT      %d\n", this->level);
            if (topLeftTree == NULL)
                return {};
            return topLeftTree->searchLevel(x, y);
        }

        // Indicates botLeftTree
        else
        {
            //DebugOut(L"YOU ARE IN BOT LEFT      %d\n", this->level);
            if (botLeftTree == NULL)
                return {};
            return botLeftTree->searchLevel(x, y);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((size.y + botRight.y) / 2 >= y)
        {
            // DebugOut(L"YOU ARE IN TOP RIGHT      %d\n", this->level);
            if (topRightTree == NULL)
                return {};
            return topRightTree->searchLevel(x, y);
        }

        // Indicates botRightTree
        else
        {
            // DebugOut(L"YOU ARE IN BOT RIGHT      %d\n", this->level);
            if (botRightTree == NULL)
                return {};
            return botRightTree->searchLevel(x, y);
        }
    }
};
