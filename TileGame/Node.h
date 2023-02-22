#pragma once
#include "Vector2AStar.h"

class Node
{
public:
    //=========================]Constructeurs[=========================//
    Node(Vector2 positionP);
    Node();
    ~Node();

    //=========================]Variables[=========================//
    Vector2 positon;
    int x;
    int y;
    double cost;
    Node* cameFrom;
    bool traversable;


    //=========================] OPERATORS [=========================//
    bool operator ==(const Node& other)
    {
        if (this->positon.x == other.positon.x && this->positon.y == other.positon.y) return true;
        return false;
    }
    bool operator !=(const Node& other)
    {
        if (this->positon.x == other.positon.x && this->positon.y == other.positon.y) return false;
        return true;
    }


    //
    bool operator>(const Node& other)
    {
        if (this->cost > other.cost) return true;
        return false;
    }
    bool operator>=(const Node& other)
    {
        if (this->cost >= other.cost) return true;
        return false;
    }

    bool operator<(const Node& other)
    {
        if (this->cost < other.cost) return true;
        return false;
    }
    bool operator<=(const Node& other)
    {
        if (this->cost <= other.cost) return true;
        return false;
    }

    //
    Node& operator =(const Node& other)
    {
        this->positon = other.positon;
        this->x = other.x;
        this->y = other.y;
        this->cameFrom = other.cameFrom;
        this->cost = other.cost;
        this->traversable = other.traversable;
        return *this;
    }



};
