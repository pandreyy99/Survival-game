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

map::map(const int line, const int column) {
    lines = line;
    columns = column;
    table = new int *[lines];
    for (int i = 0; i < lines; i++)
        table[i] = new int[columns];
    for (int i = 0; i < lines; i++)
        for (int j = 0; j < columns; j++)
            table[i][j] = 0;
}

map::~map() {
    lines = columns = 0;
    for (int i = 0; i < columns; i++)
        delete[] table[i];
    delete table;
}

const int whichAgent(agent **vectorAgents, const int nrAgents, const int x, const int y) {
    for (int i = 0; i < nrAgents; i++)
        if (vectorAgents[i]->getDOA() == true)
            if (vectorAgents[i]->getPosition().first == x)
                if (vectorAgents[i]->getPosition().second == y) {
                    return i;
                }
    return -1;
}

const int whichPowerUp(powerups **vectorItems, const int nrItems, const int x, const int y) {
    for (int i = 0; i < nrItems; i++)
        if (vectorItems[i]->getPowerUpPosition().first == x and vectorItems[i]->getPowerUpPosition().second == y)
            return i;
    return -1;
}

void map::afisare(agent **vectorAgents, powerups **vectorItems,
                  const int nrAgents, const int nrItems, const int nrRound) {
    fstream out("C:\\Users\\Andrei\\Documents\\GitHub\\Survival-game\\afisare.txt", fstream::out | fstream::app);
    string temp;
    int converter;
    out << '\n' << "Configuratia hartii in cadrul rundei " << nrRound << " : " << '\n';

    for (int i = 0; i < 3 * (columns - 1); i++)
        out << "- ";
    out << endl;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            out << "| ";
            if (table[i][j] == -3) {
                temp = "H";
                converter = whichPowerUp(vectorItems, nrItems, i, j);
                if (whichPowerUp(vectorItems, nrItems, i, j) != -1) {
                    converter = converter / 3;
                    converter++;
                    temp.append(to_string(converter));
                    temp.append(" ");
                    out << temp;
                } else out << " G ";
            } else if (table[i][j] == -2) {
                temp = "F";
                converter = whichPowerUp(vectorItems, nrItems, i, j);
                if (whichPowerUp(vectorItems, nrItems, i, j) != -1) {
                    converter = converter / 3;
                    converter++;
                    temp.append(to_string(converter));
                    temp.append(" ");
                    out << temp;
                } else out << " G ";
            } else if (table[i][j] == -1) {
                temp = "A";
                converter = whichPowerUp(vectorItems, nrItems, i, j);
                if (whichPowerUp(vectorItems, nrItems, i, j) != -1) {
                    converter = converter / 3;
                    converter++;
                    temp.append(to_string(converter));
                    temp.append(" ");
                    out << temp;
                } else out << " G ";
            } else if (table[i][j] == 0) out << "   ";
            else if (table[i][j] == 1) {
                temp = "T";
                converter = whichAgent(vectorAgents, nrAgents, i, j);
                if (whichAgent(vectorAgents, nrAgents, i, j) != -1) {
                    converter = converter / 3;
                    converter++;
                    temp.append(to_string(converter));
                    temp.append(" ");
                    out << temp;
                } else out << " G ";
            } else if (table[i][j] == 2) {
                temp = "CT";
                converter = whichAgent(vectorAgents, nrAgents, i, j);
                if (whichAgent(vectorAgents, nrAgents, i, j) != -1) {
                    converter = converter / 3;
                    converter++;
                    temp.append(to_string(converter));
                    temp.append(" ");
                    out << temp;
                } else out << " G ";
            } else {
                temp = "M";
                converter = whichAgent(vectorAgents, nrAgents, i, j);
                if (whichAgent(vectorAgents, nrAgents, i, j) != -1) {
                    converter = converter / 3;
                    converter++;
                    temp.append(to_string(converter));
                    temp.append(" ");
                    out << temp;
                } else out << " G ";
            }
        }
        out << " |";
        out << '\n';
    }
    for (int i = 0; i < 3 * (columns - 1); i++)
        out << "- ";
}

