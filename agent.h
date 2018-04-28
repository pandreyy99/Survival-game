//
// Created by Andrei on 14-Apr-18.
//

#ifndef POO2_AGENT_H
#define POO2_AGENT_H

#include "cmake-build-debug/powerups.h"
#include <random>
#include <utility>

class agent {
    int lifePoint ;
    int defence ;
    int attackPower ;
protected:
    bool deadOrAlive;
    std::pair < int , int > position ;
public:
    agent( int lp , int def , int att , int x , int y ) ;
    void setLifePoint ( int atribute ) ;
    int getLifePoint () ;
    void  setDefence ( int atribute ) ;
    int getDefence () ;
    void setAttackPower ( int atribute ) ;
    int getAttackPower () ;
    void setPosition ( int x , int y ) ;
    virtual std::pair<int, int> getPosition () ;
    void setDOA ( int atribute ) ;
    virtual bool getDOA () ;
    virtual int getAttackingPower() = 0 ;
    virtual void receivingAttack(int enemyAttackingPower) = 0 ;
    virtual void move( int x , int y ) = 0 ;
    virtual void attackeee() = 0 ;
    void powerup ( powerups& powerup ) ;
    virtual ~ agent() ;
    friend class map ;
};

#endif //POO2_AGENT_H