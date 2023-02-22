#include "AStar.h"

AStar::AStar(const int width, const int height): GRID_WIDTH(width), GRID_HEIGHT(height)
{
	aStarGrid = Graph(GRID_WIDTH, GRID_HEIGHT);

}

AStar::AStar(): GRID_WIDTH(0),GRID_HEIGHT(0)
{

}

std::vector<Vector2> AStar::GetPath(Vector2 startPos, Vector2 endPos)
{
	//===========]Initialisation[===========//
    openList.Clear();
    closedList.Clear();

	startNode = Node(startPos);
	startNode.cameFrom = &startNode;
	goalNode = Node(endPos);

	openList += startNode;

	//=====================================//

    while (!openList.nodeList.empty())
    {
        current = openList.FindLowestValue();

        //===========]Debug[===========//
        /*
        cout<< endl << "Selected/Current Node = " << current.x<<" " << current.y <<" f_cost: "<<current.cost << endl;
        cout << "Dans la liste de choix: ";
        for (Node nd : openList.nodeList)
        {
            cout << nd.cost<<" ";
        }
        cout << endl;
        */
        //=============================//


        openList -= current;
        closedList += current;

        if (current == goalNode)
        {
            break;//La recherche du chemin est fini
        }

        //C'est là qu'on va décider quel sera le prochain node à calculer
        for (Node& nextNode : aStarGrid.GetAroundNodes(current))
        {

            if (closedList.IsInList(nextNode) || !aStarGrid.GetNode(nextNode.positon).traversable) //Si le node à déjà été vérifié ou si il n'est pas traversable
            {
                continue; //Passe au voisin suivant
            }

            //On va définir le cout du prochain node
            double newCost = CalculateFCostOfNode(nextNode.positon, startNode.positon, goalNode.positon);

            if (newCost < nextNode.cost || !openList.IsInList(nextNode))//Si le chemin à un plus petit cout que le node qui est check ou si il n'est pas dans open(donc pas encore check)
            {
                //Du coup c'est ce node qu'on va prendre
                nextNode.cost = newCost; //On va set son f cost            
                nextNode.cameFrom = &current; //Dit que le node vien du node current
                nextNode.cameFrom = &aStarGrid.GetNode(current); //Dit que le node vien du node current
                if (!openList.IsInList(nextNode))
                {
                    openList += nextNode;
                }
            }
        }


    }
    if (current != goalNode)
    {
        std::cout << "Path not find" << std::endl;
        return {};
    }
    std::vector<Vector2> path = CalculatePath();

    return path;
}


std::vector<Vector2> AStar::CalculatePath()
{
    std::vector<Vector2> path;
    while (current != startNode)
    {
        path.push_back(current.positon);
        current = closedList.FindInList(*current.cameFrom);
    }
    //path.push_back(startNode.positon);
    reverse(path.begin(), path.end());

    return path;
}
