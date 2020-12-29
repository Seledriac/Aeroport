#ifndef Administrateur_H_
#define Administrateur_H_

#ifndef Destination_H_
#include <Destination.hpp>
#endif

#ifndef Date_H_
#include <Date.hpp>
#endif

#ifndef Passager_H_
#include <Passager.hpp>
#endif

#ifndef Vol_H_
#include <Vol.hpp>
#endif

class Administrateur {

    static list<Administrateur*> administrateurs; // contient toutes les instances de la classe Administrateur

    string identifiant, mot_de_passe;

    public :
        Administrateur(const char* const, const char* const);
        void ajouterVol(int, int, const char* const, const char* const, int, int, int, int, int);
        void ajouterPassager(const char* const, const char* const, const char* const, const char* const, int);
        void AfficherListeVols();
        void AfficherListePassagers();
        void ajouterReservation(Passager*, Vol*);
        void ModifierDateVol(int, int, int, int, int, int);
        bool ExistenceVol(int);
};

#endif