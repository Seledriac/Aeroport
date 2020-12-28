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

    list<Vol*> vols;

    vector<Reservation*> reservations;

    int num_vol, nb_places, prix;
    Destination dest;
    Date date;

    public :
        Vol(int, int, int, Destination, Date);
};

#ifndef Reservation_H_
#include <Reservation.hpp>
#endif

#endif