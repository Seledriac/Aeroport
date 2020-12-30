#ifndef Date_H_
#define Date_H_

#include <list>
#include <iostream>

using namespace std;

class Date {

    int annee, mois, jour, heures, minutes;
    
    public :
        Date(int, int, int, int, int);
        bool operator < (Date &);
        string to_string() const;
        int getAnnee();
        int getMois();
        int getJour();
        int getHeures();
        int getMinutes();
        void setAnnee(int);
        void setMois(int);
        void setJour(int);
        void setHeures(int);
        void setMinutes(int);
};

#endif