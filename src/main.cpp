// Commande de compilation (à exécuter depuis la racine du projet):
// g++ ./src/main.cpp ./src/Implementations/*.cpp -std=c++17

#ifndef Administrateur_H_
#include "Headers/Administrateur.hpp"
#endif

#ifndef Date_H_
#include "Headers/Date.hpp"
#endif

#ifndef Destination_H_
#include "Headers/Destination.hpp"
#endif

#ifndef Passager_H_
#include "Headers/Passager.hpp"
#endif

#ifndef Reservation_H_
#include "Headers/Reservation.hpp"
#endif

#ifndef Vol_H_
#include "Headers/Vol.hpp"
#endif

#include <iostream>
#include <fstream>
#include <ctime>
#include <regex>

void menuPrincipal();
void pageConnexionAdministrateur();
void connexionAdministrateur();
void menuLogicielAdministrateur(Administrateur*);
template <typename T> T* saisieChamp(string, char);
Date* saisieDate();
Destination* saisieDestination();
void ajoutVol(Administrateur*);
void choixAffichageVols(Passager* = NULL, Administrateur* = NULL);
void affichageTousVols(Passager* = NULL, Administrateur* = NULL);
void affichageVolsTrajet(Passager* = NULL, Administrateur* = NULL);
void affichageVolsDate(Passager* = NULL, Administrateur* = NULL);
void affichageVolsCustom(Passager* = NULL, Administrateur* = NULL);
void affichageVol(Passager* = NULL, Administrateur* = NULL);
void modificationDateVol(Administrateur*);
void ajoutPassager(Administrateur*);
void affichageListePassagers(Administrateur*);
void ajouterReservation(Administrateur*);
void choixAffichageReservations(Administrateur*);
void affichageToutesReservations(Administrateur*);
void affichageReservationsVol(Administrateur*);
void affichageReservationsPassager(Administrateur*);
void affichageReservation(Passager* = NULL, Administrateur* = NULL);
void deconnexion(Passager* = NULL, Administrateur* = NULL);
void quitter(bool);
void pageConnexionPassager();
void connexionPassager();
void menuLogicielPassager(Passager*);
void affichageListeVols(Passager*);
void reservationVol(Passager*);
void affichageListeReservationsPassager(Passager*);
void confirmerReservation(Passager*);
void annulerReservation(Passager*);

void menuPrincipal() {  
    cout << "\nBienvenue dans le logiciel de l'Aeroport Paris CDG\n";
    bool recommencer = true;
    while(recommencer) {
        char* saisie = new char;
        if((saisie = saisieChamp<char>("\nEtes-vous administrateur ? (o/n) : ", 'a')) == NULL)
            continue;
        switch(*saisie) {
            case 'o':
                pageConnexionAdministrateur();
                recommencer = false;
                break;
            case 'n':
                pageConnexionPassager();
                recommencer = false;
                break;
            default:
                cout << "\nErreur, veuillez saisir o (pour oui) ou n (pour non)\n";
                break;
        }
    }
}

void pageConnexionAdministrateur() {
    bool recommencer = true;
    while(recommencer) {
        char* saisie = new char;
        if((saisie = saisieChamp<char>("\n\nPage de connexion des administrateurs : \n\n1. Se connecter\n2. Retour au menu principal\n\nChoix : ", 'a')) == NULL)
            continue;
        switch(*saisie) {
            case '1':
                connexionAdministrateur();
                recommencer = false;
                break;
            case '2':
                menuPrincipal();
                recommencer = false;
                break;
            default:
                cout << "\nErreur, veuillez saisir 1 (pour vous connecter) ou 2 (pour retourner au menu principal)\n";
                break;
        }
    }
}

void connexionAdministrateur() {
    string* identifiant;
    if((identifiant = saisieChamp<string>("\nVeuillez saisir votre identifiant : ", 'c')) == NULL) {
        pageConnexionAdministrateur();
        return;
    }
    string* mdp;
    if((mdp = saisieChamp<string>("Veuillez saisir votre mot de passe : ", 'c')) == NULL) {
        pageConnexionAdministrateur();
        return;
    }
    Administrateur* admin = Administrateur::getAdministrateur(*identifiant, *mdp);
    if(admin != NULL) {
        cout << "\nIdentification reussie\n";
        menuLogicielAdministrateur(admin);
        return;
    } else {
        cout << "\nErreur, les identifiants saisis sont incorrects\n";
        pageConnexionAdministrateur();
    }
}

