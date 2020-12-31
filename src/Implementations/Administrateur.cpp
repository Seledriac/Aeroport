#ifndef Administrateur_H_
#include "../Headers/Administrateur.hpp"
#endif

#ifndef Vol_H_
#include "../Headers/Vol.hpp"
#endif

#include <iostream>

list<Administrateur*> Administrateur::administrateurs;

Administrateur::Administrateur(string identifiant, string MotDePasse) {    
    this->identifiant = identifiant;
    this->mot_de_passe = MotDePasse;
}

Administrateur* Administrateur::getAdministrateur(string identifiant, string mot_de_passe) {
    Administrateur* admin = NULL;
    for(list<Administrateur*>::const_iterator it = administrateurs.begin(); it != administrateurs.end(); it++) {
        if((*it)->identifiant == identifiant && (*it)->mot_de_passe == mot_de_passe) {
            admin = *it;
            break;
        }
    }
    return admin;
}

void Administrateur::ajouterVol(int nb_de_places, int prix, Destination dest, Date date){
    new Vol(nb_de_places, prix, dest, date);
}

void Administrateur::ajouterPassager(string nom, string prenom, string titre, string num_passeport, string mot_de_passe, int age) {
    Passager::nouveauPassager(nom, prenom, titre, num_passeport, mot_de_passe, age);
}

void Administrateur::AfficherListeVols(Destination* dest = NULL, Date* date = NULL){
    cout << endl;
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        if(dest == NULL && date == NULL) {
            (*it)->afficherVol();
        } 
        if(dest != NULL
            && date == NULL
            && (*it)->getDestination()->getVille_depart() == dest->getVille_depart() 
            && (*it)->getDestination()->getVille_arrivee() == dest->getVille_arrivee()) {
            
        } else if(dest == NULL
            && date != NULL
            && (*it)->getDate()->getAnnee() == date->getAnnee() 
            && (*it)->getDate()->getMois() == date->getMois() 
            && (*it)->getDate()->getJour() == date->getJour() 
            && (*it)->getDate()->getHeures() == date->getHeures()
            && (*it)->getDate()->getMinutes() == date->getMinutes() {            
        } else {
            ;
        }    
    }
    cout << endl;
}

void Administrateur::AfficherListePassagers(){
    cout << endl;
    list<Passager*> passagers = Passager::getPassagers();
    for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
        (*it)->afficherPassager();
    } 
    cout << endl;
}

void Administrateur::AfficherListeReservations(int num_vol){
    cout << endl;
    list<Reservation*> reservations = Reservation::getReservations();
    for(list<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        if((*it)->getNum_vol() == num_vol || num_vol == 0)
            (*it)->afficherReservation();
    } 
    cout << endl;
}

bool Administrateur::ajouterReservation(Passager* passager, Vol* vol){    
    return passager->ReserverVol(vol->getNum_vol());
}

void Administrateur::ModifierDateVol(int num_vol, Date &date){
    Vol::getVol(num_vol)->setDate(date);
}

bool Administrateur::ExistenceVol(int num_vol){
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

bool Administrateur::ExistencePassager(string num_passeport){
    bool passager_existe = false;
    list<Passager*> passagers = Passager::getPassagers();
    for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
        if((*it)->getNum_passeport() == num_passeport) {
            passager_existe = true;
            break;
        }            
    }
    return passager_existe;
}


void Administrateur::chargerAdministrateurs() {
    // tests
    string identifiant = "tom";
    string mdp = "pass";
    administrateurs.push_back(new Administrateur(identifiant, mdp));
    string identifiant_2 = "antoine";
    string mdp_2 = "pass";
    administrateurs.push_back(new Administrateur(identifiant_2, mdp_2));
    // connexion bdd (tous les administrateurs sont chargés vers la liste "administrateurs")
}

string Administrateur::getIdentifiant() {
    return identifiant;
}
string Administrateur::getMot_de_passe() {
    return mot_de_passe;
}