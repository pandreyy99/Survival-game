//
// Created by Andrei on 23-Apr-18.
//

#ifndef POO2_MAP_H
#define POO2_MAP_H

#include <vector>
#include <utility>
#include <string>
#include "../../agent.h"

using namespace std ;

class map {
    int **table ;
    int lines , columns ;
public:
    map( int , int ) ;
    virtual ~map() ;

    void create(agent **vectorAgenti, powerups **vectorItems, int nrAgents, int nrItems);
    std::pair < int , int > find( agent* other , int ok ) ;
    friend agent* findAgent( agent** vectorAgenti , int nrAgents , int x , int y ) ;
    friend powerups* findPowerUp( powerups** vectorItems , int nrItems , int x , int y ) ;

    friend int verifExista(agent **vectorAgenti, int nrAgents);

    friend int whichAgent(agent **vectorAgents, int nrAgents, int x, int y);

    friend int whichPowerUp(powerups **vectorItems, int nrItems, int x, int y);

    void simulateRound(agent **vectorAgenti, powerups **vectorItems, int nrAgents, int nrItems, int nrRound);
    void simulate( int nrAgents , int nrItems ) ;

    void afisare(agent **vectorAgents, powerups **vectorItems, int nrAgents, int nrItems, int nrRound);

    void afis();
};

#endif //POO2_MAP_H