void menuLogicielAdministrateur(Administrateur* admin) {
    bool recommencer = true;
    while(recommencer) {
        char* saisie = new char;
        if((saisie = saisieChamp<char>("\nPage d'administrateur : \n\n1. Ajouter un vol\n2. Afficher une liste de vols\n3. Modifier la date d'un vol\n4. Ajouter un passager\n5. Afficher la liste des passagers\n6. Ajouter une reservation\n7. Afficher une liste des reservations\n8. Se deconnecter\ns. Quitter et sauvegarder\n%. Quitter sans sauvegarder\n\nChoix : ", 'd')) == NULL)
            continue;
        switch(*saisie) {
            case '1':
                ajoutVol(admin);
                recommencer = false;
                break;
            case '2':
                choixAffichageVols(NULL, admin);
                recommencer = false;
                break;
            case '3':
                modificationDateVol(admin);
                recommencer = false;
                break;
            case '4':
                ajoutPassager(admin);
                recommencer = false;
                break;
            case '5':
                affichageListePassagers(admin);
                recommencer = false;
                break;
            case '6':
                ajouterReservation(admin);
                recommencer = false;
                break;
            case '7':
                choixAffichageReservations(admin);
                recommencer = false;
                break;
            case '8':
                deconnexion(NULL, admin);
                recommencer = false;
                break;
            case 's':
                quitter(true);
                recommencer = false;
                break;
            case '%':
                quitter(false);
                recommencer = false;
                break;
            default:
                cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
                break;
        }
    }
}

template <typename T>
T* saisieChamp(string msg, char flag) {    
    cout << msg;
    T* saisie = new T;
    cin >> *saisie;
    switch(flag) {
        case 'a':
            {                
                if(cin.fail()) {
                    cin.clear();
                    cout << "\nErreur, veuillez saisir o (pour oui) ou n (pour non)\n";
                    return NULL;
                } else {
                    return saisie;
                }
            }
        case 'b':
            {
                if(cin.fail()) {
                    cin.clear();
                    cout << "\nErreur, veuillez saisir 1 (pour vous connecter) ou 2 (pour retourner au menu principal)\n";
                    return NULL;
                } else {
                    return saisie;
                }
            }
        case 'c':
            {
                if(cin.fail()) {
                    cin.clear();
                    cout << "\nErreur, saisie invalide\n";
                    return NULL;
                } else {
                    return saisie;
                }
            }
        case 'd':
            {
                if(cin.fail()) {
                    cin.clear();
                    cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
                    return NULL;
                } else {
                    return saisie;
                }
            }
        case 'e':
            {
                if(cin.fail() || *(int*)(saisie) <= 0) {
                    cin.clear();
                    cout << "\nErreur, le champ saisi doit etre un nombre positif\n";
                    return NULL;
                } else {
                    return saisie;
                }
            }
        case 'f':
            {
                bool bon_format = true;
                for(int i = 0; (*(string*)saisie)[i] != '\0'; i++) {
                    if(!isalnum((*(string*)saisie)[i]))
                        bon_format = false;
                }
                if(cin.fail() || !bon_format) {
                    cin.clear();
                    cout << "\nErreur, le format de numero de passeport saisi est invalide\n";
                    return NULL;
                } else {
                    return saisie;
                }
            }
        case 'g':
            {
                if(cin.fail() || *((int*)saisie) < 0) {
                    cin.clear();
                    cout << "\nErreur, le nombre choisi doit etre un nombre positif\n";
                    return NULL;
                } else {
                    return saisie;
                }
            }
        default:
        {
            return NULL;
        }
    }
}

