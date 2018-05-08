//
// Created by Andrei on 23-Apr-18.
//

#include "CounterTerorist.h"

using namespace std;

CounterTerorist::~CounterTerorist() {
    ExtraDefence = 0;
}

void CounterTerorist::setExtraDefence(const int atribute) {
    ExtraDefence = atribute;
}

const int CounterTerorist::getExtraDefence() {
    return ExtraDefence;
}

const int CounterTerorist::getAttackingPower() {
    return this->getAttackPower();
}

pair<int, int> CounterTerorist::getPosition() {
    return position;
}

void CounterTerorist::receivingAttack(const int enemyAttackingPower) {
    this->setDefence(this->getDefence() - enemyAttackingPower);
    if (this->getDefence() < 0) {
        this->setLifePoint(this->getLifePoint() + this->getDefence());
        this->setDefence(0);
        this->setDOA(this->getLifePoint());
    }
}