#include "jeu.hh"
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include <string>

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
            cout << "la source est la déstination ne peuve etre la meme" << endl;
            return false;
        }
        
        //convertion
        Square porigine(orig);
        Square pdst(dest);

        //piece origine non vide
        if (mon_echiquier.est_case_vide(porigine)==true){
            cout << "la case origine" << porigine.to_string() <<" est vide "<< endl;
            return false;
        }

        Piece * piece_sel = mon_echiquier.get_piece(porigine);

        //piece source bonne couleur dst couleur opposer 
        //modifier si troc
        if( piece_sel->get_couleur()!=joueur){//tes si la piece sel appartien au joueur
            cout << "la pece selectioner n'apartien pas au joueur" << endl;    
            return false;
        }

        //si le déplacment final est bon
        int erreur = mon_echiquier.check(piece_sel,pdst);

        //quit en cas d'erreur
        if (!erreur)
            return false;     

        //effectue le deplacemnt
        mon_echiquier.deplace(piece_sel,pdst);

        //fin du tour on change
        joueur==Blanc ? joueur=Noir : joueur =Blanc;
        return true;
}
Jeu::~Jeu(){
    cout << "destructeur jeux " << endl;
}


