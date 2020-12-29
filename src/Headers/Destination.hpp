#ifndef Destination_H_
#define Destination_H_

#include <list>
#include <string>

using namespace std;

class Destination {

    string ville_depart, ville_arrivee;
    
    public :
        Destination(const char* const, const char* const);
        friend ostream& operator <<(ostream &, Destination &);
};

#endif