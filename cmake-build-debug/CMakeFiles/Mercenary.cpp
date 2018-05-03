//
// Created by Andrei on 23-Apr-18.
//

#include "Mercenary.h"
#include <iostream>

using namespace std ;

Mercenary::~Mercenary(){
    superAttack = extraDefence = 0 ;
}

void Mercenary::setSuperAttack( int atribute ) {
    superAttack = atribute ;
}

int Mercenary::getSuperAttack() {
    return superAttack ;
}

void Mercenary::setExtraDefence( int atribute ) {
    extraDefence = atribute ;
}

int Mercenary::getExtraDefence() {
    return extraDefence ;
}

int Mercenary::getAttackingPower() {
    return this->getAttackPower() + this->getSuperAttack() ;;
}

bool Mercenary::getDOA(){
    return deadOrAlive ;
}

std::pair < int , int > Mercenary::getPosition() {
    return position;
}

void Mercenary::receivingAttack(int enemyAttackingPower){
    this->setDefence( this->getDefence() - enemyAttackingPower ) ;
    if( this->getDefence() < 0 ){
        this->setLifePoint( this->getLifePoint() + this->getDefence() ) ;
        this->setDefence(0) ;
        this->setDOA( this->getLifePoint() ) ;
    }
}