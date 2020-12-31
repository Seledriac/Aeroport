#ifndef Date_H_
#include "../Headers/Date.hpp"
#endif

#include <iostream>
#include <sstream>

Date::Date(int annee, int mois, int jour, int heures, int minutes) {
    this->annee = annee;
    this->mois = mois;
    this->jour = jour;
    this->heures = heures;
    this->minutes = minutes;
}

bool Date::operator < (Date &date) {
    if(annee == date.annee) {
        if(mois == date.mois) {
            if(jour == date.jour) {
                if(heures == date.heures) {
                    return minutes < date.minutes;
                } else return heures < date.heures;
            } else return heures < date.jour;
        } else return jour < date.mois;
    } else return annee < date.annee;
}

string Date::to_string() const {
    string mois_converti;
    switch(mois) {
        case 1:
            mois_converti = "Janvier";
            break;
        case 2:
            mois_converti = "Fevrier";
            break;
        case 3:
            mois_converti = "Mars";
            break;
        case 4:
            mois_converti = "Avril";
            break;
        case 5:
            mois_converti = "Mai";
            break;
        case 6:
            mois_converti = "Juin";
            break;
        case 7:
            mois_converti = "Juillet";
            break;
        case 8:
            mois_converti = "Aout";
            break;
        case 9:
            mois_converti = "Septembre";
            break;
        case 10:
            mois_converti = "Octobre";
            break;
        case 11:
            mois_converti = "Novembre";
            break;
        case 12:
            mois_converti = "Decembre";
            break;
        default:
            break;
    }
    string mins = "";
    if(minutes < 10) {
        mins = "0" + std::to_string(minutes);
    }
    stringstream ss;
    ss << jour << " " << mois_converti << " " << annee << ", " << heures << ":" << mins;
    return ss.str();
}

int Date::getAnnee() {
    return annee;
}

int Date::getMois() {
    return mois;
}

int Date::getJour() {
    return jour;
}

int Date::getHeures() {
    return heures;
}

int Date::getMinutes() {
    return minutes;
}

void Date::setAnnee(int annee) {
    this->annee = annee;
}

void Date::setMois(int mois) {
    this->mois = mois;
}

void Date::setJour(int jour) {
    this->jour = jour;
}

void Date::setHeures(int heures) {
    this->heures = heures;
}

void Date::setMinutes(int minutes) {
    this->minutes = minutes;
}