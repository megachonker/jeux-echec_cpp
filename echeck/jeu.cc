#include "jeu.hh"
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include <string>

#include "macro.hh"

using namespace std;

Jeu::Jeu(/* args */){
    //init du plateaux
    joueur=Blanc;//commance par les blanc
}

void Jeu::affiche(){
    mon_echiquier.affiche();
}

Couleur Jeu::get_couleur(){
    return joueur;
}


bool Jeu::deplace(string const orig, string const dest){
        if (orig==dest){
            INFO("la source est la déstination ne peuve etre la meme");
            return false;
        }
        
        //convertion
        Square porigine(orig);
        Square pdst(dest);

        VERBEUX(porigine.print_deplace(pdst))

        //effectue le deplacemnt
        if(!mon_echiquier.deplace(porigine,pdst,joueur)){
            INFO("déplacement pas bon");
            return false;
        }

        //fin du tour on change
        joueur==Blanc ? joueur=Noir : joueur =Blanc;
        return true;
}
Jeu::~Jeu(){
    cout << "destructeur jeux " << endl;
}


