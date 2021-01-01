// Auteurs : Tom BOUMBA et Antoine Zaug, promo L3 info à la FST de l'université de Limoges

#ifndef Administrateur_H_
#include "../Headers/Administrateur.hpp"
#endif

#ifndef Vol_H_
#include "../Headers/Vol.hpp"
#endif

#include <iostream>
#include <fstream>

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

void Administrateur::AfficherListeVols(Destination* dest, Date* date){
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
            && date == NULL)) {
            (*it)->afficherVol();
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

bool Administrateur::ExistenceReservation(int num_reservation){
    return Reservation::getReservation(num_reservation) != NULL;
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
    fstream fichier_admins;
	fichier_admins.open("./src/donnees/Administrateurs.txt", ios::in);
	string line;
    if(fichier_admins.is_open()) {
        while(getline(fichier_admins, line)) { // Une ligne par administrateur
            string infos[2];
            size_t start;
            size_t end = 0;
            int i = 0;
            while((start = line.find_first_not_of(":", end)) != std::string::npos) {
                end = line.find(":", start);
                infos[i] = line.substr(start, end - start);
                i++;
            }
            administrateurs.push_back(new Administrateur(infos[0], infos[1]));
        }
    } else {
        cout << "Erreur lors de l'ouverture du fichier des administrateurs";
    }
    fichier_admins.close();
}

list<Administrateur*> Administrateur::getAdministrateurs() {
    list<Administrateur*> liste;
    for(list<Administrateur*>::const_iterator it = administrateurs.begin(); it != administrateurs.end(); it++) {
        liste.push_back(*it);
    }
    return liste;
}

string Administrateur::getIdentifiant() {
    return identifiant;
}
string Administrateur::getMot_de_passe() {
    return mot_de_passe;
}