// Auteurs : Tom BOUMBA et Antoine Zaug, promo L3 info à la FST de l'université de Limoges

#ifndef Reservation_H_
#include "../Headers/Reservation.hpp"
#endif

#include <iostream>
#include <fstream>

list<Reservation*> Reservation::reservations;

Reservation::Reservation(Passager* passager, Vol* vol, bool confirmation) {
    num_passeport = passager->getNum_passeport();
    num_vol = vol->getNum_vol();
    num_reservation = reservations.size() + 1;
    this->confirmation = confirmation;
    reservations.push_back(this);
}

void Reservation::Confirmer() {
    if(!confirmation) {
        confirmation = true;
        Vol::getVol(num_vol)->setNbPlaces(Vol::getVol(num_vol)->getNb_places() - 1);
    }
}

void Reservation::Annuler() {
    if(confirmation) {
        confirmation = false;    
        Vol::getVol(num_vol)->setNbPlaces(Vol::getVol(num_vol)->getNb_places() + 1);
    }
}

int Reservation::EstConfirmee() {
    if(confirmation)
        return 1;
    return 0;
}

Reservation* Reservation::getReservation(int num_reservation) {
    for(list<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        if((*it)->num_reservation == num_reservation) {
            return (*it);
        }  
    }
    return NULL;
}

list<Reservation*> Reservation::getReservations() {
    list<Reservation*> liste;
    for(list<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        liste.push_back(*it);
    }
    return liste;
}

void Reservation::afficherReservation() {
    cout << num_reservation << " => Passager : " << num_passeport << "; Vol : " << num_vol << "; Confirmation : " << confirmation << endl;
}

string Reservation::getNum_passeport() {
    return num_passeport;
}

int Reservation::getNum_reservation() {
    return num_reservation;
}

int Reservation::getNum_vol() {
    return num_vol;
}

void Reservation::chargerReservations() {
    fstream fichier_vols;
	fichier_vols.open("./src/donnees/Reservations.txt", ios::in);
	string line;
    if(fichier_vols.is_open()) {
        while(getline(fichier_vols, line)) { // Une ligne par reservation
            string infos[3];
            size_t start;
            size_t end = 0;
            int i = 0;
            while((start = line.find_first_not_of(":", end)) != std::string::npos) {
                end = line.find(":", start);
                infos[i] = line.substr(start, end - start);
                i++;
            }        
            new Reservation(Passager::getPassager(infos[0]), Vol::getVol(stoi(infos[1])), (bool)stoi(infos[2]));
        }
    } else {
        cout << "Erreur lors de l'ouverture du fichier des reservations";
    }
    fichier_vols.close();
}

bool Reservation::reservationExistante(string num_passeport, int num_vol) {
    bool existe =false;
    for(list<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
        if((*it)->num_passeport == num_passeport && (*it)->num_vol == num_vol) {
            existe = true;
        }  
    }
    return existe;
}

