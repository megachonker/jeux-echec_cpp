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


/**
 * @brief peut utiliser le check sans avoir a passer le déplacemnt
 * 
 * @param piece 
 * @param pos_dst 
 * @return int 
 */
int Jeu::check(Piece * const piece, Square const pos_dst){
    bool osef = false;
    return check(piece,pos_dst,osef);
}

/**
 * @brief est utisiler pour check les collision
 * 
 * @param [in] piece car on a un attribut virtuel donc on peut pas associer lespace 
 * @param [in] position_dst 
 * @param [out] deplacement_aggressif va la modifier si le déplacement est aggresif
 * @return int erreur numero
 */
int Jeu::check(Piece * piece, Square position_dst,bool &deplacement_aggressif){

    //piece source bonne couleur dst couleur opposer 
        //modifier si troc
    if( piece->get_couleur()!=joueur){//tes si la piece sel appartien au joueur
        cout << "vous avez selectioner une piece d'un autre joueur" << endl;
        return false;
    }

    if (mon_echiquier.get_piece(position_dst) != nullptr)   //test si dest est une piece
    {
        //destination moi
        if(mon_echiquier.get_piece(position_dst)->get_couleur()==joueur){//test couleur opposer)
            cout << "vous pouvez pas vous déplacer sur vos propre piece /!\\ troc ?" << endl;
            return false;
        }
        // test déplacement agressif
        else
            if(!piece->check_dst(position_dst,(deplacement_aggressif=true)))
                return false;
    }
    //case vide
    else
        //test deplacement
        if(!piece->check_dst(position_dst,false))
            return false;

    return true;
}


void Jeu::errorhande(int errono){
    switch (errono)
    {
    case 0:
        break;
    
    default:
        break;
    }
}


bool Jeu::deplace(string const orig, string const dest){
    //REMPLACER LES FALSE PAR DES NOMS ERREUR 
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

        bool deplacement_aggressif=false;

        //si le déplacment final est bon
        int erreur = check(piece_sel,pdst,deplacement_aggressif);
        //print l'erreur de déplacement
        errorhande(erreur);

        //quit en cas d'erreur
        if (!erreur)
            return false;     

        //effectue le deplacemnt
        mon_echiquier.deplace(piece_sel,pdst,deplacement_aggressif);

        //fin du tour on change
        joueur==Blanc ? joueur=Noir : joueur =Blanc;
        return true;
}
Jeu::~Jeu(){
    cout << "destructeur jeux " << endl;
}

