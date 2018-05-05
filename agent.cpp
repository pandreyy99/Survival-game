//
// Created by Andrei on 14-Apr-18.
//

#include <cstring>
#include "agent.h"

agent::agent(int lp, int def, int att, int x, int y) {
    lifePoint = lp;
    defence = def;
    attackPower = att;
    position.first = x;
    position.second = y;
    deadOrAlive = true;
}

void agent::setLifePoint(int atribute) {
    lifePoint = atribute;
}

int agent::getLifePoint() {
    return lifePoint;
}

void agent::setDefence(int atribute) {
    defence = atribute;
}

int agent::getDefence() {
    return defence;
}

void agent::setAttackPower(int atribute) {
    attackPower = atribute;
}

int agent::getAttackPower() {
    return attackPower;
}

std::pair<int, int> agent::getPosition() {
    return position;
}

void agent::setDOA(int atribute) {
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

agent::~ agent() {
    lifePoint = defence = attackPower = 0;
    position = std::make_pair(0, 0);
    deadOrAlive = false;
}

void agent::move(int x, int y) {
    position.first = x;
    position.second = y;
}