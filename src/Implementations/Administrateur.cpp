#ifndef Administrateur_H_
#include <Administrateur.hpp>
#endif

#ifndef Vol_H_
#include <Vol.hpp>
#endif

#include <iostream>

Administrateur::Administrateur(const char *const identifiant, const char *const MotDePasse)
{
    this->identifiant = identifiant;
    this->mot_de_passe = MotDePasse;
    this->administrateurs.push_back(this);
    // connexion bdd
}

inline void Administrateur::ajouterVol(int nb_de_places, int prix, const char* const ville_depart, const char* const ville_destination, int annee, int mois, int jour, int heures, int minutes){
    Vol(nb_de_places, prix, ville_depart, ville_destination, annee, mois, jour, heures, minutes);
}

void ajouterPassager(const char* const nom, const char* const prenom, const char* const titre, const char* const num_passeport, int age) {
    Passager(nom, prenom, titre, num_passeport, age);
}

void Administrateur:: AfficherListeVols(){
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        (*it)->afficherVol();
    }
}

void Administrateur::AfficherListePassagers(){
    list<Passager*> passagers = Passager::getPassagers();
    for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
        (*it)->afficherPassager();
    } 
}

void Administrateur::ajouterReservation(Passager* passager, Vol* vol){
    Reservation(passager, vol);
}

void Administrateur::ModifierDateVol(int num_vol, int annee, int mois, int jour, int heures, int minutes){
    Vol::getVol(num_vol)->setDate(annee, mois, jour, heures, minutes);
}

bool ExistenceVol(int num_vol){
    bool vol_existe = false;
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        if((*it)->getNum_vol() == num_vol) {
            vol_existe = true;
            break;
        }            
    }
    return vol_existe;
}

