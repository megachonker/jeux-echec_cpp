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

        //piece origine non vide
        if (mon_echiquier.est_case_vide(porigine)==true){
            INFO("la case origine" << porigine.to_string() <<" est vide ");
            return false;
        }

        Piece * piece_sel = mon_echiquier.get_piece(porigine);

        //piece source bonne couleur dst couleur opposer 
        //modifier si troc
        if( piece_sel->get_couleur()!=joueur){//tes si la piece sel appartien au joueur
            INFO("la pece selectioner n'apartien pas au joueur" );    
            return false;
        }

        //si le déplacment final est bon
        if(!mon_echiquier.check(piece_sel,pdst)){
            INFO("déplacement pas bon");
            return false;
        }



        //effectue le deplacemnt
        mon_echiquier.deplace(piece_sel,pdst);

        //fin du tour on change
        joueur==Blanc ? joueur=Noir : joueur =Blanc;
        return true;
}
Jeu::~Jeu(){
    cout << "destructeur jeux " << endl;
}


