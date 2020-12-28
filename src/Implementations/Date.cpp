#ifndef Date_H_
#define Date_H_

#include <list>

using namespace std;

class Date {

    int minute, heure, jour, mois, annee;
    
    public :
        Date(int, int, int, int, int);
        bool operator < (const Date &) const;
};

#endif