void map::create(agent **vectorAgenti, powerups **vectorItems, const int nrAgents, const int nrItems) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution;
    int x, y;
    bool ok;
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

std::pair<int, int> map::find(agent *other, const int ok) {
    pair<int, int> agentPosition = other->getPosition(), nextPosition;
    int x = agentPosition.first, y = agentPosition.second, maxim = -1;
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
                else goto N;
            }
        }
            /// Caz 2 : N
        N :
        if (x - i >= 0) {
            if (table[x - i][y] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x - i, y);
                if (maxim == ok) return nextPosition;
            } else if (table[x - i][y] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x - i, y);
                if (maxim == ok) return nextPosition;
                else goto E;
            }
        }
            /// Caz 3 : E
        E :
        if (y + i < columns) {
            if (table[x][y + i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x, y + i);
                if (maxim == ok) return nextPosition;
            } else if (table[x][y + i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x, y + i);
                if (maxim == ok) return nextPosition;
                else goto V;
            }
        }
            /// Caz 4 : V
        V :
        if (y - i >= 0) {
            if (table[x][y - i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x, y - i);
                if (maxim == ok) return nextPosition;
            } else if (table[x][y - i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x, y - i);
                if (maxim == ok) return nextPosition;
                else goto NV;
            }
        }
            /// Caz 5 : N-V
        NV :
        if (x - i >= 0 and y - i >= 0) {
            if (table[x - i][y - i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x - i, y - i);
                if (maxim == ok) return nextPosition;
            } else if (table[x - i][y - i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x - i, y - i);
                if (maxim == ok) return nextPosition;
                else goto NE;
            }
        }
            /// Caz 6 : N-E
        NE :
        if (x - i >= 0 and y + i < columns) {
            if (table[x - i][y + i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x - i, y + i);
                if (maxim == ok) return nextPosition;
            } else if (table[x - i][y + i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x - i, y + i);
                if (maxim == ok) return nextPosition;
                else goto SE;
            }
        }
            /// Caz 7 : S-E
        SE :
        if (x + i < lines and y + i < columns) {
            if (table[x + i][y + i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x + i, y + i);
                if (maxim == ok) return nextPosition;
            } else if (table[x + i][y + i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x + i, y + i);
                if (maxim == ok) return nextPosition;
                else goto SV;
            }
        }
            /// Caz 8 : S-V
        SV :
        if (x + i < lines and y - i >= 0) {
            if (table[x + i][y - i] < 0) {
                maxim = max(maxim, 1);
                nextPosition = make_pair(x + i, y - i);
                if (maxim == ok) return nextPosition;
            } else if (table[x + i][y - i] > 0) {
                maxim = max(maxim, 2);
                nextPosition = make_pair(x + i, y - i);
                if (maxim == ok) return nextPosition;
                else goto EXIT;
            }
        }
    }
    /// daca nu gasim ce era prioritar ,  verificam daca am gasit ceva de o prioritate mai mica
    /// si returnam ultima astfel de pozitie
    EXIT :
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

agent *findAgent(agent **vectorAgenti, const int nrAgents, const int x, const int y) {
    for (int i = 0; i < nrAgents; i++) {
        pair<int, int> agentPosition = vectorAgenti[i]->getPosition();
        if ((agentPosition.first == x) and (agentPosition.second == y)) return vectorAgenti[i];
    }
    return nullptr;
}

powerups *findPowerUp(powerups **vectorItems, const int nrItems, const int x, const int y) {
    for (int i = 0; i < nrItems; i++) {
        pair<int, int> itemPosition = vectorItems[i]->getPowerUpPosition();
        if ((itemPosition.first == x) and (itemPosition.second == y)) return vectorItems[i];
    }
    return nullptr;
}

const int verifExista(agent **vectorAgenti, int nrAgents) {
    int nrAlive = 0, poz;
    for (int i = 0; i < nrAgents && nrAlive <= 2; i++)
        if (vectorAgenti[i]->getDOA()) {
            nrAlive++;
            poz = i;
        }
    if (nrAlive == 1) return poz;
    if (nrAlive > 1) return -1;
    return -2;
}

