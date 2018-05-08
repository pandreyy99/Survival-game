//
// Created by Andrei on 14-Apr-18.
//

#ifndef POO2_AGENT_H
#define POO2_AGENT_H

#include "cmake-build-debug/powerups.h"
#include <random>
#include <utility>

using namespace std;

class agent {
    int lifePoint;
    int defence;
    int attackPower;

protected:
    bool deadOrAlive;
    pair<int, int> position;

public:
    agent(const int lp, const int def, const int att, const int x, const int y);

    void setLifePoint(const int atribute);

    const int getLifePoint();

    void setDefence(const int atribute);

    const int getDefence();

    void setAttackPower(const int atribute);

    const int getAttackPower();

    virtual pair<int, int> getPosition();

    void setDOA(const int atribute);

    bool getDOA();

    virtual const int getAttackingPower() = 0;

    virtual void receivingAttack(const int enemyAttackingPower) = 0;

    void move(const int x, const int y);

    void powerup(powerups &powerup);

    virtual ~agent();

    friend class map;
};

#endif //POO2_AGENT_H