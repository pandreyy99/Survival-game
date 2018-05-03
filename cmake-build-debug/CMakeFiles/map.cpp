//
// Created by Andrei on 23-Apr-18.
//

#include <iostream>
#include <utility>
#include <cstring>
#include <random>
#include <fstream>
#include "map.h"
#include "../../CounterTerorist.h"
#include "terorist.h"
#include "Mercenary.h"

using namespace std;

map::map(int line, int column) {
    lines = line ;
    columns = column ;
    table = new int *[lines];
    for (int i = 0; i < lines; i++)
        table[i] = new int[columns];
    for (int i = 0; i < lines; i++)
        for (int j = 0; j < columns; j++)
            table[i][j] = 0 ;
}

map::~map() {
    lines = columns = 0;
    for (int i = 0; i < columns; i++)
        delete[] table[i];
    delete table;
}

int whichAgent(agent **vectorAgents, int nrAgents, int x, int y) {
    for (int i = 0; i < nrAgents; i++)
        if (vectorAgents[i]->getPosition().first == x)
            if (vectorAgents[i]->getPosition().second == y)
                return i;
    return -1;
}

int whichPowerUp(powerups **vectorItems, int nrItems, int x, int y) {
    for (int i = 0; i < nrItems; i++)
        if (vectorItems[i]->getPowerUpPosition().first == x and vectorItems[i]->getPowerUpPosition().second == y)
            return i;
    return -1;
}

void map::afisare(agent **vectorAgents, powerups **vectorItems, int nrAgents, int nrItems, int nrRound) {
    ofstream out("C:\\Users\\Andrei\\Documents\\GitHub\\Survival-game\\afisare.txt");
    string temp;

    out << "Configuratia hartii in cadrul rundei " << nrRound << " : " << '\n';

    for (int i = 0; i < 3 * (columns - 1); i++)
        out << "- ";
    out << endl;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            out << "| ";
            if (table[i][j] == -3) {
                temp = "H";
                if (whichPowerUp(vectorItems, nrItems, i, j) != -1) {
                    temp.append(to_string(whichPowerUp(vectorItems, nrItems, i, j) / 3 + 1));
                    temp.append(" ");
                    out << temp;
                } else out << "   ";
            } else if (table[i][j] == -2) {
                temp = "F";
                if (whichPowerUp(vectorItems, nrItems, i, j) != -1) {
                    temp.append(to_string(whichPowerUp(vectorItems, nrItems, i, j) / 3 + 1));
                    temp.append(" ");
                    out << temp;
                } else out << "   ";
            } else if (table[i][j] == -1) {
                temp = "A";
                if (whichPowerUp(vectorItems, nrItems, i, j) != -1) {
                    temp.append(to_string(whichPowerUp(vectorItems, nrItems, i, j) / 3 + 1));
                    temp.append(" ");
                    out << temp;
                } else out << "   ";
            } else if (table[i][j] == 0) out << "   ";
            else if (table[i][j] == 1) {
                temp = "T";
                if (whichAgent(vectorAgents, nrAgents, i, j) != -1) {
                    temp.append(to_string(whichAgent(vectorAgents, nrAgents, i, j) / 3 + 1));
                    temp.append(" ");
                    out << temp;
                } else out << "   ";
            } else if (table[i][j] == 2) {
                temp = "CT";
                if (whichAgent(vectorAgents, nrAgents, i, j) != -1) {
                    temp.append(to_string(whichAgent(vectorAgents, nrAgents, i, j) / 3 + 1));
                    temp.append(" ");
                    out << temp;
                } else out << "   ";
            } else {
                temp = "M";
                if (whichAgent(vectorAgents, nrAgents, i, j) != -1) {
                    temp.append(to_string(whichAgent(vectorAgents, nrAgents, i, j) / 3 + 1));
                    temp.append(" ");
                    out << temp;
                } else out << "   ";
            }
        }
        out << " |";
        out << '\n';
    }
    for (int i = 0; i < 3 * (columns - 1); i++)
        out << "- ";
}

/**void map::afisare( int nrRound) {
   /// ofstream cout("C:\\Users\\Andrei\\Documents\\GitHub\\Survival-game\\afisare.txt") ;
    string temp ;
    int indiceH = 0 , indiceF = 0 , indiceA = 0 ;
    int indiceT = 0 , indiceCt = 0 , indiceM = 0 ;
    cout << "Configuratia la runda " << nrRound << " : " << '\n' ;
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
            else if( table[i][j] == 0 ) cout << "E " ;
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
}*/

void map::afis() {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++)
            if (table[i][j] >= 0)
                cout << " " << table[i][j] << " ";
            else cout << table[i][j] << " ";
        cout << endl;
    }
}

