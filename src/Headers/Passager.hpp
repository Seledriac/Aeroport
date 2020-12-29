#ifndef Passager_H_
#define Passager_H_

class Reservation;

#include <string>
#include <vector>
#include <list>

using namespace std;

class Passager {

    static list<Passager*> passagers; // contient toutes les instances de la classe Passager

    vector<Reservation*> reservations;

    string nom, prenom, titre, num_passeport;
    int age;

    public :
        Passager(const char* const, const char* const, const char* const, const char* const, int);
        void ReserverVol(int);
        void ConfirmerReservation(int);
        void AnnulerReservation(int);
        void AfficherListeVols();
        void AfficherListeReservations();
        bool ExistenceVol(int);
        bool ExistenceReservation(int);
<<<<<<< Updated upstream
        static list<Passager*> getPassagers();
        string getNum_passeport();
=======
        static Passager* getPassager();
        void afficherPassager();
>>>>>>> Stashed changes
};

#ifndef Reservation_H_
#include <Reservation.hpp>
#endif

#endif