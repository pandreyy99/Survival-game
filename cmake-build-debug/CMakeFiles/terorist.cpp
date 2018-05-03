//
// Created by Andrei on 17-Apr-18.
//

#include "terorist.h"
#include <iostream>

using namespace std ;

void terorist::setSuperAttack( int atribute ){
    superAttack = atribute ;
}

int terorist::getSuperAttack(){
    return superAttack ;
}

void terorist::setKamikaze( int atribute ){
    kamikaze = atribute ;
}

int terorist::getKamikaze(){
    return kamikaze ;
}

bool terorist::getDOA(){
    return deadOrAlive ;
}

int terorist::getAttackingPower() {
    return this->getAttackPower() + this->getSuperAttack() ;
}

std::pair < int , int > terorist::getPosition(){
    return position ;
}

terorist::~terorist(){
    superAttack = kamikaze = 0 ;
}

void terorist::receivingAttack(int enemyAttackingPower){
    this->setDefence( this->getDefence() - enemyAttackingPower ) ;
    if( this->getDefence() < 0 ){
        this->setLifePoint( this->getLifePoint() + this->getDefence() ) ;
        this->setDefence(0) ;
    }
    /**
      * efectul kamikaze
      */
    this->setDefence( this->getDefence() - this->kamikaze ) ;
    if( this->getDefence() < 0 ){
        this->setLifePoint( this->getLifePoint() + this->getDefence() ) ;
        this->setDefence(0) ;
    }
    ///verificam daca mai e in viata
    this->setDOA(this->getLifePoint());
}
