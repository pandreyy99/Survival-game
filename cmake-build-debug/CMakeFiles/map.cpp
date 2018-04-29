//
// Created by Andrei on 23-Apr-18.
//

#include <iostream>
#include <utility>
#include <cstring>
#include <random>
#include "map.h"
#include "../../CounterTerorist.h"
#include "terorist.h"
#include "Mercenary.h"

using namespace std ;

map::map(int line, int column) {
    if( line < 15 or column < 15)
        return ;
    lines = line ;
    columns = column ;
    table = new int*[ lines ] ;
    for( int i = 0 ; i < lines ; i++ )
        table[i] = new int[ columns ] ;
}

map::~map(){
    for( int i = 0 ; i < lines ; i++ )
        delete[] table[i] ;
    delete[] table ;
    lines = columns = 0 ;
}

void map::initialize(){
    for( int i = 0 ; i < lines ; i++ )
        for(  int j = 0 ; j < columns ; j++ )
            table[i][j] = 0 ;
}

void map::afisare() {
    string temp ;
    int indiceH = 0 , indiceF = 0 , indiceA = 0 ;
    int indiceT = 0 , indiceCt = 0 , indiceM = 0 ;
    for( int i = 0 ; i < 3 * (columns - 2)  ; i++ )
        cout << "- " ;
    cout << endl ;
    for( int i = 0 ; i < lines ; i++ ){
        for( int j = 0 ; j < columns ; j++ ){
            cout << "| " ;
            if( table[i][j] == -3 ) {
                temp = "H" ;
                temp.append(to_string(++indiceH)) ;
                temp.append(" ") ;
                cout << temp ;
            }
            else if( table[i][j] == -2 ) {
                temp = "F" ;
                temp.append(to_string(++indiceF)) ;
                temp.append(" ") ;
                cout << temp ;
            }
            else if( table[i][j] == -1 ) {
                temp = "A" ;
                temp.append(to_string(++indiceA)) ;
                temp.append(" ") ;
                cout << temp ;
            }
            else if( table[i][j] == 0 ) cout << "   " ;
            else if( table[i][j] == 1 ) {
                temp = "T" ;
                temp.append(to_string(++indiceT)) ;
                temp.append(" ") ;
                cout << temp ;
            }
            else if( table[i][j] == 2 ) {
                temp = "CT" ;
                temp.append(to_string(++indiceCt)) ;
                cout << temp ;
            }
            else {
                temp = "M";
                temp.append(to_string(++indiceM)) ;
                temp.append(" ") ;
                cout << temp ;
            }
        }
        cout << " |" ;
        cout << '\n' ;
    }
    for( int i = 0 ; i < 3 * (columns - 2) ; i++ )
        cout << "- " ;
}

void map::create( agent** vectorAgenti , powerups** vectorItems , int nrAgents , int nrItems ){
    default_random_engine generator ;
    uniform_int_distribution<int> distribution ;
    int x , y  ;
    bool ok ;
    for( int i = 0 ; i < nrAgents ; i++ ){
        if( i % 3 == 0 ){
                ok = true ;
                while (ok) {
                    x = distribution(generator) ;
                    y = distribution(generator) ;
                    x = abs( x % lines ) ;
                    y = abs( y % columns ) ;
                    if ( table[x][y] == 0 ) {
                        vectorAgenti[i] = new terorist( x , y ) ;
                        table[x][y] = 1 ;
                        ok = false ;
                    }
                }
        }
        else if( i % 3 == 1 ){
                ok = true ;
                while (ok) {
                    x = distribution(generator) ;
                    y = distribution(generator) ;
                    x = abs( x % lines ) ;
                    y = abs( y % columns ) ;
                    if ( table[x][y] == 0 ) {
                        vectorAgenti[i] = new CounterTerorist( x  , y ) ;
                        table[x][y] = 2 ;
                        ok = false ;
                    }
                }
        }
        else if( i % 3 == 2 ){
                ok = true ;
                while (ok) {
                    x = distribution(generator);
                    y = distribution(generator);
                    x = abs( x % lines ) ;
                    y = abs( y % columns ) ;
                    if ( table[x][y] == 0 ) {
                        vectorAgenti[i] = new Mercenary( x , y ) ;
                        table[x][y] = 3 ;
                        ok = false ;
                    }
                }
        }
    }

    for( int i = 0 ; i < nrItems ; i++ ){
        if( i % 3 == 0 ){
                ok = true ;
                while (ok) {
                    x = distribution(generator) ;
                    y = distribution(generator) ;
                    x = abs( x % lines ) ;
                    y = abs( y % columns ) ;
                    if ( table[x][y] == 0 ) {
                        vectorItems[i] = new powerups( 'A' , x , y ) ;
                        table[x][y] = -1 ;
                        ok = false ;
                    }
                }
        }
        else if( i % 3 == 1 ){
                ok = true ;
                while (ok) {
                    x = distribution(generator) ;
                    y = distribution(generator) ;
                    x = abs( x % lines ) ;
                    y = abs( y % columns ) ;
                    if ( table[x][y] == 0 ) {
                        vectorItems[i] = new powerups( 'F' , x , y ) ;
                        table[x][y] = -2 ;
                        ok = false ;
                    }
                }
        }
        else if( i % 3 == 2 ){
                ok = true ;
                while (ok) {
                    x = distribution(generator) ;
                    y = distribution(generator) ;
                    x = abs( x % lines ) ;
                    y = abs( y % columns ) ;
                    if ( table[x][y] == 0 ) {
                        vectorItems[i] = new powerups( 'H' , x , y ) ;
                        table[x][y] = -3 ;
                        ok = false ;
                    }
                }
        }
    }
}