void map::simulateRound(agent **vectorAgenti, powerups **vectorItems,
                        const int nrAgents, const int nrItems, const int nrRound) {
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
                        if (vectorAgenti[i]->getDOA()) {
                            table[x][y] = 1;
                            vectorAgenti[i]->move(x, y);
                            temp->move(-1, -1);
                        } else {
                            vectorAgenti[i]->move(-1, -1);
                            if (!temp->getDOA()) {
                                temp->move(-1, -1);
                                table[x][y] = 0;
                            }
                        }
                    } else cout << "Return de agent gresit!\n";
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
                        if (vectorAgenti[i]->getDOA()) {
                            table[x][y] = 2;
                            vectorAgenti[i]->move(x, y);
                        } else {
                            vectorAgenti[i]->move(-1, -1);
                            if (!temp->getDOA()) {
                                temp->move(-1, -1);
                                table[x][y] = 0;
                            }
                        }
                    } else cout << "Return de agent gresit!\n";
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
                        if (vectorAgenti[i]->getDOA()) {
                            table[x][y] = 3;
                            vectorAgenti[i]->move(x, y);
                        } else {
                            vectorAgenti[i]->move(-1, -1);
                            if (!temp->getDOA()) {
                                temp->move(-1, -1);
                                table[x][y] = 0;
                            }
                        }
                    } else cout << "Return de agent gresit!\n";
                }
            }
        }
    }
}

void map::simulate(const int nrAgents, const int nrItems) {
    char continuare;
    int nrRounds = 0;
    agent *vectorAgents[nrAgents];
    powerups *vectorItems[nrItems];
    this->create(vectorAgents, vectorItems, nrAgents, nrItems);
    this->afisare(vectorAgents, vectorItems, nrAgents, nrItems, 0);
    do {
        cout << "Menu : \n";
        cout << "1.Simulare completa joc\n";
        cout << "2.Simulare runda\n";
        cout << "N/n - Iesire\n";
        cin >> continuare;
        cout << '\n';

        switch (continuare) {
            case '1' : {
                do {
                    this->simulateRound(vectorAgents, vectorItems, nrAgents, nrItems, ++nrRounds);
                } while (verifExista(vectorAgents, nrAgents) == -1);
                cout << '\n';
                int final = verifExista(vectorAgents, nrAgents);
                if (final == -2) {
                    continuare = 'n';
                    cout << "Nu se mai poate simula!\nNu mai exista agenti in viata!\nE egalitate!\nLa revedere!\n";
                    this->afisare(vectorAgents, vectorItems, nrAgents, nrItems, nrRounds);
                } else if (final >= 0) {
                    if (final % 3 == 0) {
                        cout << "A castigat teroristul " << final / 3 + 1;
                        continuare = 'n';
                    } else if (final % 3 == 1) {
                        cout << "A castigat counter-teroristul " << final / 3 + 1;
                        continuare = 'n';
                    } else if (final % 3 == 2) {
                        cout << "A castigat mercenarul " << final / 3 + 1;
                        continuare = 'n';
                    }
                    this->afisare(vectorAgents, vectorItems, nrAgents, nrItems, nrRounds);
                }
                break;
            }
            case '2' : {
                nrRounds++;
                if (verifExista(vectorAgents, nrAgents) == -1) {
                    this->simulateRound(vectorAgents, vectorItems, nrAgents, nrItems, nrRounds);
                    this->afisare(vectorAgents, vectorItems, nrAgents, nrItems, nrRounds);
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
                    continuare = 'n';
                    cout << "Nu se mai poate simula!\nNu mai exista agenti in viata!\nE egalitate!\nLa revedere!\n";
                }
                cout << endl;
                break;
            }
            default :
                cout << "Ati introdus un raspuns gresit!\nVa rugam introduceti unul corect!\n";
                break;
        }

    } while (continuare == '1' or continuare == '2');
}