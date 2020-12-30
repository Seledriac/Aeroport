#ifndef Destination_H_
#include "../Headers/Destination.hpp"
#endif

#include <iostream>
#include <sstream>

Destination::Destination(string ville_depart, string ville_arrivee) {
    this->ville_depart = ville_depart;
    this->ville_arrivee = ville_arrivee;
}

string Destination::to_string() const {
    stringstream ss;
    ss << ville_depart << " -> " << ville_arrivee;
    return ss.str(); 
}