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

void Administrateur::ajouterVol(int nb_de_places, int prix, string ville_depart, string ville_destination, int annee, int mois, int jour, int heures, int minutes){
    new Vol(nb_de_places, prix, ville_depart, ville_destination, annee, mois, jour, heures, minutes);
}

void ajouterPassager(string nom, string prenom, string titre, string num_passeport, int age) {
    new Passager(nom, prenom, titre, num_passeport, age);
}

void Administrateur::AfficherListeVols(){
    cout << endl;
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        (*it)->afficherVol();
    }
    cout << endl;
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

void Administrateur::chargerAdministrateurs() {
    // tests
    string identifiant = "tom";
    string mdp = "pass";
    administrateurs.push_back(new Administrateur(identifiant, mdp));
    identifiant = "antoine";
    mdp = "pass";
    administrateurs.push_back(new Administrateur(identifiant, mdp));
    // connexion bdd (tous les administrateurs sont chargés vers la liste "administrateur")
}

string Administrateur::getIdentifiant() {
    return identifiant;
}
string Administrateur::getMot_de_passe() {
    return mot_de_passe;
}