//
// Created by Andrei on 14-Apr-18.
//

#include <cstring>
#include "agent.h"

agent::agent(int lp , int def , int att , int x , int y) {
    lifePoint = lp ;
    defence = def ;
    attackPower = att ;
    position.first = x ;
    position.second = y ;
    deadOrAlive = true ;
}

void agent::setLifePoint ( int atribute ) {
    lifePoint = atribute ;
}

int agent::getLifePoint () {
    return lifePoint ;
}

void  agent::setDefence ( int atribute ) {
    defence = atribute ;
}

int agent::getDefence () {
    return defence ;
}

void agent::setAttackPower ( int atribute ) {
    attackPower = atribute ;
}

int agent::getAttackPower () {
    return attackPower ;
}

void agent::setPosition ( int x , int y ) {
    position = std::make_pair( x , y ) ;
}

std::pair<int, int> agent::getPosition () {
    return position ;
}

void agent::setDOA ( int atribute ) {
    deadOrAlive = atribute > 0;
}

bool agent::getDOA () {
    return deadOrAlive ;
}

void agent::powerup ( powerups& powerup ) {
    if( powerup.getType() == 'H' )
        lifePoint += powerup.getAspirine() ;
    else if ( powerup.getType() == 'F' )
        attackPower += powerup.getFood() * 10 ;
    else if (strcmp(reinterpret_cast<const char *>(powerup.getType()), reinterpret_cast<const char *>("A")) == 0 )
        defence += powerup.getHelmet() ;
}

agent::~ agent() {
    lifePoint = defence = attackPower = 0 ;
    position = std::make_pair( 0 , 0 ) ;
    deadOrAlive = false ;
}