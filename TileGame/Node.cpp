#include "Node.h"

Node::Node()
{   
    positon = {-1,-1};
    x = -1;
    y = -1;
    cameFrom = nullptr;
    cost = -1;
    traversable = true;
    
}

Node::Node(Vector2 positionP) : positon(positionP)
{ 
    x = positon.x;
    y = positon.y;
    cameFrom = nullptr;
    cost = -1;
    traversable = true;   
}

Node::~Node()
{
    
}
