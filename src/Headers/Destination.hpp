#ifndef Destination_H_
#define Destination_H_

#include <list>

using namespace std;

class Destination {

    list<Destination*> destinations;

    string ville_depart, ville_arrivee;
    
    public :
        Destination(const char* const, const char* const);
};

#endif