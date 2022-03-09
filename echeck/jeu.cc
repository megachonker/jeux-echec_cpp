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
    //REMPLACER LES FALSE PAR DES NOMS ERREUR 
        if (orig==dest){
            cout << "la source est la déstination ne peuve etre la meme" << endl;
            return false;
        }
        
        bool deplacement_aggressif=false;

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
            cout << "vous avez selectioner une piece d'un autre joueur" << endl;
            return false;
        }

        if (mon_echiquier.get_piece(pdst) != nullptr)   //test si dest est une piece
        {
            //destination moi
            if(mon_echiquier.get_piece(pdst)->get_couleur()==joueur){//test couleur opposer)
                cout << "vous pouvez pas vous déplacer sur vos propre piece /!\\ troc ?" << endl;
                return false;
            }
            // test déplacement agressif
            else
                if(!piece_sel->check_dst(dest,(deplacement_aggressif=true)))
                    return false;
        }
        //case vide
        else
            //test deplacement
            if(!piece_sel->check_dst(dest,false))
                return false;

        mon_echiquier.deplace(piece_sel,pdst,deplacement_aggressif);

        //fin du tour on change
        joueur==Blanc ? joueur=Noir : joueur =Blanc;
        return true;
}
Jeu::~Jeu(){
    cout << "destructeur jeux " << endl;
}

