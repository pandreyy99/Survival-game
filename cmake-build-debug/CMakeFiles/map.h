//
// Created by Andrei on 23-Apr-18.
//

#ifndef POO2_MAP_H
#define POO2_MAP_H

#include <vector>
#include <utility>
#include <string>
#include "../../agent.h"

using namespace std;

class map {
    int **table;
    int lines, columns;

public:
    map(const int, const int);

    virtual ~map();

    void create(agent **vectorAgenti, powerups **vectorItems, const int nrAgents, const int nrItems);

    std::pair<int, int> find(agent *other, const int ok);

    friend agent *findAgent(agent **vectorAgenti, const int nrAgents, const int x, const int y);

    friend powerups *findPowerUp(powerups **vectorItems, const int nrItems, const int x, const int y);

    friend const int verifExista(agent **vectorAgenti, const int nrAgents);

    friend const int whichAgent(agent **vectorAgents, const int nrAgents, const int x, const int y);

    friend const int whichPowerUp(powerups **vectorItems, const int nrItems, const int x, const int y);

    void simulateRound(agent **vectorAgenti, powerups **vectorItems,
                       const int nrAgents, const int nrItems, const int nrRound);

    void simulate(const int nrAgents, const int nrItems);

    void afisare(agent **vectorAgents, powerups **vectorItems,
                 const int nrAgents, const int nrItems, const int nrRound);
};

#endif //POO2_MAP_H
