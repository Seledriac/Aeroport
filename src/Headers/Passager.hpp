#ifndef Passager_H_
#define Passager_H_

class Reservation;

#ifndef Destination_H_
#include "Destination.hpp"
#endif

#ifndef Date_H_
#include "Date.hpp"
#endif

#include <vector>

using namespace std;

class Passager {

    static list<Passager*> passagers; // contient toutes les instances de la classe Passager

    vector<Reservation*> reservations;

    string nom, prenom, titre, num_passeport, mot_de_passe;
    int age;

    Passager(string, string, string, string, string, int); // privé car on ne veut pas que l'utilisateur puisse créer des passagers

    public :    
        static Passager* getPassager(string, string);
        static void nouveauPassager(string, string, string, string, string, int);
        bool ReserverVol(int);
        void ConfirmerReservation(int);
        void AnnulerReservation(int);
        void AfficherListeVols(Destination* = NULL, Date* = NULL);
        void AfficherListeReservations();
        bool ExistenceVol(int);
        bool ExistenceReservation(int);
        static list<Passager*> getPassagers();
        string getNum_passeport();
        string getMot_de_passe();
        string getPrenom();
        string getNom();
        string getTitre();
        int getAge();
        static Passager* getPassager(string);
        void afficherPassager();
        static void chargerPassagers();
};

#ifndef Reservation_H_
#include "Reservation.hpp"
#endif

#endif