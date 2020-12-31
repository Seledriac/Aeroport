// Commande de compilation (à exécuter depuis la racine du projet):
// g++ ./src/main.cpp ./src/Implementations/*.cpp 

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
#include <ctime>
#include <regex>

void menuPrincipal();
void pageConnexionAdministrateur();
void connexionAdministrateur();
void menuLogicielAdministrateur(Administrateur*);
void ajoutVol(Administrateur*);
void affichageListeVols(Administrateur*);
void modificationDateVol(Administrateur*);
void ajoutPassager(Administrateur*);
void affichageListePassagers(Administrateur*);
void ajouterReservation(Administrateur*);
void choixAffichageReservations(Administrateur*);
void affichageToutesReservations(Administrateur*);
void affichageReservationsVol(Administrateur*);
void affichageReservationsPassager(Administrateur*);
void deconnexion();
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
        cout << "\nEtes-vous administrateur ? (o/n) : ";
        char reponse;
        cin >> reponse;
        if(cin.fail()) {
            cin.clear();
            cout << "\nErreur, veuillez saisir o (pour oui) ou n (pour non)\n";
            break;
        }
        switch(reponse) {
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
        cout << "\n\nPage de connexion des administrateurs : \n";
        cout << "\n1. Se connecter";
        cout << "\n2. Retour au menu principal\n\n";
        cout << "Choix : ";
        char reponse;
        cin >> reponse;
        if(cin.fail()) {
            cin.clear();
            cout << "\nErreur, veuillez saisir 1 (pour vous connecter) ou 2 (pour retourner au menu principal)\n";
            break;
        }
        switch(reponse) {
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
    cout << "\nVeuillez saisir votre identifiant : ";
    string identifiant;
    cin >> identifiant;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        pageConnexionAdministrateur();
        return;
    }
    cout << "Veuillez saisir votre mot de passe : ";
    string mdp;
    cin >> mdp;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        pageConnexionAdministrateur();
        return;
    }
    Administrateur* admin = Administrateur::getAdministrateur(identifiant, mdp);
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
        cout << "\nPage d'administrateur : \n";
        cout << "\n1. Ajouter un vol";
        cout << "\n2. Afficher la liste des vols";
        cout << "\n3. Modifier la date d'un vol";
        cout << "\n4. Ajouter un passager";
        cout << "\n5. Afficher la liste des passagers";
        cout << "\n6. Ajouter une reservation";
        cout << "\n7. Afficher une liste des reservations";        
        cout << "\n8. Se deconnecter";
        cout << "\ns. Quitter et sauvegarder";
        cout << "\n%. Quitter sans sauvegarder\n\n";
        cout << "Choix : ";
        char reponse;
        cin >> reponse;
        if(cin.fail()) {
            cin.clear();
            cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
            break;
        }
        switch(reponse) {
            case '1':
                ajoutVol(admin);
                recommencer = false;
                break;
            case '2':
                affichageListeVols(admin);
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
                deconnexion();
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

void ajoutVol(Administrateur* admin) {
    cout << "\nVeuillez saisir le nombre de places maximal du vol : ";
    int nb_places;
    cin >> nb_places;
    if(nb_places <= 0 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le nombre de places saisi doit etre un nombre positif\n";        
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le prix d'une place dans ce vol : ";
    int prix;
    cin >> prix;
    if(prix <= 0 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le prix saisi doit etre un nombre positif\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\n ------ TRAJET ------\n";
    cout << "\nVeuillez saisir le nom de la ville de depart : ";
    string ville_depart;
    cin >> ville_depart;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le nom de la ville de destination : ";
    string ville_destination;
    cin >> ville_destination;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    time_t mtn = time(0);
    tm* ltm = localtime(&mtn);
    cout << "\n ------ DATE ------\n";
    cout << "\nVeuillez saisir l'annee : ";
    int annee;
    cin >> annee;
    if(annee < 1900 + ltm->tm_year || cin.fail()) {
        cin.clear();
        cout << "\nErreur, l'annee saisie doit etre un nombre superieur a celui de l'annee de la date actuelle\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le numero du mois : ";
    int mois;
    cin >> mois;
    if(mois < 1 || mois > 12 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero de mois saisi doit etre un nombre compris entre 1 et 12\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois < 1 + ltm->tm_mon) {        
        cout << "\nErreur, le mois saisi ne peut pas etre inferieur au mois actuel si l'annee est egale\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le numero du jour du mois : ";
    int jour;
    cin >> jour;
    if(jour < 1 || jour > 31 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero de jour du mois saisi doit etre un nombre compris entre 1 et 31\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour < ltm->tm_mday) {        
        cout << "\nErreur, le numero de jour du mois saisi ne peut pas etre inferieur au jour actuel si l'annee et le mois sont egaux a l'annee et le mois actuels\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le nombre d'heures : ";
    int heures;
    cin >> heures;
    if(heures < 0 || heures > 24 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le nombre d'heures saisi doit etre un nombre compris entre 0 et 23\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour == ltm->tm_mday && heures < ltm->tm_hour) {        
        cout << "\nErreur, le nombre d'heures saisi ne peut pas etre inferieur au nombre d'heures actuel si la date est celle d'aujourd'hui\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le nombre de minutes : ";
    int minutes;
    cin >> minutes;
    if(minutes < 0 || minutes > 60 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le nombre de minutes saisi doit etre un nombre compris entre 0 et 59\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour == ltm->tm_mday && heures == ltm->tm_hour && minutes < ltm->tm_min) {        
        cout << "\nErreur, le nombre de minutes saisi ne peut pas etre inferieur au nombre de minutes de l'heure actuelle si la date et est celle d'aujourd'hui et le nombre d'heures est le nombre d'heures actuel\n";        
        menuLogicielAdministrateur(admin);
        return;
    }
    admin->ajouterVol(nb_places, prix, ville_depart, ville_destination, annee, mois, jour, heures, minutes);
    cout << "\nAjout du vol fait" << endl;
    menuLogicielAdministrateur(admin);
}

void affichageListeVols(Administrateur* admin) {
    admin->AfficherListeVols();
    menuLogicielAdministrateur(admin);
}

void modificationDateVol(Administrateur* admin) {
    cout << "\nVeuillez saisir le numero du vol choisi : ";
    int num_vol;
    cin >> num_vol;
    if(!(admin->ExistenceVol(num_vol))) {
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\nVoici le vol correspondant : ";
    Vol::getVol(num_vol)->afficherVol();
    time_t mtn = time(0);
    tm* ltm = localtime(&mtn);
    cout << "\nVeuillez saisir la nouvelle annee : ";
    int annee;
    cin >> annee;
    if(annee < 1900 + ltm->tm_year || cin.fail()) {
        cin.clear();
        cout << "\nErreur, l'annee saisie doit etre un nombre superieur a celui de l'annee de la date actuelle\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le numero du mois : ";
    int mois;
    cin >> mois;
    if(mois < 1 || mois > 12 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero de mois saisi doit etre un nombre compris entre 1 et 12\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois < 1 + ltm->tm_mon) {        
        cout << "\nErreur, le mois saisi ne peut pas etre inferieur au mois actuel si l'annee est egale\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le numero du jour du mois : ";
    int jour;
    cin >> jour;
    if(jour < 1 || jour > 31 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero de jour du mois saisi doit etre un nombre compris entre 1 et 31\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour < ltm->tm_mday) {        
        cout << "\nErreur, le numero de jour du mois saisi ne peut pas etre inferieur au jour actuel si l'annee et le mois sont egaux a l'annee et le mois actuels\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le nombre d'heures : ";
    int heures;
    cin >> heures;
    if(heures < 0 || heures > 24) {
        cin.clear();
        cout << "\nErreur, le nombre d'heures saisi doit etre un nombre compris entre 0 et 23\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour == ltm->tm_mday && heures < ltm->tm_hour) {        
        cout << "\nErreur, le nombre d'heures saisi ne peut pas etre inferieur au nombre d'heures actuel si la date est celle d'aujourd'hui\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le nombre de minutes : ";
    int minutes;
    cin >> minutes;
    if(minutes < 0 || minutes > 60 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le nombre de minutes saisi doit etre un nombre compris entre 0 et 59\n";
        menuLogicielAdministrateur(admin);
        return;
    } else if(annee == 1900 + ltm->tm_year && mois == 1 + ltm->tm_mon && jour == ltm->tm_mday && heures == ltm->tm_hour && minutes < ltm->tm_min) {        
        cout << "\nErreur, le nombre de minutes saisi ne peut pas etre inferieur au nombre de minutes de l'heure actuelle si la date et est celle d'aujourd'hui et le nombre d'heures est le nombre d'heures actuel\n";        
        menuLogicielAdministrateur(admin);
        return;
    }
    admin->ModifierDateVol(num_vol, annee, mois, jour, heures, minutes);
    cout << "\nModification de date effectuee\n";
    menuLogicielAdministrateur(admin);
}

void ajoutPassager(Administrateur* admin) {
    cout << "\nVeuillez saisir le numero de passeport du passager a ajouter : ";
    string num_passeport;
    cin >> num_passeport;
    bool bon_format = true;
    for(int i = 0; num_passeport[i] != '\0'; i++) {
        if(!isalnum(num_passeport[i]))
            bon_format = false;
    }
    if(!bon_format || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le format de numero de passeport saisi est invalide\n";        
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le mot de passe du passager a ajouter : ";
    string mot_de_passe;
    cin >> mot_de_passe;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\nVeuillez saisir le prenom du passager : ";
    string prenom;
    cin >> prenom;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\nVeuillez saisir le nom du passager : ";
    string nom;
    cin >> nom;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\nVeuillez saisir le titre du passager : ";
    string titre;
    cin >> titre;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "\nVeuillez saisir l'age du passager : ";
    int age;
    cin >> age;
    if(age < 0 || cin.fail()) {
        cin.clear();
        cout << "\nErreur, l'age saisi doit etre un nombre positif\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    admin->ajouterPassager(prenom, nom, titre, num_passeport, mot_de_passe, age);
    cout << "\nAjout du passager fait\n";
    menuLogicielAdministrateur(admin);
}

void affichageListePassagers(Administrateur* admin) {
    admin->AfficherListePassagers();
    menuLogicielAdministrateur(admin);
}

void ajouterReservation(Administrateur* admin) {
    cout << "\nVeuillez saisir le numero de passeport du passager : ";
    string num_passeport;
    cin >> num_passeport;
    if(!(admin->ExistencePassager(num_passeport)) || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero de passeport ne correspond a aucun passager existant\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    cout << "Veuillez saisir le numero du vol : ";
    int num_vol;
    cin >> num_vol;
    if(!(admin->ExistenceVol(num_vol)) || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        menuLogicielAdministrateur(admin);
        return;
    }  else if(Reservation::reservationExistante(num_passeport, num_vol)) {
        cout << "\nErreur, la reservation en quesiton existe deja\n";
        menuLogicielAdministrateur(admin);
        return;
    }
    Passager* passager = Passager::getPassager(num_passeport);
    Vol* vol = Vol::getVol(num_vol);
    if(admin->ajouterReservation(passager, vol))
        cout << "\nAjout de la reservation fait\n";
    else
        cout << "\nLa reservation ne peut pas etre effectuee car l'avion est deja plein\n";
    menuLogicielAdministrateur(admin);
}

void choixAffichageReservations(Administrateur* admin) {
    bool recommencer = true;
    while(recommencer) {    
        cout << "\nAu choix : \n";
        cout << "\n1. Afficher la liste de toutes les reservations tous vols et tous passagers confondus";
        cout << "\n2. Afficher la liste des reservations pour un vol particulier";
        cout << "\n3. Afficher la liste des reservations d'un passager\n\n";
        cout << "Choix : ";
        char reponse;
        cin >> reponse;        
        if(cin.fail()) {
            cin.clear();
            cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
            break;
        }
        switch(reponse) {
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
    cout << "\nVeuillez saisir le numero du vol choisi : ";
    int num_vol;
    cin >> num_vol;
    if(!(admin->ExistenceVol(num_vol)) || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        return;
    }
    admin->AfficherListeReservations(num_vol);
}

void affichageReservationsPassager(Administrateur* admin) {
    cout << "\nVeuillez saisir le numero de passeport du passager choisi : ";
    string num_passeport;
    cin >> num_passeport;
    if(!(admin->ExistencePassager(num_passeport)) || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero de passeport saisi ne correspond à aucun passager\n";
        return;
    }
    Passager::getPassager(num_passeport)->AfficherListeReservations();
}

void deconnexion() {
    cout << "\nDeconnexion effectuee" << endl;
    menuPrincipal();
}

void quitter(bool sauvegarder) {
    if(sauvegarder) {
        // connexion bdd et insertion des listes dans leurs tables correspondantes
    }
    cout << "\nAu revoir\n" << endl;
}

void pageConnexionPassager() {
    bool recommencer = true;
    while(recommencer) {    
        cout << "\n\nPage de connexion des passagers : \n";
        cout << "\n1. Se connecter";
        cout << "\n2. Retour au menu principal\n\n";
        cout << "Choix : ";
        char reponse;
        cin >> reponse;
        if(cin.fail()) {
            cin.clear();
            cout << "\nErreur, veuillez saisir 1 (pour vous connecter) ou 2 (pour retourner au menu principal)\n";
            break;
        }
        switch(reponse) {
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
    cout << "\nVeuillez saisir votre numero de passeport : ";
    string num_passeport;
    cin >> num_passeport;
    bool bon_format = true;
    for(int i = 0; num_passeport[i] != '\0'; i++) {
        if(!isalnum(num_passeport[i]))
            bon_format = false;
    }
    if(!bon_format || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le format de numero de passeport saisi est invalide\n";     
        pageConnexionPassager();
        return;
    }
    cout << "Veuillez saisir votre mot de passe : ";
    string mdp;
    cin >> mdp;
    if(cin.fail()) {
        cin.clear();
        cout << "\nErreur, saisie invalide\n";
        pageConnexionPassager();
        return;
    }
    Passager* passager = Passager::getPassager(num_passeport, mdp);
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
        cout << "Veuillez choisir l'une des actions suivantes a effectuer\n";
        cout << "\n1. Afficher la liste des vols";
        cout << "\n2. Reserver un vol";
        cout << "\n3. Afficher la liste de mes reservations";
        cout << "\n4. Confirmer une reservation";
        cout << "\n5. Annuler une reservation";
        cout << "\n6. Se deconnecter";
        cout << "\ns. Quitter et sauvegarder";
        cout << "\n%. Quitter sans sauvegarder\n\n";
        cout << "Choix : ";
        char reponse;
        cin >> reponse;
        if(cin.fail()) {
            cin.clear();
            cout << "\nErreur, veuillez saisir un chiffre-commande adéquat\n";
            break;
        }
        switch(reponse) {
            case '1':
                affichageListeVols(passager);
                recommencer = false;
                break;
            case '2':
                reservationVol(passager);
                recommencer = false;
                break;
            case '3':
                affichageListeReservationsPassager(passager);
                recommencer = false;
                break;
            case '4':
                confirmerReservation(passager);
                recommencer = false;
                break;
            case '5':
                annulerReservation(passager);
                recommencer = false;
                break;
            case '6':
                deconnexion();
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
    cout << "\nVeuillez saisir le numero du vol : ";
    int num_vol;
    cin >> num_vol;
    if(!(passager->ExistenceVol(num_vol)) || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucun vol\n";
        menuLogicielPassager(passager);
        return;
    } else if(Reservation::reservationExistante(passager->getNum_passeport(), num_vol)) {
        cout << "\nErreur, vous disposez deja d'une reservation pour ce vol\n";
        menuLogicielPassager(passager);
        return;
    }
    if(passager->ReserverVol(num_vol))
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
    cout << "\nVeuillez saisir le numero de la reservation a confirmer : ";
    int num_reservation;
    cin >> num_reservation;
    if(!(passager->ExistenceReservation(num_reservation)) || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucune de vos reservations\n";
        menuLogicielPassager(passager);
        return;
    }
    passager->ConfirmerReservation(num_reservation);
    cout << "\nConfirmation faite\n";
    menuLogicielPassager(passager);
}

void annulerReservation(Passager* passager) {
    cout << "\nVeuillez saisir le numero de la reservation a annuler : ";
    int num_reservation;
    cin >> num_reservation;
    if(!(passager->ExistenceReservation(num_reservation)) || cin.fail()) {
        cin.clear();
        cout << "\nErreur, le numero saisi ne correspond a aucune de vos reservations\n";
        menuLogicielPassager(passager);
        return;
    }
    passager->AnnulerReservation(num_reservation);
    cout << "\nAnnulation faite\n";
    menuLogicielPassager(passager);
}

int main() {
    Administrateur::chargerAdministrateurs();
    Passager::chargerPassagers();
    menuPrincipal();
}