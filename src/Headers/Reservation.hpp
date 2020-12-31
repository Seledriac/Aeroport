#ifndef Reservation_H_
#define Reservation_H_

#ifndef Passager_H_
#include "Passager.hpp"
#endif

#ifndef Vol_H_
#include "Vol.hpp"
#endif

class Reservation {

    static list<Reservation*> reservations;

    string num_passeport;
    int num_reservation;
    int num_vol;
    bool confirmation;

    public :
        Reservation(Passager*, Vol*);
        void Confirmer();
        void Annuler();
        static Reservation* getReservation(int);
        static list<Reservation*> getReservations();
        void afficherReservation();
        string getNum_passeport();
        int getNum_reservation();
        int getNum_vol();
        static void chargerReservations();
        static bool reservationExistante(string, int);
}; 

#endif