/**void map::afis( agent** vectorAgents , int nrAgents ) {
    for( int i = 0 ; i < nrAgents ; i++ )
        cout << "Agentul " << i+1 << " are pozitia ( " << vectorAgents[i]->getPosition().first << " , " << vectorAgents[i]->getPosition().second << " )\n" ;
}*/

void map::create(agent **vectorAgenti, powerups **vectorItems, int nrAgents, int nrItems) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution;
    int x, y;
    bool ok ;
    for (int i = 0; i < nrAgents; i++) {
        if (i % 3 == 0) {
            ok = true;
            while (ok) {
                x = distribution(generator);
                y = distribution(generator);
                x = abs(x % lines);
                y = abs(y % columns);
                if (table[x][y] == 0) {
                    vectorAgenti[i] = new terorist(x, y);
                    table[x][y] = 1;
                    ok = false;
                }
            }
        } else if (i % 3 == 1) {
            ok = true;
            while (ok) {
                x = distribution(generator);
                y = distribution(generator);
                x = abs(x % lines);
                y = abs(y % columns);
                if (table[x][y] == 0) {
                    vectorAgenti[i] = new CounterTerorist(x, y);
                    table[x][y] = 2;
                    ok = false;
                }
            }
        } else if (i % 3 == 2) {
            ok = true;
            while (ok) {
                x = distribution(generator);
                y = distribution(generator);
                x = abs(x % lines);
                y = abs(y % columns);
                if (table[x][y] == 0) {
                    vectorAgenti[i] = new Mercenary(x, y);
                    table[x][y] = 3;
                    ok = false;
                }
            }
        }
    }

    for (int i = 0; i < nrItems; i++) {
        if (i % 3 == 0) {
            ok = true;
            while (ok) {
                x = distribution(generator);
                y = distribution(generator);
                x = abs(x % lines);
                y = abs(y % columns);
                if (table[x][y] == 0) {
                    vectorItems[i] = new powerups('A', x, y);
                    table[x][y] = -1;
                    ok = false;
                }
            }
        } else if (i % 3 == 1) {
            ok = true;
            while (ok) {
                x = distribution(generator);
                y = distribution(generator);
                x = abs(x % lines);
                y = abs(y % columns);
                if (table[x][y] == 0) {
                    vectorItems[i] = new powerups('F', x, y);
                    table[x][y] = -2;
                    ok = false;
                }
            }
        } else if (i % 3 == 2) {
            ok = true;
            while (ok) {
                x = distribution(generator);
                y = distribution(generator);
                x = abs(x % lines);
                y = abs(y % columns);
                if (table[x][y] == 0) {
                    vectorItems[i] = new powerups('H', x, y);
                    table[x][y] = -3;
                    ok = false;
                }
            }
        }
    }
}

std::pair<int, int> map::find(agent *other, int ok) {
    pair<int, int> agentPosition = other->getPosition(), nextPosition;
    int x = agentPosition.first , y = agentPosition.second , maxim = -1 ;
    int dir[4] = {-2, -1, 1, 2};
    for (int i = 1; i <= 2; i++) {
        /// Caz 1 : S
        if (x + i < lines) { /// daca putem cauta
            if (table[x + i][y] < 0) { /// daca gasim powerup
                maxim = max(maxim, 1);
                nextPosition = make_pair(x + i, y);
                if (maxim == ok) return nextPosition; /// 1 = prioritar e powerup-ul , 2 = prioritar e inamicul
            } else if (table[x + i][y] > 0) { /// daca gasim inamic
                maxim = max(maxim, 2);
                nextPosition = make_pair(x + i, y);
                if (maxim == ok) return nextPosition;
            }
        }
            /// Caz 2 : N
        else if (x - i >= 0) {
            if (table[x - i][y] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x - i, y);
                if (maxim == ok) return nextPosition;
            } else if (table[x - i][y] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x - i, y);
                if (maxim == ok) return nextPosition;
            }
        }
            /// Caz 3 : E
        else if (y + i < columns) {
            if (table[x][y + i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x, y + i);
                if (maxim == ok) return nextPosition;
            } else if (table[x][y + i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x, y + i);
                if (maxim == ok) return nextPosition;
            }
        }
            /// Caz 4 : V
        else if (y - i >= 0) {
            if (table[x][y - i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x, y - i);
                if (maxim == ok) return nextPosition;
            } else if (table[x][y - i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x, y - i);
                if (maxim == ok) return nextPosition;
            }
        }
            /// Caz 5 : N-V
        else if (x - i >= 0 and y - i >= 0) {
            if (table[x - i][y - i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x - i, y - i);
                if (maxim == ok) return nextPosition;
            } else if (table[x - i][y - i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x - i, y - i);
                if (maxim == ok) return nextPosition;
            }
        }
            /// Caz 6 : N-E
        else if (x - i >= 0 and y + i < columns) {
            if (table[x - i][y + i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x - i, y + i);
                if (maxim == ok) return nextPosition;
            } else if (table[x - i][y + i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x - i, y + i);
                if (maxim == ok) return nextPosition;
            }
        }
            /// Caz 7 : S-E
        else if (x + i < lines and y + i < columns) {
            if (table[x + i][y + i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x + i, y + i);
                if (maxim == ok) return nextPosition;
            } else if (table[x + i][y + i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x + i, y + i);
                if (maxim == ok) return nextPosition;
            }
        }
            /// Caz 8 : S-V
        else if (x + i < lines and y - i >= 0) {
            if (table[x + i][y - i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x + i, y - i);
                if (maxim == ok) return nextPosition;
            } else if (table[x + i][y - i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x + i, y - i);
                if (maxim == ok) return nextPosition;
            }
        }
    }
    /// daca nu gasim ce era prioritar ,  verificam daca am gasit ceva de o prioritate mai mica
    /// si returnam ultima astfel de pozitie
    if (maxim >= 1) return nextPosition;
    /// daca nu am gasit nimic , generam o pozitie viitoare random
    while (maxim != 0) {
        int dirx = rand() % 4, diry = rand() % 4;
        if (x + dir[dirx] < lines && x + dir[dirx] >= 0 && y + dir[diry] < columns && y + dir[diry] >= 0) {
            nextPosition = make_pair(x + dir[dirx], y + dir[diry]);
            maxim = 0;
        }
    }
    return nextPosition;
}

