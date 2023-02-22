#include "List.h"

void List::Add(Node newNode)
{
    nodeList.push_back(newNode);
}

Node& List::FindInList(Node node)
{
    auto it = find(nodeList.begin(), nodeList.end(), node);
    if (it != nodeList.end())
    {
        int index = distance(nodeList.begin(), it);
        return nodeList.at(index);

    }
    else
    {
        //cout << "NOT FOUND IN THE LIST" << endl;
    }
}

bool List::IsInList(Node node)
{
    auto it = find(nodeList.begin(), nodeList.end(), node);
    if (it != nodeList.end())
    {
        return true;

    }
    return false;
}

Node& List::FindLowestValue()
{
    return *std::min_element(nodeList.begin(), nodeList.end());
}

void List::Clear()
{
    nodeList.clear();
}
