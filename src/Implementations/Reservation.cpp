#ifndef Reservation_H_
#define Reservation_H_

#ifndef Passager_H_
#include <Passager.hpp>
#endif

#ifndef Vol_H_
#include <Vol.hpp>
#endif

class Reservation {

    list<Reservation*> reservations;

    string num_passeport;
    int num_reservation;
    int num_vol;
    bool confirmation;

    public :
        Reservation(Passager*, Vol*);
        bool Confirmer();
        bool Annuler();
}; 

#endif