Date* saisieDate() {
    time_t mtn = time(0);
    tm* ltm = localtime(&mtn);
    cout << "\nVeuillez saisir l'annee : ";
    int annee;
    cin >> annee;
    if(cin.fail() || annee < 1900 + ltm->tm_year) {
        cin.clear();
        cout << "\nErreur, l'annee saisie doit etre un nombre superieur a celui de l'annee de la date actuelle\n";
        return NULL;
    }
    cout << "Veuillez saisir le numero du mois : ";
    int mois;
    cin >> mois;
    if(cin.fail() || mois < 1 || mois > 12) {
        cin.clear();
        cout << "\nErreur, le numero de mois saisi doit etre un nombre compris entre 1 et 12\n";
        return NULL;
    } else if(annee == 1900 + ltm->tm_year && mois < 1 + ltm->tm_mon) {        
        cout << "\nErreur, le mois saisi ne peut pas etre inferieur au mois actuel si l'annee est egale\n";        
        return NULL;
    }
    cout << "Veuillez saisir le numero du jour du mois : ";
    int jour;
    cin >> jour;
    if(cin.fail() || jour < 1 || jour > 31) {
        cin.clear();
        cout << "\nErreur, le numero de jour du mois saisi doit etre un nombre compris entre 1 et 31\n";
        return NULL;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour < ltm->tm_mday) {        
        cout << "\nErreur, le numero de jour du mois saisi ne peut pas etre inferieur au jour actuel si l'annee et le mois sont egaux a l'annee et le mois actuels\n";
        return NULL;
    }
    cout << "Veuillez saisir le nombre d'heures : ";
    int heures;
    cin >> heures;
    if(cin.fail() || heures < 0 || heures > 24) {
        cin.clear();
        cout << "\nErreur, le nombre d'heures saisi doit etre un nombre compris entre 0 et 23\n";        
        return NULL;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour == ltm->tm_mday && heures < ltm->tm_hour) {        
        cout << "\nErreur, le nombre d'heures saisi ne peut pas etre inferieur au nombre d'heures actuel si la date est celle d'aujourd'hui\n";
        return NULL;
    }
    cout << "Veuillez saisir le nombre de minutes : ";
    int minutes;
    cin >> minutes;
    if(cin.fail() || minutes < 0 || minutes > 60) {
        cin.clear();
        cout << "\nErreur, le nombre de minutes saisi doit etre un nombre compris entre 0 et 59\n";
        return NULL;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour == ltm->tm_mday && heures == ltm->tm_hour && minutes < ltm->tm_min) {
        cout << "\nErreur, le nombre de minutes saisi ne peut pas etre inferieur au nombre de minutes de l'heure actuelle si la date et est celle d'aujourd'hui et le nombre d'heures est le nombre d'heures actuel\n";
        return NULL;
    }
    return new Date(annee, mois, jour, heures, minutes);
}

Destination* saisieDestination() {
    cout << "\nVeuillez saisir le nom de la ville de depart : ";
    string ville_depart;
    cin >> ville_depart;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        return NULL;
    }
    cout << "Veuillez saisir le nom de la ville de destination : ";
    string ville_destination;
    cin >> ville_destination;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        return NULL;
    }
    return new Destination(ville_depart, ville_destination);
}

