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

    list<Administrateur*> administrateurs; // contient toutes les instances de la classe Administrateur

    string identifiant, mot_de_passe;
    bool connected;

    public :
        Administrateur(const char* const, const char* const);
        bool seConnecter();
        void ajouterVol(int, int, int, Destination, Date);
        void ajouterPassager(const char* const, const char* const, const char* const, const char* const, int);
        void AfficherListeVols() const;
        void AfficherListePassagers() const;
        void ajouterReservation(Passager*, Vol*);
        void ajouterDestination(const char* const, const char* const);
};

#endif