//
// Created by Andrei on 23-Apr-18.
//

#include "CounterTerorist.h"
#include <iostream>

using namespace std ;

CounterTerorist::~CounterTerorist() {
    ExtraDefence = 0 ;
    delete this ;
}

void CounterTerorist::setExtraDefence( int atribute ){
    ExtraDefence = atribute ;
}

int CounterTerorist::getExtraDefence(){
    return ExtraDefence ;
}

int CounterTerorist::getAttackingPower() {
    return this->getAttackPower() ;
}

bool CounterTerorist::getDOA(){
    return deadOrAlive ;
}

std::pair < int , int > CounterTerorist::getPosition(){
    return position ;
}

void CounterTerorist::receivingAttack(int enemyAttackingPower){
    this->setDefence( this->getDefence() - enemyAttackingPower ) ;
    if( this->getDefence() < 0 ){
        this->setLifePoint( this->getLifePoint() + this->getDefence() ) ;
        this->setDefence(0) ;
        this->setDOA( this->getLifePoint() ) ;
    }
}

void CounterTerorist::move( int x , int y ){
    this->setPosition( x , y ) ;
}
