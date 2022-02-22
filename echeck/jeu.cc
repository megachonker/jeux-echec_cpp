#include "jeu.hh"
#include "echiquier.hh"
#include "square.hh"
#include <string>
using namespace std;

Jeu::Jeu(/* args */){
    //init du plateaux
    mon_echiquier = Echiquier();
}

void Jeu::affiche(){}
bool Jeu::deplace(string coordoner, string const orig, string const dest){
    //convertion
    Square square(coordoner);
    //la piece existe ?
    mon_echiquier.est_case_vide(square);
    
    //la couleur est bonne ?
    mon_echiquier.get_piece(square);//.color et self couleur

    return true;
    }
