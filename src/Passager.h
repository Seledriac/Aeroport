#ifndef Passager_H
#define Passager_H

using namespace std

class Passager{
    string nom,prenom,titre;
    int numero; 
    public :
        Passager(string,string,string,int);
        void ReserverVol();
        bool ConfirmerReservation();
        void AnnulerReservation();
        void AfficherListeVol();
        bool ExistenceVol();
        bool ExistenceReservation();
};
#endif