agent *findAgent(agent **vectorAgenti, int nrAgents, int x, int y) {
    for (int i = 0; i < nrAgents; i++) {
        pair<int, int> agentPosition = vectorAgenti[i]->getPosition();
        if ((agentPosition.first == x) and (agentPosition.second == y)) return vectorAgenti[i];
    }
    return nullptr;
}

powerups *findPowerUp(powerups **vectorItems, int nrItems, int x, int y) {
    for (int i = 0; i < nrItems; i++) {
        pair<int, int> itemPosition = vectorItems[i]->getPowerUpPosition();
        if ((itemPosition.first == x) and (itemPosition.second == y)) return vectorItems[i];
    }
    return nullptr;
}

int verifExista(agent **vectorAgenti, int nrAgents) {
    int nrAlive = 0, poz;
    for (int i = 0; i < nrAgents; i++)
        if (vectorAgenti[i]->getDOA()) {
            nrAlive++;
            poz = i;
        }
    if (nrAlive == 1) return poz;
    if (nrAlive > 1) return -1;
    return -2;
}

void map::simulateRound(agent **vectorAgenti, powerups **vectorItems, int nrAgents, int nrItems, int nrRound) {
    for (int i = 0; i < nrAgents; i++) {
        if (vectorAgenti[i]->getDOA()) {
            if (i % 3 == 0) {
                pair<int, int> curentPosition, nextPosition;
                curentPosition = vectorAgenti[i]->getPosition();
                nextPosition = find(vectorAgenti[i], 2);
                int x = nextPosition.first, y = nextPosition.second;
                table[curentPosition.first][curentPosition.second] = 0;
                if (table[x][y] == 0) {
                    table[x][y] = 1;
                    vectorAgenti[i]->move(x, y);
                } else if (table[x][y] < 0) {
                    powerups *temp = findPowerUp(vectorItems, nrItems, x, y);
                    if (temp != nullptr) {
                        table[x][y] = 1;
                        vectorAgenti[i]->powerup(*temp);
                        vectorAgenti[i]->move(x, y);
                    } else cout << "Return de powerup gresit!\n";
                } else {
                    agent *temp;
                    temp = findAgent(vectorAgenti, nrAgents, x, y);
                    if (temp != nullptr) {
                        while (vectorAgenti[i]->getDOA() && temp->getDOA()) {
                            vectorAgenti[i]->receivingAttack(temp->getAttackingPower());
                            temp->receivingAttack(vectorAgenti[i]->getAttackingPower());
                        }
                    } else cout << "Return de agent gresit!\n";

                    if (vectorAgenti[i]->getDOA()) {
                        table[x][y] = 1;
                        vectorAgenti[i]->move(x, y);
                    } else if (!temp->getDOA()) {
                        table[x][x] = 0;
                    }
                }
            } else if (i % 3 == 1) {
                pair<int, int> curentPosition, nextPosition;
                curentPosition = vectorAgenti[i]->getPosition();
                nextPosition = find(vectorAgenti[i], 1);
                int x = nextPosition.first, y = nextPosition.second;
                table[curentPosition.first][curentPosition.second] = 0;
                if (table[x][y] == 0) {
                    table[x][y] = 2;
                    vectorAgenti[i]->move(x, y);
                } else if (table[x][y] < 0) {
                    powerups *temp = findPowerUp(vectorItems, nrItems, x, y);
                    if (temp != nullptr) {
                        table[x][y] = 2;
                        vectorAgenti[i]->powerup(*temp);
                        vectorAgenti[i]->move(x, y);
                    } else cout << "Return de powerup gresit!\n";
                } else {
                    agent *temp;
                    temp = findAgent(vectorAgenti, nrAgents, x, y);
                    if (temp != nullptr) {
                        while (vectorAgenti[i]->getDOA() && temp->getDOA()) {
                            vectorAgenti[i]->receivingAttack(temp->getAttackingPower());
                            temp->receivingAttack(vectorAgenti[i]->getAttackingPower());
                        }
                    } else cout << "Return de agent gresit!\n";
                    if (vectorAgenti[i]->getDOA()) {
                        table[x][y] = 2;
                        vectorAgenti[i]->move(x, y);
                    } else if (!temp->getDOA()) {
                        table[x][y] = 0;
                    }
                }
            } else if (i % 3 == 2) {
                pair<int, int> curentPosition, nextPosition;
                curentPosition = vectorAgenti[i]->getPosition();
                nextPosition = find(vectorAgenti[i], 1);
                int x = nextPosition.first, y = nextPosition.second;
                table[curentPosition.first][curentPosition.second] = 0;
                if (table[x][y] == 0) {
                    table[x][y] = 3;
                    vectorAgenti[i]->move(x, y);
                } else if (table[x][y] < 0) {
                    powerups *temp = findPowerUp(vectorItems, nrItems, x, y);
                    if (temp != nullptr) {
                        table[x][y] = 3;
                        vectorAgenti[i]->powerup(*temp);
                        vectorAgenti[i]->move(x, y);
                    } else cout << "Return de powerup gresit!\n";
                } else {
                    agent *temp;
                    temp = findAgent(vectorAgenti, nrAgents, x, y);
                    if (temp != nullptr) {
                        while (vectorAgenti[i]->getDOA() && temp->getDOA()) {
                            vectorAgenti[i]->receivingAttack(temp->getAttackingPower());
                            temp->receivingAttack(vectorAgenti[i]->getAttackingPower());
                        }
                    } else cout << "Return de agent gresit!\n";

                    if (vectorAgenti[i]->getDOA()) {
                        table[x][y] = 3;
                        vectorAgenti[i]->move(x, y);
                    } else if (!temp->getDOA()) {
                        table[x][y] = 0;
                    }
                }
            }
        }
    }
    this->afisare(vectorAgenti, vectorItems, nrAgents, nrItems, ++nrRound);
    cout << endl << endl;
    this->afis();
}

