#include "jeu.hh"
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include <string>

#include "macro.hh"

using namespace std;

Jeu::Jeu(/* args */){
    //init du plateaux
    resolut=false;
    cache_resolution=false;
    joueur=Blanc;//commance par les blanc
    en_echeque=false;
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
        VERBEUX("joueur commence sont tour est t'il en echeque ?:")
        en_echeque = mon_echiquier.chk_echec_roi(joueur);

        if (orig==dest){
            INFO("la source est la déstination ne peuve etre la meme");
            return false;
        }
        
        //convertion
        Square porigine(orig);
        Square pdst(dest);

        INFO("INPUT: " << porigine.print_deplace(pdst));
        //effectue le deplacemnt
        erreurDeplacement err;
        if((err = mon_echiquier.deplace(porigine,pdst,joueur))!=ok){
            explain(err);
            return false;
        }
        //fin du tour on change de joueur
        joueur==Blanc ? joueur=Noir : joueur =Blanc;
        //on invalide le cache de la fesabilitée du jeux
        cache_resolution = false;
        return true;
}

bool Jeu::fin(){
    Echiquier plateaux_temporaire = mon_echiquier;
    
    //si le cache de résolution est plus valide on le régénère
    if (!cache_resolution)
        resolut = plateaux_temporaire.isstuck(joueur);

    //si la partie est irrésolvable
    if(!resolut){
        if(en_echeque){
            INFO("Vous ête echeque est MAT");
        }
        else{
            INFO("Vous PAT");
        }
        return false;
    }
    return true;
}

Jeu::~Jeu(){
    cout << "destructeur jeux " << endl;
}



void Jeu::explain(enum erreurDeplacement err){
    switch (err)
    {
        case ok:
            break;
        case srcvide:
            WARNING("case d'origine vide !");
            break;
        case appartenance:
            WARNING("la pece selectioner n'apartien pas au joueur");
            break;
        case checkgeometric:
            WARNING("pseudo check géometrique echouer");
            break;
        case collision:
            WARNING("les piece entre en colision");
            break;
        case echeque:
            WARNING("vous vous metez en echeque");
            break;
    }
}