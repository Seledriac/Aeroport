#ifndef Reservation_H_
#include "../Headers/Reservation.hpp"
#endif

#include <iostream>

list<Reservation*> Reservation::reservations;

Reservation::Reservation(Passager* passager, Vol* vol) {
    num_passeport = passager->getNum_passeport();
    num_vol = vol->getNum_vol();
    num_reservation = reservations.size() + 1;
    confirmation = false;
    reservations.push_back(this);
}

void Reservation::Confirmer() {
    if(!confirmation) {
        confirmation = true;
        Vol::getVol(num_vol)->setNbPlaces(Vol::getVol(num_vol)->getNb_places() - 1);
    }
}

void Reservation::Annuler() {
    if(confirmation) {
        confirmation = false;    
        Vol::getVol(num_vol)->setNbPlaces(Vol::getVol(num_vol)->getNb_places() + 1);
    }
}

Reservation* Reservation::getReservation(int num_reservation) {
    for(list<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        if((*it)->num_reservation == num_reservation) {
            return (*it);
        }  
    }
    return NULL;
}

list<Reservation*> Reservation::getReservations() {
    list<Reservation*> liste;
    for(list<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        liste.push_back(*it);
    }
    return liste;
}

void Reservation::afficherReservation() {
    cout << num_reservation << " => Passager : " << num_passeport << "; Vol : " << num_vol << endl;
}

string Reservation::getNum_passeport() {
    return num_passeport;
}

int Reservation::getNum_reservation() {
    return num_reservation;
}

int Reservation::getNum_vol() {
    return num_vol;
}

void Reservation::chargerReservations() {
    
}