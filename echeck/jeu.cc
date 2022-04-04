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
    numero_tour=5;
}

void Jeu::affiche(){
    mon_echiquier.affiche();
    VERBEUX("affichage joueur:");
    //stoque le resultat du test pour savoir si mat
    en_echeque=mon_echiquier.chk_echec_roi(joueur);
    if(en_echeque){
        INFO("Vous ête en Echèque !");
    }
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

        INFO("INPUT: " << porigine.print_deplace(pdst));
        //effectue le deplacemnt
        erreurDeplacement err;
        if((err = mon_echiquier.deplace(porigine,pdst,joueur))!=ok){
            explain(err);
            return false;
        }

        deplacement[numero_tour+1][0] = porigine;
        deplacement[numero_tour+1][1] = pdst;

        end_turn();
        return true;
}


bool Jeu::is_pat(){

    DEBUG("numero tour: " << numero_tour);
    if (numero_tour > 50)
    {
        INFO("PAT plus de 50 coup");
        return true;
    }

    if(
    deplacement[numero_tour  ][1].to_string() == deplacement[numero_tour-4][1].to_string() &&
    deplacement[numero_tour  ][1].to_string() == deplacement[numero_tour-8][1].to_string() && 
    deplacement[numero_tour  ][0].to_string() == deplacement[numero_tour-4][0].to_string() &&
    deplacement[numero_tour  ][0].to_string() == deplacement[numero_tour-8][0].to_string()){
        INFO("PAT 3 movement identique d'afiler");
        return true;
    }


    DEBUG("mouvement précédent: " << deplacement[numero_tour  ][1].to_string()<< " <= " <<deplacement[numero_tour-4][1].to_string() << " <== " << deplacement[numero_tour-8][1].to_string());

    return false;
}

bool Jeu::fin(){

    //si le cache de résolution est plus valide on le régénère
    if (!cache_resolution){     

        #ifdef DEBUG_ON
        mon_echiquier.print_all_piece();
        #endif

        Echiquier plateaux_temporaire(mon_echiquier);
        resolut = plateaux_temporaire.isstuck(joueur);

        if(resolut){
            DEBUG("Solution Empirique");
            #ifdef DEBUG_ON
            plateaux_temporaire.affiche(&mon_echiquier);
            #endif            
        }else
            DEBUG("pas de solution");

        cache_resolution=true;
    }

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

    //verifie le pat
    if (is_pat())
        return false;

    DEBUG("PAS EN ECHEQUE");
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
        case dejabougerR:
            WARNING("le rois a déja bouger");
            break;
        case dejabougerT:
            WARNING("la tour a déja bouger");
            break;
        case echeque:
            WARNING("vous vous metez en echeque");
            break;
        case TK:
            WARNING("vous pouvez pas manger vos propre piece");
            break;
        case prisepasantfail:
            WARNING("la prise en passant n'es pas effectuer avec la bonne piece");
            break;
    }
}

erreurDeplacement Jeu::rock(bool grand){
        erreurDeplacement retour = mon_echiquier.rocker(joueur,grand);
        if(retour==ok){
            end_turn();
            return ok;
        }
    
        WARNING("rock imposible");
        return retour;
}

void Jeu::end_turn(){
    numero_tour++;
    //fin du tour on change de joueur
    joueur==Blanc ? joueur=Noir : joueur =Blanc;
    //on invalide le cache de la fesabilitée du jeux
    cache_resolution = false;
    //reset de la prise en passant
    mon_echiquier.rst_passant();
}