void ajoutVol(Administrateur* admin) {
    int* nb_places;
    if((nb_places = saisieChamp<int>("\nVeuillez saisir le nombre de places maximal du vol : ", 'e')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    int* prix;
    if((prix = saisieChamp<int>("Veuillez saisir le prix d'une place dans ce vol : ", 'e')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }    
    cout << "\n ------ TRAJET ------\n";
    Destination* dest;
    if((dest = saisieDestination()) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\n ------ DATE ------\n";
    Date* date;
    if((date = saisieDate()) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    admin->ajouterVol(*nb_places, *prix, *dest, *date);
    cout << "\nAjout du vol fait" << endl;
    menuLogicielAdministrateur(admin);
}

void choixAffichageVols(Passager* passager, Administrateur* admin) {
    bool recommencer = true;
    while(recommencer) {
        char* saisie = new char;
        if((saisie = saisieChamp<char>("\nAu choix : \n\n1. Afficher la liste de tous les vols\n2. Afficher la liste des vols pour un trajet en particulier\n3. Afficher la liste des vols ayant lieu avant une certaine date\n4. Afficher la liste des vols pour un trajet en particulier ayant lieu avant une certaine date\n5. Afficher un vol en particulier\n\nChoix : ", 'd')) == NULL)
            continue;
        switch(*saisie) {
            case '1':                
                if(admin != NULL) {
                    affichageTousVols(NULL, admin);
                } else {
                    affichageTousVols(passager);
                }
                recommencer = false;
                break;
            case '2':
                if(admin != NULL) {
                    affichageVolsTrajet(NULL, admin);
                } else {
                    affichageVolsTrajet(passager);
                }
                recommencer = false;
                break;
            case '3':
                if(admin != NULL) {
                    affichageVolsDate(NULL, admin);
                } else {
                    affichageVolsDate(passager);
                }
                recommencer = false;
                break;
            case '4':
                if(admin != NULL) {
                    affichageVolsCustom(NULL, admin);
                } else {
                    affichageVolsCustom(passager);
                }
                recommencer = false;
                break;
            case '5':
                if(admin != NULL) {
                    affichageVol(NULL, admin);
                } else {
                    affichageVol(passager);
                }
                recommencer = false;
                break;
            default:
                cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
                break;
        }
    }
    if(admin != NULL) {
        menuLogicielAdministrateur(admin);
    } else {
        menuLogicielPassager(passager);
    }
}

void affichageTousVols(Passager* passager, Administrateur* admin) {
    if(admin != NULL) {
        admin->AfficherListeVols();
    } else {
        passager->AfficherListeVols();
    }
}

void affichageVolsTrajet(Passager* passager, Administrateur* admin) {
    Destination* dest;
    if((dest = saisieDestination()) == NULL) {
        return;
    }
    if(admin != NULL) {
        admin->AfficherListeVols(dest, NULL);
    } else {
        passager->AfficherListeVols(dest, NULL);
    }
}

void affichageVolsDate(Passager* passager, Administrateur* admin) {
    Date* date;
    if((date = saisieDate()) == NULL) {
        return;
    }
    if(admin != NULL) {
        admin->AfficherListeVols(NULL, date);
    } else {
        passager->AfficherListeVols(NULL, date);
    }
}

void affichageVolsCustom(Passager* passager, Administrateur* admin) {
    Destination* dest;
    if((dest = saisieDestination()) == NULL) {
        return;
    }
    Date* date;
    if((date = saisieDate()) == NULL) {
        return;
    }
    if(admin != NULL) {
        admin->AfficherListeVols(dest, date);
    } else {
        passager->AfficherListeVols(dest, date);
    }
}

void affichageVol(Passager* passager, Administrateur* admin) {
    int* num_vol = new int;
    if((num_vol = saisieChamp<int>("\nVeuillez saisir le numero du vol : ", 'e')) == NULL) {
        return;
    }
    if(admin != NULL) {
        if(!(admin->ExistenceVol(*num_vol))) {
            cout << "\nLe numero saisi ne correspond a aucun vol\n";
        } else {
            cout << endl;
            Vol::getVol(*num_vol)->afficherVol();
        }
    } else {
        if(!(passager->ExistenceVol(*num_vol))) {
            cout << "\nLe numero saisi ne correspond a aucun vol\n";
        } else {
            cout << endl;
            Vol::getVol(*num_vol)->afficherVol();
        }
    }
}

void modificationDateVol(Administrateur* admin) {
    int* num_vol = new int;
    if((num_vol = saisieChamp<int>("\nVeuillez saisir le numero du vol choisi : ", 'e')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    if(!(admin->ExistenceVol(*num_vol))) {
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\nVoici le vol correspondant : ";
    Vol::getVol(*num_vol)->afficherVol();
    Date* date;
    if((date = saisieDate()) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    admin->ModifierDateVol(*num_vol, *date);
    cout << "\nModification de date effectuee\n";
    menuLogicielAdministrateur(admin);
}

void ajoutPassager(Administrateur* admin) {
    string* num_passeport = new string;
    if((num_passeport = saisieChamp<string>("\nVeuillez saisir le numero de passeport du passager a ajouter : ", 'f')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    string* mot_de_passe = new string;
    if((mot_de_passe = saisieChamp<string>("Veuillez saisir le mot de passe du passager a ajouter : ", 'c')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    string* prenom = new string;
    if((prenom = saisieChamp<string>("\nVeuillez saisir le prenom du passager : ", 'c')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    string* nom = new string;
    if((nom = saisieChamp<string>("\nVeuillez saisir le nom du passager : ", 'c')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    string* titre = new string;
    if((titre = saisieChamp<string>("\nVeuillez saisir le titre du passager : ", 'c')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    int* age = new int;
    if((age = saisieChamp<int>("\nVeuillez saisir l'age du passager : ", 'g')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    admin->ajouterPassager(*prenom, *nom, *titre, *num_passeport, *mot_de_passe, *age);
    cout << "\nAjout du passager fait\n";
    menuLogicielAdministrateur(admin);
}

void affichageListePassagers(Administrateur* admin) {
    admin->AfficherListePassagers();
    menuLogicielAdministrateur(admin);
}

void ajouterReservation(Administrateur* admin) {
    string* num_passeport = new string;
    if((num_passeport = saisieChamp<string>("\nVeuillez saisir le numero de passeport du passager : ", 'f')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    if(!(admin->ExistencePassager(*num_passeport))) {
        cin.clear();
        cout << "\nErreur, le numero de passeport ne correspond a aucun passager existant\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    int* num_vol = new int;
    if((num_vol = saisieChamp<int>("\nVeuillez saisir le numero du vol : ", 'e')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    if(cin.fail() || !(admin->ExistenceVol(*num_vol))) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        menuLogicielAdministrateur(admin);
        return;
    }  else if(Reservation::reservationExistante(*num_passeport, *num_vol)) {
        cout << "\nErreur, la reservation en quesiton existe deja\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    if(admin->ajouterReservation(Passager::getPassager(*num_passeport), Vol::getVol(*num_vol)))
        cout << "\nAjout de la reservation fait\n";
    else
        cout << "\nLa reservation ne peut pas etre effectuee car l'avion est deja plein\n";
    menuLogicielAdministrateur(admin);
}

void choixAffichageReservations(Administrateur* admin) {
    bool recommencer = true;
    while(recommencer) {
        char* saisie = new char;
        if((saisie = saisieChamp<char>("\nAu choix : \n\n1. Afficher la liste de toutes les reservations tous vols et tous passagers confondus\n2. Afficher la liste des reservations pour un vol particulier\n3. Afficher la liste des reservations d'un passager\n4. Afficher une reservation en particulier\n\nChoix : ", 'd')) == NULL)
            continue;
        switch(*saisie) {
            case '1':
                affichageToutesReservations(admin);
                recommencer = false;
                break;
            case '2':
                affichageReservationsVol(admin);
                recommencer = false;
                break;
            case '3':
                affichageReservationsPassager(admin);
                recommencer = false;
                break;
            case '4':
                affichageReservation(NULL, admin);
                recommencer = false;
                break;
            default:
                cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
                break;
        }
    }
    menuLogicielAdministrateur(admin);
}

void affichageToutesReservations(Administrateur* admin) {
    admin->AfficherListeReservations(0);
}

void affichageReservationsVol(Administrateur* admin) {
    int* num_vol = new int;
    if((num_vol = saisieChamp<int>("\nVeuillez saisir le numero du vol choisi : ", 'e')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }   
    if(!(admin->ExistenceVol(*num_vol))) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        return;
    }
    admin->AfficherListeReservations(*num_vol);
}

void affichageReservationsPassager(Administrateur* admin) {
    string* num_passeport = new string;
    if((num_passeport = saisieChamp<string>("\nVeuillez saisir le numero de passeport du passager choisi : ", 'f')) == NULL) {
        menuLogicielAdministrateur(admin);
        return;
    }
    if(!(admin->ExistencePassager(*num_passeport))) {
        cin.clear();
        cout << "\nErreur, le numero de passeport saisi ne correspond à aucun passager\n";
        return;
    }
    Passager::getPassager(*num_passeport)->AfficherListeReservations();
}

void affichageReservation(Passager* passager, Administrateur* admin) {
    int* num_reservation = new int;
    if((num_reservation = saisieChamp<int>("\nVeuillez saisir le numero de la reservation : ", 'e')) == NULL) {
        return;
    }
    if(admin != NULL) {
        if(!(admin->ExistenceReservation(*num_reservation))) {
            cout << "\nLe numero saisi ne correspond a aucune reservation\n";
        } else {
            cout << endl;
            Reservation::getReservation(*num_reservation)->afficherReservation();
        }
    } else {
        if(!(passager->ExistenceReservation(*num_reservation))) {
            cout << "\nLe numero saisi ne correspond a aucune de vos reservations\n";
        } else {
            cout << endl;
            Reservation::getReservation(*num_reservation)->afficherReservation();
        }
        menuLogicielPassager(passager);
    }
}

void deconnexion(Passager* passager, Administrateur* admin) {
    if(admin != NULL) {
        admin = NULL;
    } else {
        passager = NULL;
    }
    cout << "\nDeconnexion effectuee" << endl;
    menuPrincipal();
}

void quitter(bool sauvegarder) {
    if(sauvegarder) {
        fstream fichier_passagers;
        fichier_passagers.open("./src/donnees/Passagers.txt", ios::out);
        list<Passager*> passagers = Passager::getPassagers();
        list<Passager*>::iterator fin_passagers = passagers.end(); fin_passagers--;
        for(list<Passager*>::const_iterator it = passagers.begin(); it != passagers.end(); it++) {
            fichier_passagers << (*it)->getNom() << ":";
            fichier_passagers << (*it)->getPrenom() << ":";
            fichier_passagers << (*it)->getTitre() << ":";
            fichier_passagers << (*it)->getNum_passeport() << ":";
            fichier_passagers << (*it)->getMot_de_passe() << ":";
            fichier_passagers << (*it)->getAge();
            if(*it != *fin_passagers)
                fichier_passagers << "\n";
        }
        fichier_passagers.close();
        fstream fichier_vols;
        fichier_vols.open("./src/donnees/Vols.txt", ios::out);
        list<Vol*> vols = Vol::getVols();
        list<Vol*>::iterator fin_vols = vols.end(); fin_vols--;
        for(list<Vol*>::const_iterator it = vols.begin(); it != vols.end(); it++) {
            fichier_vols << (*it)->getNb_places() << ":";
            fichier_vols << (*it)->getPrix() << ":";
            fichier_vols << (*it)->getDestination()->getVille_depart() << ":";
            fichier_vols << (*it)->getDestination()->getVille_arrivee() << ":";
            fichier_vols << (*it)->getDate()->getAnnee() << ":";
            fichier_vols << (*it)->getDate()->getMois() << ":";
            fichier_vols << (*it)->getDate()->getJour() << ":";
            fichier_vols << (*it)->getDate()->getHeures() << ":";
            fichier_vols << (*it)->getDate()->getMinutes();            
            if(*it != *fin_vols)
                fichier_vols << "\n";
        }
        fichier_vols.close();
        fstream fichier_reservations;
        fichier_reservations.open("./src/donnees/Reservations.txt", ios::out);        
        list<Reservation*> reservations = Reservation::getReservations();
        list<Reservation*>::iterator fin_reservations = reservations.end(); fin_reservations--;
        for(list<Reservation*>::const_iterator it = reservations.begin(); it != reservations.end(); it++) {
            fichier_reservations << (*it)->getNum_passeport() << ":";
            fichier_reservations << (*it)->getNum_vol() << ":";
            fichier_reservations << (*it)->EstConfirmee();
            if(*it != *fin_reservations)
                fichier_reservations << "\n";
        }
        fichier_reservations.close();
    }
    cout << "\nAu revoir\n" << endl;
}

void pageConnexionPassager() {
    bool recommencer = true;
    while(recommencer) {
        char* saisie = new char;
        if((saisie = saisieChamp<char>("\n\nPage de connexion des passagers : \n\n1. Se connecter\n2. Retour au menu principal\n\nChoix : ", 'd')) == NULL)
            continue;
        switch(*saisie) {
            case '1':
                connexionPassager();
                recommencer = false;
                break;
            case '2':
                menuPrincipal();
                recommencer = false;
                break;
            default:
                cout << "\nErreur, veuillez saisir 1 (pour vous connecter) ou 2 (pour retourner au menu principal)\n";
                break;
        }
    }
}

void connexionPassager() {
    string* num_passeport;
    if((num_passeport = saisieChamp<string>("\nVeuillez saisir votre numero de passeport : ", 'f')) == NULL) {
        pageConnexionPassager();
        return;
    }
    string* mot_de_passe;
    if((mot_de_passe = saisieChamp<string>("Veuillez saisir votre mot de passe : ", 'c')) == NULL) {
        pageConnexionPassager();
        return;
    }
    Passager* passager = Passager::getPassager(*num_passeport, *mot_de_passe);
    if(passager != NULL) {
        cout << "\nIdentification reussie\n";
        menuLogicielPassager(passager);
    } else {
        cout << "\nErreur, les identifiants saisis sont incorrects\n";
        pageConnexionPassager();
    }
}

void menuLogicielPassager(Passager* passager) {
    cout << "\nVous etes connecte en tant que " << passager->getPrenom() << " " << passager->getNom() << endl;
    bool recommencer = true;
    while(recommencer) {
        char* saisie = new char;
        if((saisie = saisieChamp<char>("Veuillez choisir l'une des actions suivantes a effectuer\n\n1. Afficher une liste des vols\n2. Reserver un vol\n3. Afficher une de mes reservations\n4. Afficher la liste de mes reservations\n5. Confirmer une reservation\n6. Annuler une reservation\n7. Se deconnecter\ns. Quitter et sauvegarder\n%. Quitter sans sauvegarder\n\nChoix : ", 'd')) == NULL)
            continue;
        switch(*saisie) {
            case '1':
                choixAffichageVols(passager);
                recommencer = false;
                break;
            case '2':
                reservationVol(passager);
                recommencer = false;
                break;
            case '3' :
                affichageReservation(passager);
                recommencer = false;
                break;
            case '4':
                affichageListeReservationsPassager(passager);
                recommencer = false;
                break;
            case '5':
                confirmerReservation(passager);
                recommencer = false;
                break;
            case '6':
                annulerReservation(passager);
                recommencer = false;
                break;
            case '7':
                deconnexion(passager);
                recommencer = false;
                break;
            case 's':
                quitter(true);
                recommencer = false;
                break;
            case '%':
                quitter(false);
                recommencer = false;
                break;
            default:
                cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
                break;
        }
    }
}

void affichageListeVols(Passager* passager) {
    passager->AfficherListeVols();
    menuLogicielPassager(passager);
}

void reservationVol(Passager* passager) {
    int* num_vol = new int;
    if((num_vol = saisieChamp<int>("\nVeuillez saisir le numero du vol choisi : ", 'e')) == NULL) {
        menuLogicielPassager(passager);
        return;
    }
    if(!(passager->ExistenceVol(*num_vol))) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        menuLogicielPassager(passager);
        return;
    } else if(Reservation::reservationExistante(passager->getNum_passeport(), *num_vol)) {
        cout << "\nErreur, vous disposez deja d'une reservation pour ce vol\n";
        menuLogicielPassager(passager);
        return;
    }
    if(passager->ReserverVol(*num_vol))
        cout << "\nAjout de la reservation fait\n";
    else
        cout << "\nLa reservation ne peut pas etre effectuee car l'avion est deja plein\n";
    menuLogicielPassager(passager);
}

void affichageListeReservationsPassager(Passager* passager) {
    passager->AfficherListeReservations();
    menuLogicielPassager(passager);
}

void confirmerReservation(Passager* passager) {
    int* num_reservation = new int;
    if((num_reservation = saisieChamp<int>("\nVeuillez saisir le numero de la reservation a confirmer : ", 'e')) == NULL) {
        menuLogicielPassager(passager);
        return;
    }
    if(!(passager->ExistenceReservation(*num_reservation))) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucune de vos reservations\n";
        menuLogicielPassager(passager);
        return;
    }
    passager->ConfirmerReservation(*num_reservation);
    cout << "\nConfirmation faite\n";
    menuLogicielPassager(passager);
}

void annulerReservation(Passager* passager) {
    int* num_reservation = new int;
    if((num_reservation = saisieChamp<int>("\nVeuillez saisir le numero de la reservation a annuler : ", 'e')) == NULL) {
        menuLogicielPassager(passager);
        return;
    }
    if(!(passager->ExistenceReservation(*num_reservation))) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucune de vos reservations\n";
        menuLogicielPassager(passager);
        return;
    }
    passager->AnnulerReservation(*num_reservation);
    cout << "\nAnnulation faite\n";
    menuLogicielPassager(passager);
}

int main() {
    Administrateur::chargerAdministrateurs();
    Passager::chargerPassagers();
    Vol::chargerVols();
    Reservation::chargerReservations();
    menuPrincipal();
}