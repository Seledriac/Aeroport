#ifndef Vol_H_
#define Vol_H_

class Reservation;

#ifndef Destination_H_
#include <Destination.hpp>
#endif

#ifndef Date_H_
#include <Date.hpp>
#endif

#include <vector>

class Vol {

    static list<Vol*> vols;

    vector<Reservation*> reservations;

    int num_vol, nb_places, prix;
    Destination dest;
    Date date;

    public :
        Vol(int, int, int, Destination, Date);
        static Vol* getVol(int);
        static list<Vol*> getVols();
        int getNum_vol();
        int getNb_places();
        int getPrix();
        Destination getDestination();
        Date getDate();
        void afficherVol();
};

#ifndef Reservation_H_
#include <Reservation.hpp>
#endif

#endif