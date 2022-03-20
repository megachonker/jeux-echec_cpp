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
    VERBEUX("affichage joueur:");
    if(mon_echiquier.chk_echec_roi(joueur))
        INFO("Vous ête en Echèque !");
}

Couleur Jeu::get_couleur(){
    return joueur;
}


bool Jeu::deplace(string const orig, string const dest){
        /// affiche si le joueur est en echeque
        DEBUG("joueur commence sont tour est t'il en echeque ?:")
        bool en_echeque = mon_echiquier.chk_echec_roi(joueur);

        if (orig==dest){
            INFO("la source est la déstination ne peuve etre la meme");
            return false;
        }
        
        //convertion
        Square porigine(orig);
        Square pdst(dest);

        INFO("INPUT: " << porigine.print_deplace(pdst));

        //effectue le deplacemnt
        if(!mon_echiquier.deplace(porigine,pdst,joueur)){
            INFO("déplacement pas bon");
            

            //le joueur a réfléchit pour nous il a pas trouver de coup donc a nous de chercher si il y a un coup qui existe

            //on instancie un jeux est on joue un coup
                //tant qu'il n'y a pas un coup possible
            //si aucune solution n'es trouver allor
            //si le joueur etait en echeque au début du tour 
            //allor MAT
            //sinon PAT

            return false;
        }
        //fin du tour on change
        joueur==Blanc ? joueur=Noir : joueur =Blanc;
        return true;
}
Jeu::~Jeu(){
    cout << "destructeur jeux " << endl;
}


