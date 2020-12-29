#ifndef Vol_H_
#include <Vol.hpp>
#endif

#include <iostream>

Vol::Vol(int nb_places, int prix, const char* const ville_depart, const char* const ville_arrivee, int annee, int mois, int jour, int heures, int minutes) {
    num_vol = vols.size() + 1;
    this->nb_places = nb_places;
    this->prix = prix;
    this->dest = *(new Destination(ville_depart, ville_arrivee));    
    this->date = *(new Date(annee, mois, jour, heures, minutes));
    vols.push_back(this);
}

Vol* Vol::getVol(int num_vol) {
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        if((*it)->num_vol == num_vol) {
            return (*it);
        }  
    }
    return NULL;
}

list<Vol*> Vol::getVols() {
    list<Vol*> liste;
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        liste.push_back(*it);
    }
    return liste;
}

int Vol::getNum_vol() {
    return num_vol;
}

int Vol::getNb_places() {
    return nb_places;
}

void Vol::setNbPlaces(int nb_places) {
    this->nb_places = nb_places;
}

int Vol::getPrix() {
    return prix;
}

Destination Vol::getDestination() {
    return dest;
}

Date Vol::getDate() {
    return date;
}

void Vol::afficherVol() {
    cout << num_vol << " => " << dest <<  " - Date : " << date << " - Prix : " << prix << " - Nombre de places restantes : " << nb_places;
}