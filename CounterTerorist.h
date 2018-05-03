//
// Created by Andrei on 23-Apr-18.
//

#ifndef POO2_COUNTERTERORIST_H
#define POO2_COUNTERTERORIST_H


#include "agent.h"

class CounterTerorist : public agent {
    int ExtraDefence ;
public:
    CounterTerorist ( int x , int y , int extraDef = 30 ) :  agent( 250 , 150 + extraDef , 130 , x , y ){
        ExtraDefence = extraDef ;
    }
    void setExtraDefence( int atribute ) ;
    int getExtraDefence() ;
    bool getDOA() ;
    int getAttackingPower() ;
    std::pair < int , int > getPosition() ;
    void receivingAttack(int enemyAttackingPower) ;
    virtual ~CounterTerorist() ;
    friend class map ;
};

#endif //POO2_COUNTERTERORIST_H
