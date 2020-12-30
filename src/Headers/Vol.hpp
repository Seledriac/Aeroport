#ifndef Vol_H_
#define Vol_H_

class Reservation;

#ifndef Destination_H_
#include "Destination.hpp"
#endif

#ifndef Date_H_
#include "Date.hpp"
#endif

#include "vector"

class Vol {

    static list<Vol*> vols;

    int num_vol, nb_places, prix;
    Destination* dest;
    Date* date;

    public :
        Vol(int, int, string, string, int, int, int, int, int);
        ~Vol();
        static Vol* getVol(int);
        static list<Vol*> getVols();
        int getNum_vol();
        int getNb_places();
        void setNbPlaces(int);
        int getPrix();
        Destination* getDestination();
        Date* getDate();
        void setDate(int, int, int, int, int);
        void afficherVol();
        static void chargerVols();     
};

#ifndef Reservation_H_
#include "Reservation.hpp"
#endif

#endif