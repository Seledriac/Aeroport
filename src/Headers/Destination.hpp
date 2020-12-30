#ifndef Destination_H_
#define Destination_H_

#include <list>
#include <string>
#include <iostream>

using namespace std;

class Destination {

    string ville_depart, ville_arrivee;
    
    public :
        Destination(string, string);
        string to_string() const;
};

#endif