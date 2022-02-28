#include "jeu.hh"
#include "echiquier.hh"
#include "square.hh"
#include <string>
using namespace std;

Jeu::Jeu(/* args */){
    //init du plateaux
    mon_echiquier = Echiquier();
}

void Jeu::affiche(){
    mon_echiquier.affiche();
}

bool Jeu::deplace(string const orig, string const dest){
        if (orig==dest)
            return false;
        
        bool flag = true;

        //convertion
        Square porigine(orig);
        Square pdst(dest);
        //la piece existe ?
        mon_echiquier.est_case_vide(porigine);
        if (flag == false)
        {
            cout << "la case" << orig <<" est vide "<< endl;
            return false;
        }
        
        //la couleur est bonne ?
        mon_echiquier.get_piece(porigine);//.color et self couleur
        mon_echiquier.get_piece(pdst);//.color et self couleur

        // mon_echiquier.deplace(pdst);

        return flag;
    }
