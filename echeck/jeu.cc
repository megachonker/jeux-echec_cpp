#include "jeu.hh"
#include "echiquier.hh"
#include <string>
using namespace std;

Jeu::Jeu(/* args */){
    //init du plateaux
    Echiquier mon_echiquier = Echiquier();
}
void Jeu::affiche(){}
bool Jeu::deplace(string coordoner, string const orig, string const dest){
    //convertion
    Square square(coordoner);
    //la piece existe ?
    est_case_vide(square);
    
    //la couleur est bonne ?
    get_piece(square);//.color et self couleur

    return true;
    }
