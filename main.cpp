#include <iostream>
#include "cmake-build-debug/CMakeFiles/map.h"

using namespace std ;

int main() {
   int nrAgents , nrItems , lines , columns ;

    cout << "LET THE GAME BEGIN !" << '\n' << "Introduceti nr de linii : " ;
    cin >> lines ;
    cout << '\n' << "Nr de coloane : " ;
    cin >> columns ;
    map MAP( lines , columns ) ;
    cout << '\n' << "Acum introduceti nr de agenti : " ;
    cin >> nrAgents ;
    if( nrAgents < 21 ) {
        cout << "Ati introdus un nr gresit de agenti! La revedere! " ;
        exit(1);
    }
    cout << "...Si nr de iteme : " ;
    cin >> nrItems ;
    cout << "Simulare inceputa!" << '\n' << '\n';
    MAP.simulate( nrAgents , nrItems );
    return 0;
}