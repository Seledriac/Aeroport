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
        void ajouterVol(int, int, string, string, int, int, int, int, int);
        void ajouterPassager(string, string, string, string, int);
        void AfficherListeVols();
        void AfficherListePassagers();
        void ajouterReservation(Passager*, Vol*);
        void ModifierDateVol(int, int, int, int, int, int);
        bool ExistenceVol(int);
        static void chargerAdministrateurs();
        string getIdentifiant();
        string getMot_de_passe();
};

#endif