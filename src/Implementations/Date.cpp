#ifndef Date_H_
#include <Date.hpp>
#endif

#include <iostream>

Date::Date(int annee, int mois, int jour, int heures, int minutes) {
    this->annee = annee;
    this->mois = mois;
    this->jour = jour;
    this->heures = heures;
    this->minutes = minutes;
}

bool Date::operator < (Date &date) {
    if(annee == date.getAnnee()) {
        if(mois == date.getMois()) {
            if(jour == date.getJour()) {
                if(heures == date.getHeures()) {
                    return minutes < date.getMinutes();
                } else return heures < date.getHeures();
            } else return heures < date.getJour();
        } else return jour < date.getMois();
    } else return annee < date.getAnnee();
}

ostream& operator <<(ostream &os, Date &date) {
    string mois;
    switch(date.getMois()) {
        case 1:
            mois = "Janvier";
            break;
        case 2:
            mois = "Fevrier";
            break;
        case 3:
            mois = "Mars";
            break;
        case 4:
            mois = "Avril";
            break;
        case 5:
            mois = "Mai";
            break;
        case 6:
            mois = "Juin";
            break;
        case 7:
            mois = "Juillet";
            break;
        case 8:
            mois = "Aout";
            break;
        case 9:
            mois = "Septembre";
            break;
        case 10:
            mois = "Octobre";
            break;
        case 11:
            mois = "Novembre";
            break;
        case 12:
            mois = "Decembre";
            break;
        default:
            break;
    }
    return os << date.getJour() << " " << mois << " " << date.getAnnee() << ", " << date.getHeures() << ":" << date.getMinutes();
}