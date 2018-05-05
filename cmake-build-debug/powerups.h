//
// Created by Andrei on 17-Apr-18.
//

#ifndef POO2_POWERUPS_H
#define POO2_POWERUPS_H


#include <utility>

class powerups {
    char type;
    int aspirine;
    int food;
    int helmet;
    std::pair<int, int> position;
public :
    powerups(char powerupType, int x, int y);

    void setType(char);

    char getType();

    void setAspirine(int);

    int getAspirine();

    void setFood(int);

    int getFood();

    void setHelmet(int);

    int getHelmet();

    void setPowerUpPosition(int, int);

    std::pair<int, int> getPowerUpPosition();

    virtual ~powerups();

    friend class map;
};

#endif //POO2_POWERUPS_H
