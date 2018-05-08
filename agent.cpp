//
// Created by Andrei on 14-Apr-18.
//

#include <cstring>
#include "agent.h"

using namespace std;

agent::agent(const int lp, const int def, const int att, const int x, const int y) {
    lifePoint = lp;
    defence = def;
    attackPower = att;
    position.first = x;
    position.second = y;
    deadOrAlive = true;
}

void agent::setLifePoint(const int atribute) {
    lifePoint = atribute;
}

const int agent::getLifePoint() {
    return lifePoint;
}

void agent::setDefence(const int atribute) {
    defence = atribute;
}

const int agent::getDefence() {
    return defence;
}

void agent::setAttackPower(const int atribute) {
    attackPower = atribute;
}

const int agent::getAttackPower() {
    return attackPower;
}

pair<int, int> agent::getPosition() {
    return position;
}

void agent::setDOA(const int atribute) {
    if (atribute > 0) deadOrAlive = true;
    else deadOrAlive = false;
}

bool agent::getDOA() {
    return deadOrAlive;
}

void agent::powerup(powerups &powerup) {
    lifePoint += powerup.getAspirine();
    defence += powerup.getHelmet();
    attackPower += powerup.getFood();
}

agent::~agent() {
    lifePoint = defence = attackPower = 0;
    position = std::make_pair(0, 0);
    deadOrAlive = false;
}

void agent::move(const int x, const int y) {
    position.first = x;
    position.second = y;
}