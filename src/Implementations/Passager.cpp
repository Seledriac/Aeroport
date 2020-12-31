#ifndef Passager_H_
#include "../Headers/Passager.hpp"
#endif

#ifndef Reservation_H_
#include "../Headers/Reservation.hpp"
#endif

#ifndef Vol_H_
#include "../Headers/Vol.hpp"
#endif

#include <iostream>

list<Passager*> Passager::passagers;

Passager::Passager(string nom, string prenom, string titre, string num_passeport, string mot_de_passe, int age) {    
    this->nom = nom;
    this->prenom = prenom;
    this->titre = titre;
    this->num_passeport = num_passeport;
    this->mot_de_passe = mot_de_passe;
    this->age = age;
}

Passager* Passager::getPassager(string num_passeport, string mot_de_passe) {
    Passager* passager = NULL;
    for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
        if((*it)->num_passeport == num_passeport && (*it)->mot_de_passe == mot_de_passe) {
            passager = *it;
            break;
        }
    }
    return passager;
}

void Passager::nouveauPassager(string nom, string prenom, string titre, string num_passeport, string mot_de_passe, int age) {
    passagers.push_back(new Passager(nom, prenom, titre, num_passeport, mot_de_passe, age));
}


bool Passager::ReserverVol(int num_vol) {
    bool a_pu_reserver = false;
    if(Vol::getVol(num_vol)->getNb_places() > 0) {        
        reservations.push_back(new Reservation(this, Vol::getVol(num_vol)));
        a_pu_reserver = true;
    }
    return a_pu_reserver;
}

void Passager::ConfirmerReservation(int num_reservation) {
    Reservation::getReservation(num_reservation)->Confirmer();
}

void Passager::AnnulerReservation(int num_reservation) {
    Reservation::getReservation(num_reservation)->Annuler();
}

void Passager::AfficherListeVols() {
    cout << endl;
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        (*it)->afficherVol();
    }
    cout << endl;
}

void Passager::AfficherListeReservations() {
    cout << endl;
    for(vector<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        (*it)->afficherReservation();
    }
    cout << endl;
}

bool Passager::ExistenceVol(int num_vol) {
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

bool Passager::ExistenceReservation(int num_reservation) {
    bool reservation_existe = false;
    for(vector<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        if((*it)->getNum_reservation() == num_reservation) {
            reservation_existe = true;
            break;
        }
    }
    return reservation_existe;
}

Passager* Passager::getPassager(string num_passeport) {
    for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
        if((*it)->num_passeport == num_passeport) {
            return (*it);
        }  
    }
    return NULL;
}

list<Passager*> Passager::getPassagers() {
    list<Passager*> liste;
    for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
        liste.push_back(*it);
    }
    return liste;
}

string Passager::getNum_passeport() {
    return num_passeport;
}

string Passager::getPrenom() {
    return prenom;
}

string Passager::getNom() {
    return nom;
}

void Passager::afficherPassager() {
    cout << num_passeport << " => " << prenom << " " << nom << " : " << titre << ", " << age << " ans" << endl;
}

void Passager::chargerPassagers() {
    // tests
    string num_passeport = "0FE";
    string mdp = "pass";
    string nom = "boumba";
    string prenom = "tom";
    string titre = "Homme";
    int age = 20;
    passagers.push_back(new Passager(nom, prenom, titre, num_passeport, mdp, age));
    num_passeport = "A2F";
    mdp = "pass";
    nom = "zaug";
    prenom = "antoine";
    titre = "Homme";
    age = 20;
    passagers.push_back(new Passager(nom, prenom, titre, num_passeport, mdp, age));
    // connexion bdd (tous les passagers sont chargés vers la liste "passagers")
}