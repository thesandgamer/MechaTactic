#pragma once
#include "Vector2AStar.h"
#include <algorithm>


class AStartUtility
{
public:




};

static const double CalculateHeuristic(Vector2 posA, Vector2 posB)
{

    double dx = abs(posA.x - posB.x);
    double dy = abs(posA.y - posB.y);

    //Le 1 vaut la distance entre les points(ou cases dans le cas d'une grille)
    double heuritic = 1 * (dx + dy) + (sqrt(2) - 2 * 1) * std::min(dx, dy);

    return heuritic;
}

static const double CalculateFCostOfNode(Vector2 currentNode, Vector2 startNode, Vector2 goalNode)
{
    //1) Calcul du g cost: Distance du node par rapport au départ(quand diagonal vaut 14, quand droit vaut 10, pour un déplacement de case)
    double gCost = CalculateHeuristic(currentNode, startNode);
    gCost *= 10;
    gCost = round(gCost);
    //2) Calcul du h cost: heursitique: distance du node par rapport au goal(quand diagonal vaut 14, quand droit vaut 10, pour un déplacement de case)
    double hCost = CalculateHeuristic(currentNode, goalNode);
    hCost *= 10;
    hCost = round(hCost);
    // cout << "F cost of calculated Node: " << currentNode.x << " " << currentNode.y << " is: " << gCost << " + " << hCost << " = " << gCost + hCost << endl;

    return gCost + hCost;
}