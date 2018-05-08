//
// Created by Andrei on 23-Apr-18.
//

#include "Mercenary.h"

using namespace std ;

Mercenary::~Mercenary(){
    superAttack = extraDefence = 0;
}

void Mercenary::setSuperAttack(const int atribute) {
    superAttack = atribute;
}

const int Mercenary::getSuperAttack() {
    return superAttack;
}

void Mercenary::setExtraDefence(const int atribute) {
    extraDefence = atribute;
}

const int Mercenary::getExtraDefence() {
    return extraDefence;
}

const int Mercenary::getAttackingPower() {
    return this->getAttackPower() + this->getSuperAttack();
}

pair<int, int> Mercenary::getPosition() {
    return position;
}

void Mercenary::receivingAttack(const int enemyAttackingPower) {
    this->setDefence(this->getDefence() - enemyAttackingPower);
    if (this->getDefence() < 0) {
        this->setLifePoint(this->getLifePoint() + this->getDefence());
        this->setDefence(0);
        this->setDOA(this->getLifePoint());
    }
}