// Auteurs : Tom BOUMBA et Antoine Zaug, promo L3 info à la FST de l'université de Limoges

#ifndef Vol_H_
#include "../Headers/Vol.hpp"
#endif

#include <iostream>
#include <fstream>

list<Vol*> Vol::vols;

Vol::Vol(int nb_places, int prix, Destination dest, Date date) {
    num_vol = vols.size() + 1;
    this->nb_places = nb_places;
    this->prix = prix;
    this->dest = new Destination(dest.getVille_depart(), dest.getVille_arrivee());
    this->date = new Date(date.getAnnee(), date.getMois(), date.getJour(), date.getHeures(), date.getMinutes());
    vols.push_back(this);
}

Vol::~Vol() {
    delete dest;
    delete date;
}

Vol* Vol::getVol(int num_vol) {
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        if((*it)->num_vol == num_vol) {
            return (*it);
        }  
    }
    return NULL;
}

list<Vol*> Vol::getVols() {
    list<Vol*> liste;
    for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
        liste.push_back(*it);
    }
    return liste;
}

int Vol::getNum_vol() {
    return num_vol;
}

int Vol::getNb_places() {
    return nb_places;
}

void Vol::setNbPlaces(int nb_places) {
    this->nb_places = nb_places;
}

int Vol::getPrix() {
    return prix;
}

Destination* Vol::getDestination() {
    return dest;
}

Date* Vol::getDate() {
    return date;
}

void Vol::setDate(Date &date) {
    this->date->setAnnee(date.getAnnee());
    this->date->setMois(date.getMois());
    this->date->setJour(date.getJour());
    this->date->setHeures(date.getHeures());
    this->date->setMinutes(date.getMinutes());
}

void Vol::afficherVol() {
    cout << num_vol << " => " << dest->to_string() <<  " - Date : " << date->to_string() << " - Prix : " << prix << " - Nombre de places restantes : " << nb_places << endl;
}

void Vol::chargerVols() {
    fstream fichier_vols;
	fichier_vols.open("./src/donnees/Vols.txt", ios::in);
	string line;
    if(fichier_vols.is_open()) {
        while(getline(fichier_vols, line)) { // Une ligne par vol
            string infos[8];
            size_t start;
            size_t end = 0;
            int i = 0;
            while((start = line.find_first_not_of(":", end)) != std::string::npos) {
                end = line.find(":", start);
                infos[i] = line.substr(start, end - start);
                i++;
            }
            new Vol(stoi(infos[0]), stoi(infos[1]), *(new Destination(infos[2], infos[3])), *(new Date(stoi(infos[4]), stoi(infos[5]), stoi(infos[6]), stoi(infos[7]), stoi(infos[8]))));
        }
    } else {
        cout << "Erreur lors de l'ouverture du fichier des vols";
    }
    fichier_vols.close();
}