std::pair < int , int > map::find( agent* other , int ok ) {
    pair<int, int> agentPosition = other->getPosition();
    int x = agentPosition.first , y = agentPosition.second , maxim = -1 ;
    for (int i = 1 ; i <= 3 ; i++) {
        /**
         * caz 1 S
         */
        if (table[x + i][y] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair(x + i, y);
        } else if (table[x + i][y] < 0) {
            maxim = max(maxim, 1);
            agentPosition = make_pair(x + i, y);
            if (maxim == ok) return agentPosition;
        } else if (table[x + i][y] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x + i, y);
            if (maxim == ok) return agentPosition;
        }
        /**
         * caz 2 N
         */
        else if (table[x - i][y] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair( x - i , y );
        } else if (table[x - i][y] < 0) {
            maxim = max(maxim, 1);
            agentPosition = make_pair( x - i , y );
            if (maxim == ok) return agentPosition;
        } else if (table[x - i][y] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x - i, y);
            if (maxim == ok) return agentPosition;
        }
        /**
         * caz 3 E
         */
        else if (table[x][y + i] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair(x , y + i);
        } else if (table[x][y + i] < 0) {
            maxim = max(maxim, 1);
            agentPosition = make_pair(x , y + i);
            if (maxim == ok) return agentPosition;
        } else if (table[x][y + i] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x , y + i);
            if (maxim == ok) return agentPosition;
        }
        /**
         * caz 4 V
         */
        else if (table[x][y - i] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair(x , y - i);
        }
        else if ( table[x][y - i] < 0 ) {
            maxim = max(maxim, 1);
            agentPosition = make_pair(x , y - i);
            if (maxim == ok) return agentPosition;
        } else if (table[x][y - i] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x , y - i);
            if (maxim == ok) return agentPosition;
        }
        /**
         * caz 5 N-V
         */
        else if (table[x - i][y - i] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair(x - i , y - i);
        } else if (table[x - i][y - i] < 0) {
            maxim = max(maxim, 1);
            agentPosition = make_pair(x - i , y - i);
            if (maxim == ok) return agentPosition;
        } else if (table[x - i][y - i] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x - i , y - i);
            if (maxim == ok) return agentPosition;
        }
        /**
         * caz 6 N-E
         */
        else if (table[x - i][y + i] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair(x - i , y + i);
        } else if (table[x - i][y + i] < 0) {
            maxim = max(maxim, 1);
            agentPosition = make_pair(x - i , y + i);
            if (maxim == ok) return agentPosition;
        } else if (table[x - i][y + i] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x - i , y + i);
            if (maxim == ok) return agentPosition;
        }
        /**
         * caz 7 S-E
         */
        else if (table[x + i][y + i] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair(x + i , y + i);
        } else if (table[x + i][y + i] < 0) {
            maxim = max(maxim, 1);
            agentPosition = make_pair(x + i , y + i);
            if (maxim == ok) return agentPosition;
        } else if (table[x + i][y + i] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x + i , y + i);
            if (maxim == ok) return agentPosition;
        }
        /**
         * caz 8 S-V
         */
        else if (table[x + i][y - i] == 0) {
            maxim = max(maxim, 0);
            agentPosition = make_pair(x + i , y - i);
        }
        else if ( table[x + i][y - i] < 0 ) {
            maxim = max(maxim, 1);
            agentPosition = make_pair(x + i , y - i);
            if (maxim == ok) return agentPosition;
        } else if (table[x + i][y - i] > 0) {
            maxim = max(maxim, 2);
            agentPosition = make_pair(x + i , y - i);
            if (maxim == ok) return agentPosition;
        }
        return agentPosition;
    }
}

agent* findAgent( agent** vectorAgenti , int nrAgents , int x , int y ) {
    for( int i = 0 ; i < nrAgents ; i++ ){
        pair < int , int > agentPosition =  vectorAgenti[i]->getPosition() ;
        if( (agentPosition.first == x) and (agentPosition.second == y) ) return vectorAgenti[i] ;
    }
}

powerups* findPowerUp( powerups** vectorItems , int nrItems , int x , int y ) {
    for( int i = 0 ; i < nrItems ; i++ ){
        pair < int , int > itemPosition = vectorItems[i]->getPowerUpPosition() ;
        if( (itemPosition.first == x) and (itemPosition.second == y) ) return vectorItems[i] ;
    }
}

