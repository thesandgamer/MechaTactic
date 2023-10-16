#include "Graph.h"

Graph::Graph(int width, int height) : graphWidth(width), graphHeight(height) {
    for (int xx = 0; xx < width; xx++)//Lignes
    {
        for (int yy = 0; yy < height; yy++)//Colognes
        {
            graphNodes.push_back(Node({ (float)xx, (float)yy }));
        }
    }
}

Graph::Graph()
{
}

Graph::~Graph()
{
}

double Graph::GetCostOfNode(Node current, Node next)
{
    auto it = find(graphNodes.begin(), graphNodes.end(), current);
    if (it != graphNodes.end())
    {
        int index = distance(graphNodes.begin(), it);
        return graphNodes.at(index).cost;

    }

    return -1;
}

Node* Graph::GetNode(Vector2 node)
{
    auto it = find(graphNodes.begin(), graphNodes.end(), node);
    if (it != graphNodes.end())
    {
        int index = distance(graphNodes.begin(), it);
        return &graphNodes.at(index);

    }
    else
    {
        return nullptr;
    }
}

Node* Graph::GetNode(const Node& node)
{
    auto it = find(graphNodes.begin(), graphNodes.end(), node);
    if (it != graphNodes.end())
    {
        int index = distance(graphNodes.begin(), it);
        return &graphNodes.at(index);

    }
    return nullptr;
}

std::vector<Node*> Graph::GetAroundNodes(const Node current)
{
    std::vector<Node*> nodes{};
    /*
    int i = 0;
    //On va parcourir les 9 tiles
    for (int xx = -1; xx < 2; xx++)
    {
        for (int yy = -1; yy < 2; yy++)
        {
            if (xx == 0 && yy == 0) continue;
            if (current.x + xx >= 0 && current.x + xx < graphWidth && current.y + yy >= 0 && current.y + yy < graphHeight) //Check si on est dans la grille
            {
                Node newNode = GetNode({current.x + (float)xx, current.y + (float)yy });// Node(Vector2(current.x + xx, current.y + yy));
                nodes.push_back(newNode);
                i++;
            }

        }
    }*/

    nodes.push_back(GetNode({ current.x - (float)1, current.y + (float)0 }));
    nodes.push_back(GetNode({ current.x + (float)1, current.y + (float)0 }));
    nodes.push_back(GetNode({ current.x + (float)0, current.y - (float)1 }));
    nodes.push_back(GetNode({ current.x + (float)0, current.y + (float)1 }));

    return nodes;
}

void Graph::AddObstacles(std::vector<Vector2> positions)
{
    for (Vector2 pos : positions)
    {
        AddObstacle(pos);
    }
}

void Graph::AddObstacle(Vector2 position)
{
    auto it = find(graphNodes.begin(), graphNodes.end(), position);
    if (it != graphNodes.end())
    {
        int index = distance(graphNodes.begin(), it);
        graphNodes.at(index).traversable = false;

    }
}

void Graph::RemoveObstacle(Vector2 position)
{
    auto it = find(graphNodes.begin(), graphNodes.end(), position);
    if (it != graphNodes.end())
    {
        int index = distance(graphNodes.begin(), it);
        graphNodes.at(index).traversable = true;

    }
}
