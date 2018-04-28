//
// Created by Andrei on 17-Apr-18.
//

#include "powerups.h"

powerups::powerups( char powerupType , int x , int y ){
    type = powerupType ;
    position = std::make_pair( x , y ) ;
    switch( type ){
        case 'A' :
            aspirine = 25 ;
            food = helmet = 0 ;
            break ;
        case 'F' :
            food = 15 ;
            aspirine = helmet = 0 ;
            break ;
        case 'H' :
            helmet = 10 ;
            food = aspirine = 0 ;
            break ;
        default :
            aspirine = food = helmet = 0 ;
            break ;
    }
}

powerups::~powerups() {
    aspirine = food = helmet = 0 ;
    delete this ;
}

void powerups::setType( char atribute ){
    type = atribute ;
}

char powerups::getType(){
    return type ;
}

void powerups::setAspirine( int atribute ){
    aspirine = atribute ;
}

int powerups::getAspirine(){
    return aspirine ;
}

void powerups::setFood( int atribute ){
    food = atribute ;
}

int powerups::getFood(){
    return food ;
}

void powerups::setHelmet(int atribute){
    helmet = atribute ;
}

int powerups::getHelmet(){
    return helmet ;
}

void powerups::setPowerUpPosition(int x, int y){
    position = std::make_pair( x , y ) ;
}

std::pair < int , int > powerups::getPowerUpPosition() {
    return position ;
}