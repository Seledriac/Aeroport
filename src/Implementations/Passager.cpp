#ifndef Passager_H_
#include <Passager.hpp>
#endif

#ifndef Reservation_H_
#include <Reservation.hpp>
#endif

#ifndef Vol_H_
#include <Vol.hpp>
#endif

#include <iostream>

Passager::Passager(const char* const nom, const char* const prenom, const char* const titre, const char* const num_passeport, int age) {    
    this->nom = nom;
    this->nom = prenom;
    this->titre = titre;
    this->num_passeport = num_passeport;
    this->age = age;
    passagers.push_back(this);
}

void Passager::ReserverVol(int num_vol) {
    Reservation reservation(this, Vol::getVol(num_vol));
    reservations.push_back(&reservation);
}

void Passager::ConfirmerReservation(int num_reservation) {
    Reservation::getReservation(num_reservation)->Confirmer();
}

void Passager::AnnulerReservation(int num_reservation) {
    Reservation::getReservation(num_reservation)->Annuler();
}

void Passager::AfficherListeVols() {
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        (*it)->afficherVol();
    }
}

void Passager::AfficherListeReservations() {
    for(vector<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        (*it)->afficherReservation();
    }
}

bool Passager::ExistenceVol(int num_vol) {
    bool vol_existe = false;
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        if((*it)->getNum_vol() == num_vol) {
            vol_existe = true;
            break;
        }            
    }
    return vol_existe;
}

bool Passager::ExistenceReservation(int num_reservation) {
    bool reservation_existe = false;
    for(vector<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        if((*it)->getNum_reservation() == num_reservation) {
            reservation_existe = true;
            break;
        }            
    }
    return reservation_existe;
}
