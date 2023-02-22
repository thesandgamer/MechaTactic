#pragma once
#include <vector>

#include "Node.h"

//Le graph sert à stoquer les informations à propos des nodes, de qui est lié à qui


class Graph
{
public:

    Graph(int width, int height);
    Graph();
    ~Graph();

    int graphWidth;
    int graphHeight;

    std::vector<Node> graphNodes{}; //Liste des nodes dans le jeu

    double GetCostOfNode(Node current, Node  next);

    Node& GetNode(Vector2 node);
    Node& GetNode(Node& node);


    std::vector<Node> GetAroundNodes(Node current);

    void AddObstacles(std::vector<Vector2> positions);
    void AddObstacle(Vector2 position);
    void RemoveObstacle(Vector2 position);

};

