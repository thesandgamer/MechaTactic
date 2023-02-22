#pragma once
#include <algorithm>
#include <vector>

#include "Node.h"


class List
{
public:
    List() {};
    ~List() {};


    //=============]Variables[======================//
    std::vector<Node> nodeList{};


    //=============]Fonctions[======================//
    void Add(Node newNode);

    Node& FindInList(Node node);

    bool IsInList(Node node);

    Node& FindLowestValue();

    void Clear();


    //=============]Operators[======================//

    List& operator+=(const Node& other) {

        this->nodeList.push_back(other);
        return *this;
    }
    List& operator-=(const Node& other) {

        this->nodeList.erase(std::find(this->nodeList.begin(), this->nodeList.end(), other));
        return *this;
    }

};

