#ifndef Administrateur_H_
#define Administrateur_H_

#ifndef Destination_H_
#include "Destination.hpp"
#endif

#ifndef Date_H_
#include "Date.hpp"
#endif

#ifndef Passager_H_
#include "Passager.hpp"
#endif

#ifndef Vol_H_
#include "Vol.hpp"
#endif

class Administrateur {

    static list<Administrateur*> administrateurs; // contient toutes les instances de la classe Administrateur

    string identifiant, mot_de_passe;

    Administrateur(string, string); // privé car on ne veut pas que l'utilisateur puisse créer des administrateurs

    public :
        static Administrateur* getAdministrateur(string, string);
        void ajouterVol(int, int, Destination, Date);
        void ajouterPassager(string, string, string, string, string, int);
        bool ajouterReservation(Passager*, Vol*);
        void AfficherListeVols(Destination* = NULL, Date* = NULL);
        void AfficherListePassagers();
        void AfficherListeReservations(int);
        void ModifierDateVol(int, Date &);
        bool ExistenceVol(int);
        bool ExistenceReservation(int);
        bool ExistencePassager(string);
        static void chargerAdministrateurs();
        static list<Administrateur*> getAdministrateurs();
        string getIdentifiant();
        string getMot_de_passe();
};

#endif