//
// Created by Andrei on 23-Apr-18.
//

#ifndef POO2_MERCENARY_H
#define POO2_MERCENARY_H


#include "../../agent.h"

class Mercenary : public agent {
    int superAttack ;
    int extraDefence ;
public:
    Mercenary( int x , int y , int sAtt = 50 , int extraDef = 30 ) : agent( 200 , 100 + extraDef , 175 , x , y ) {
        superAttack = sAtt ;
        extraDefence = extraDef ;
    }
    void setSuperAttack( int atribute ) ;
    int getSuperAttack() ;
    void setExtraDefence( int atribute ) ;
    int getExtraDefence() ;
    int getAttackingPower () ;
    bool getDOA() ;
    std::pair < int , int > getPosition() ;
    void receivingAttack(int enemyAttackingPower) ;
    virtual ~Mercenary() ;
    friend class map ;
};

#endif //POO2_MERCENARY_H
