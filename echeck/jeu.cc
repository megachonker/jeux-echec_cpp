#include "jeu.hh"
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
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
        if (orig==dest){
            cout << "la source est la déstination ne peuve etre la meme" << endl;
            return false;
        }
        
        bool flag = true;

        //convertion
        Square porigine(orig);
        Square pdst(dest);
        //piece source
        if (mon_echiquier.est_case_vide(porigine)==true)
        {
            cout << "la case origine" << orig <<" est vide "<< endl;
        }
        
        //la couleur est bonne ?
        Piece * piece_sel = mon_echiquier.get_piece(porigine);//.color et self couleur
        mon_echiquier.get_piece(pdst);//.color et self couleur

        flag = mon_echiquier.deplace(piece_sel,pdst);//passer une ref au lieux d'un pointeurs


        return flag;
    }
