#ifndef Date_H_
#define Date_H_

#include <list>

using namespace std;

class Date {

    int annee, mois, jour, heures, minutes;
    
    public :
        Date(int, int, int, int, int);
        bool operator < (Date &);
        friend ostream& operator <<(ostream &, Date &);
        int getAnnee();
        int getMois();
        int getJour();
        int getHeures();
        int getMinutes();
};

#endif