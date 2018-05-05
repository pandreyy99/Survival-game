//
// Created by Andrei on 17-Apr-18.
//

#ifndef POO2_TERORIST_H
#define POO2_TERORIST_H


#include "../../agent.h"

class terorist : public agent {
    int superAttack;
    int kamikaze;

public:
    terorist(int x, int y, int satt = 50, int kmkz = 10) : agent(250, 100, 150, x, y) {
        superAttack = satt;
        kamikaze = kmkz;
    }

    void setSuperAttack(int atribute);

    int getSuperAttack();

    void setKamikaze(int atribute);

    int getKamikaze();

    int getAttackingPower();

    std::pair<int, int> getPosition();

    void receivingAttack(int enemyAttackingPower);

    virtual ~terorist();

    friend class map;
};

#endif //POO2_TERORIST_H
