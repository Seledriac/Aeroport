#ifndef Destination_H_
#include <Destination.hpp>
#endif

#include <iostream>

Destination::Destination(const char* const ville_depart, const char* const ville_arrivee) {
    this->ville_depart = ville_depart;
    this->ville_arrivee = ville_arrivee;
}

inline ostream& operator <<(ostream &os, Destination &dest) {
    return os << dest.ville_depart << " -> " << dest.ville_arrivee;
}