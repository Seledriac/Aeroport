// Commande de compilation (à exécuter depuis la racine du projet):
// g++ ./src/main.cpp ./src/Implementations/Administrateur.cpp ./src/Implementations/Date.cpp ./src/Implementations/Destination.cpp ./src/Implementations/Passager.cpp ./src/Implementations/Reservation.cpp ./src/Implementations/Vol.cpp -o app 

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


void menuPrincipal();
void pageConnexionAdministrateur();
void connexionAdministrateur();
void menuLogicielAdministrateur(Administrateur*);
void ajoutVol(Administrateur*);
void affichageListeVols(Administrateur*);
void modificationDateVol(Administrateur*);
void quitter(bool);
void pageConnexionPassager();


void menuPrincipal() {
    bool recommencer = true;    
    while(recommencer) {        
        cout << "\nEtes-vous administrateur ? (o/n) : ";
        char reponse;
        cin >> reponse;        
        switch(reponse) {
            case 'o':
                pageConnexionAdministrateur();
                recommencer = false;
                break;
            case 'n':
                cout << "Passager";
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
        cout << "\nPage de connexion : \n";
        cout << "\n1. Se connecter";
        cout << "\n2. Retour au menu principal\n\n";
        cout << "Choix : ";
        char reponse;
        cin >> reponse;
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
    cout << "\nVeuillez saisir votre mot de passe : ";
    string mdp;
    cin >> mdp;
    Administrateur* admin = Administrateur::getAdministrateur(identifiant, mdp);
    if(admin != NULL) {
        cout << "\nIdentification reussie\n";
        menuLogicielAdministrateur(admin);
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
        cout << "\n4. Quitter et sauvegarder";
        cout << "\n5. Quitter sans sauvegarder\n\n";
        cout << "Choix : ";
        char reponse;
        cin >> reponse;
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
                quitter(true);
                recommencer = false;
                break;
            case '5':
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
    cout << "\nVeuillez saisir le prix d'une place dans ce vol : ";
    int prix;
    cin >> prix;
    cout << "\n ------ DESTINATION ------";
    cout << "\nVeuillez saisir le nom de la ville de depart : ";
    string ville_depart;
    cin >> ville_depart;
    cout << "\nVeuillez saisir le nom de la ville de destination : ";
    string ville_destination;
    cin >> ville_destination;
    cout << "\n ------ DATE ------";
    cout << "\nVeuillez saisir l'annee : ";
    int annee;
    cin >> annee;
    cout << "\nVeuillez saisir le mois : ";
    int mois;
    cin >> mois;
    cout << "\nVeuillez saisir le jour : ";
    int jour;
    cin >> jour;
    cout << "\nVeuillez saisir les heures : ";
    int heures;
    cin >> heures;
    cout << "\nVeuillez saisir les minutes : ";
    int minutes;
    cin >> minutes;
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
    cout << "\n\nVeuillez saisir la nouvelle annee : ";
    int annee;
    cin >> annee;
    cout << "\nVeuillez saisir le nouveau mois : ";
    int mois;
    cin >> mois;
    cout << "\nVeuillez saisir le nouveau jour : ";
    int jour;
    cin >> jour;
    cout << "\nVeuillez saisir les nouvelles heures : ";
    int heures;
    cin >> heures;
    cout << "\nVeuillez saisir les nouvelles minutes : ";
    int minutes;
    cin >> minutes;
    admin->ModifierDateVol(num_vol, annee, mois, jour, heures, minutes);
    cout << "Modification de date effectuee";
    menuLogicielAdministrateur(admin);
}

void quitter(bool sauvegarder) {
    if(sauvegarder) {
        // connexion bdd et insertion des listes dans leurs tables correspondantes
    }
    cout << "\nAu revoir\n" << endl;
}

void pageConnexionPassager() {
}

int main() {
    cout << "\nBienvenue dans le logiciel de l'Aeroport Paris CDG\n";
    Administrateur::chargerAdministrateurs();
    menuPrincipal();
}