void map::simulate(const int nrAgents, const int nrItems) {
    char continuare ;
    int nrRounds = 0;
    agent *vectorAgents[nrAgents];
    powerups *vectorItems[nrItems];
    this->create(vectorAgents, vectorItems, nrAgents, nrItems);
    this->afisare(vectorAgents, vectorItems, nrAgents, nrItems, 0);
    this->afis();
    do {
        nrRounds++;
        cout << "Continuam ?(Y/N)" << '\n';
        bool ok = true;

        do {
            cin >> continuare;
            if (strchr("YyNn", continuare) == nullptr) {
                cout << "\nAti introdus un raspuns gresit!\n";
                cout << "Va rugam introduceti un raspun corect : ";
            } else ok = false;
        } while (ok);

        if (verifExista(vectorAgents, nrAgents) == -1) {
            this->simulateRound(vectorAgents, vectorItems, nrAgents, nrItems, nrRounds);
        } else if (verifExista(vectorAgents, nrAgents) >= 0) {
            int i = verifExista(vectorAgents, nrAgents);
            if (i % 3 == 0) {
                cout << "A castigat teroristul " << i / 3 + 1;
                continuare = 'n';
            } else if (i % 3 == 1) {
                cout << "A castigat counter-teroristul " << i / 3 + 1;
                continuare = 'n';
            } else if (i % 3 == 2) {
                cout << "A castigat mercenarul " << i / 3 + 1;
                continuare = 'n';
            }
        } else if (verifExista(vectorAgents, nrAgents) == -2) {
            cout << "Nu se mai poate simula!\nNu mai exista agenti in viata!\nLa revedere!\n";
        }
    } while (continuare == 'Y' or continuare == 'y');
    cout << endl;
}
