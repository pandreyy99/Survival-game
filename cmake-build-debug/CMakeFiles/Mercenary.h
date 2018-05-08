//
// Created by Andrei on 23-Apr-18.
//

#ifndef POO2_MERCENARY_H
#define POO2_MERCENARY_H

#include "../../agent.h"

using namespace std;

class Mercenary : public agent {
    int superAttack ;
    int extraDefence ;

public:
    Mercenary(const int x, const int y, const int sAtt = 50,
              const int extraDef = 30) : agent(200, 100 + extraDef, 175, x, y) {
        superAttack = sAtt;
        extraDefence = extraDef;
    }

    void setSuperAttack(const int atribute);

    const int getSuperAttack();

    void setExtraDefence(const int atribute);

    const int getExtraDefence();

    const int getAttackingPower();

    pair<int, int> getPosition();

    void receivingAttack(const int enemyAttackingPower);

    virtual ~Mercenary();

    friend class map;
};

#endif //POO2_MERCENARY_H
