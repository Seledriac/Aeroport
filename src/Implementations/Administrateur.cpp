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
    this->connected = false;
    this->administrateurs.push_back(this);
}

bool Administrateur::seConnecter(){

}

void Administrateur::ajouterVol(int num_vol, int nb_de_places, int prix, Destination destination, Date date){
    list<Vol*> vols = Vol::getVols();
    Vol nouveau_vol = Vol(num_vol,nb_de_places,prix,destination,date);
    vols.push_back(nouveau_vol);
}

void ajouterPassager(const char* const, const char* const, const char* const, const char* const, int){
    // getter Passager à mettre 
}

void Administrateur:: AfficherListeVols(){
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        (*it)->afficherVol();
    }
}

void Administrateur::AfficherListePassagers(){
    list<Passager*> passagers = Passager::getPassager();
    for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
        (*it)->afficherPassager();
    } 
}

void ajouterReservation(Passager*, Vol*){
    
}

void ajouterDestination(const char* const, const char* const){

}

void ModifierHeureVol(Vol *){

}

void ModifierDateVol(Vol *){

}

bool ExistenceVol(Vol *){

}

