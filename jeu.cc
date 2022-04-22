#include "jeu.hh"
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include <string>

#include "macro.hh"

using namespace std;

Jeu::Jeu(){
    //init du plateaux
    resolut=false;
    cache_resolution=false;
    joueur=Blanc;//commance par les blanc
    en_echeque=false;
    numero_tour=5;
    deplacement[1][0] = Square(1,1);
    deplacement[1][1] = Square(1,1);
}


/**
 * @brief affiche le plateaux 
 * 
 */
void Jeu::affiche(){
    mon_echiquier.affiche();
    VERBEUX("affichage joueur:");
    if(en_echeque){
        INFO("Vous ête en Echèque !");
    }
}

Couleur Jeu::get_couleur(){
    return joueur;
}
 
/**
 * @brief permet de demander a déplacer la piece au vue du jeux
 * 
 * @param orig 
 * @param dest 
 * @return true 
 * @return false 
 */
bool Jeu::deplace(string const orig, string const dest){

        if (orig==dest){
            INFO("la source est la déstination ne peuvent pas être la meme");
            return false;
        }
        
        //convertion
        Square porigine(orig);
        Square pdst(dest);

        INFO("INPUT: " << porigine.print_deplace(pdst));
        
        //effectue le deplacemnt
        erreurDeplacement err;
        if((err = mon_echiquier.deplace(porigine,pdst,joueur,true))!=ok){
            explain(err);
            return false;
        }

        deplacement[numero_tour+1][0] = porigine;
        deplacement[numero_tour+1][1] = pdst;

        //promotion
        mon_echiquier.promote(pdst);

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

        #ifdef DEBUG_EMP
        mon_echiquier.print_all_piece();
        #endif

        Echiquier plateaux_temporaire(mon_echiquier);
        resolut = plateaux_temporaire.isstuck(joueur,en_echeque);

        if(resolut){
            DEBUG("Solution Empirique");
            #ifdef DEBUG_EMP
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


/**
 * @brief traduit les code d'erreur en message pour l'utilisateur
 * 
 * @param err 
 */
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
    swapcolor(joueur);
    //met a jour si le joueur suivant est en echeque
    en_echeque=mon_echiquier.chk_echec_roi(joueur);
    //on invalide le cache de la fesabilitée du jeux
    cache_resolution = false;
    //reset de la prise en passant
    mon_echiquier.rst_passant();
}