void map::simulateRound(agent** vectorAgenti , powerups** vectorItems , int nrAgents , int nrItems) {
    for (int i = 0; i < nrAgents; i++){
        if( i % 3 == 0 ){
                pair<int, int> curentPosition, nextPosition;
                curentPosition = vectorAgenti[i]->getPosition();
            nextPosition = find(vectorAgenti[i], 2);
            int x = curentPosition.first, y = curentPosition.second;
                table[x][y] = 0;
                x = nextPosition.first;
                y = nextPosition.second;
            if (table[x][y] == 0) {
                vectorAgenti[i]->move(x, y);
                table[x][y] = 1;
                } else if (table[x][y] < 0) {
                powerups *temp = findPowerUp(vectorItems, nrItems, x, y);
                    vectorAgenti[i]->powerup(*temp);
                vectorAgenti[i]->move(x, y);
                table[x][y] = 1;
                }
                else {
                    agent *temp;
                temp = findAgent(vectorAgenti, nrAgents, x, y);
                while (vectorAgenti[i]->getDOA() && temp->getDOA()) {
                        vectorAgenti[i]->receivingAttack(temp->getAttackingPower());
                        temp->receivingAttack(vectorAgenti[i]->getAttackingPower());
                    }
                if (vectorAgenti[i]->getDOA()) {
                        vectorAgenti[i]->move(x, y);
                    table[x][y] = 1;
                    }
                if (!temp->getDOA())
                        table[x][y] = 0 ;
                }
            }
        if( i % 3 == 1 ){
            pair<int, int> curentPosition, nextPosition;
            curentPosition = vectorAgenti[i]->getPosition();
            nextPosition = find(vectorAgenti[i], 1);
            int x = curentPosition.first, y = curentPosition.second;
            table[x][y] = 0;
            x = nextPosition.first;
            y = nextPosition.second;
            if (table[x][y] == 0) {
                vectorAgenti[i]->move(x, y);
                table[x][y] = 2;
            } else if (table[x][y] < 0) {
                powerups *temp = findPowerUp(vectorItems, nrItems, x, y);
                vectorAgenti[i]->powerup(*temp);
                vectorAgenti[i]->move(x, y);
                table[x][y] = 2;
            } else {
                agent *temp;
                temp = findAgent(vectorAgenti, nrAgents, x, y);
                while (vectorAgenti[i]->getDOA() && temp->getDOA()) {
                    vectorAgenti[i]->receivingAttack(temp->getAttackingPower());
                    temp->receivingAttack(vectorAgenti[i]->getAttackingPower());
                }
                if (vectorAgenti[i]->getDOA()) {
                    vectorAgenti[i]->move(x, y);
                    table[x][y] = 2;
                }
                if (!temp->getDOA())
                    table[x][y] = 0;
            }
        }
        if (i % 3 == 2) {
            pair<int, int> curentPosition, nextPosition;
            curentPosition = vectorAgenti[i]->getPosition();
            nextPosition = find(vectorAgenti[i], 1);
            int x = curentPosition.first, y = curentPosition.second;
            table[x][y] = 0;
            x = nextPosition.first;
            y = nextPosition.second;
            if (table[x][y] == 0) {
                vectorAgenti[i]->move(x, y);
                table[x][y] = 3;
            } else if (table[x][y] < 0) {
                powerups *temp = findPowerUp(vectorItems, nrItems, x, y);
                vectorAgenti[i]->powerup(*temp);
                vectorAgenti[i]->move(x, y);
                table[x][y] = 3;
                } else {
                agent *temp;
                temp = findAgent(vectorAgenti, nrAgents, x, y);
                while (vectorAgenti[i]->getDOA() && temp->getDOA()) {
                    vectorAgenti[i]->receivingAttack(temp->getAttackingPower());
                    temp->receivingAttack(vectorAgenti[i]->getAttackingPower());
                }
                if (vectorAgenti[i]->getDOA()) {
                    vectorAgenti[i]->move(x, y);
                    table[x][y] = 3;
                }
                if (!temp->getDOA())
                    table[x][y] = 0;
            }
        }
    }
}

void map::simulate( const int nrAgents , const int nrItems ){
    bool ok ;
    char continuare ;
    int nrRounds = -1 ;
    agent* vectorAgents[ nrAgents ] ;
    powerups* vectorItems[ nrItems ] ;
    this->initialize() ;
    this->create( vectorAgents , vectorItems , nrAgents , nrItems ) ;
    do {
        cout << "Continuam ?(Y/N)" << '\n';
        ok = true;
        nrRounds ++ ;
        do {
            cin >> continuare ;
            if ( strchr( "YyNn" , continuare ) == nullptr ) {
                cout << "Ati introdus un raspuns gresit!" << '\n' ;
                cout << "Va rugam introduceti un raspun corect la urmatoarea rulare! " << '\n';
            }
            else ok = false ;
        }
        while(ok) ;
        if( continuare == 'n' or continuare == 'N' ){
            system("CLS") ;
            cout << "Configuratia hartii in cadrul rundei " << nrRounds << " : " << '\n' ;
            this->afisare() ;
            cout  << '\n' << '\n' << "La revedere !" ;
            exit(1);
        }
        this->simulateRound( vectorAgents , vectorItems , nrAgents , nrItems ) ;
    }
    while(true) ;
}