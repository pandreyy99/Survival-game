//
// Created by Andrei on 23-Apr-18.
//

#ifndef POO2_COUNTERTERORIST_H
#define POO2_COUNTERTERORIST_H


#include "agent.h"

using namespace std;

class CounterTerorist : public agent {
    int ExtraDefence;

public:
    CounterTerorist(const int x, const int y, const int extraDef = 30) : agent(250, 150 + extraDef, 130, x, y) {
        ExtraDefence = extraDef;
    }

    void setExtraDefence(const int atribute);

    const int getExtraDefence();

    const int getAttackingPower();

    pair<int, int> getPosition();

    void receivingAttack(const int enemyAttackingPower);

    virtual ~CounterTerorist();

    friend class map;
};

#endif //POO2_COUNTERTERORIST_H
