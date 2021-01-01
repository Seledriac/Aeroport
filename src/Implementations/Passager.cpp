// Auteurs : Tom BOUMBA et Antoine Zaug, promo L3 info à la FST de l'université de Limoges

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
#include <fstream>

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

void Passager::AfficherListeVols(Destination* dest, Date* date) {
    cout << endl;
    list<Vol*> vols = Vol::getVols();
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        if((dest != NULL 
            && date != NULL
            && (*it)->getDate() < date
            && (*it)->getDestination()->getVille_depart() == dest->getVille_depart() 
            && (*it)->getDestination()->getVille_arrivee() == dest->getVille_arrivee())
            || (dest != NULL
            && date == NULL
            && (*it)->getDestination()->getVille_depart() == dest->getVille_depart() 
            && (*it)->getDestination()->getVille_arrivee() == dest->getVille_arrivee())
            || (dest == NULL
            && date != NULL
            && (*it)->getDate() < date)
            || (dest == NULL 
            && date == NULL)){
            (*it)->afficherVol();
        }
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

string Passager::getTitre() {
    return titre;
}

int Passager::getAge() {
    return age;
}

string Passager::getMot_de_passe() {
    return mot_de_passe;
}

void Passager::afficherPassager() {
    cout << num_passeport << " => " << prenom << " " << nom << " : " << titre << ", " << age << " ans" << endl;
}

void Passager::chargerPassagers() {
    fstream fichier_passagers;
	fichier_passagers.open("./src/donnees/Passagers.txt", ios::in);
	string line;
    if(fichier_passagers.is_open()) {
        while(getline(fichier_passagers, line)) { // Une ligne par administrateur
            string infos[6];
            size_t start;
            size_t end = 0;
            int i = 0;
            while((start = line.find_first_not_of(":", end)) != std::string::npos) {
                end = line.find(":", start);
                infos[i] = line.substr(start, end - start);
                i++;
            }
            passagers.push_back(new Passager(infos[0], infos[1], infos[2], infos[3], infos[4], stoi(infos[5])));
        }
    } else {
        cout << "Erreur lors de l'ouverture du fichier des administrateurs";
    }
    fichier_passagers.close();
}