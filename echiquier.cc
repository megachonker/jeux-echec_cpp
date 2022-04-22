#include <iostream>
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include "jeu.hh" //include mouvement


using namespace std;
#include "macro.hh"

//avance d'une ligne dans le plateaux en fonction du joueur
#define AVANCE1BONSENS  Square((piece->get_couleur()==Noir ? -1: 1),0)

/**
 * @brief Construct a new Echiquier:: Echiquier object
 * 
 */
Echiquier::Echiquier () 
{
        for (size_t y = 0; y < 8; y++){
                for (size_t x = 0; x < 8; x++)
                        echiquier[x][y] = nullptr;
                piecesb[y] = piecesb[15-y] = nullptr;
                piecesn[y] = piecesn[15-y] = nullptr;
        }
        piecesb[0] = new Tour    (Blanc ,Square(0,0));
        piecesb[1] = new Cavalier(Blanc ,Square(0,1));
        piecesb[2] = new Fou     (Blanc ,Square(0,2));
        piecesb[3] = new Dame    (Blanc ,Square(0,3));
        piecesb[4] = new Roi     (Blanc ,Square(0,4));
        piecesb[5] = new Fou     (Blanc ,Square(0,5));
        piecesb[6] = new Cavalier(Blanc ,Square(0,6));
        piecesb[7] = new Tour    (Blanc ,Square(0,7));
        piecesn[0] = new Tour    (Noir  ,Square(7,0));
        piecesn[1] = new Cavalier(Noir  ,Square(7,1));
        piecesn[2] = new Fou     (Noir  ,Square(7,2));
        piecesn[3] = new Dame    (Noir  ,Square(7,3));
        piecesn[4] = new Roi     (Noir  ,Square(7,4));
        piecesn[5] = new Fou     (Noir  ,Square(7,5));
        piecesn[6] = new Cavalier(Noir  ,Square(7,6));
        piecesn[7] = new Tour    (Noir  ,Square(7,7));

        // allocation des pions
        for (unsigned char i(0);i<8;i++) {
                pionsb[i] =  new Pion(Blanc     , Square(1,i),true);
                pionsn[i] =  new Pion(Noir      , Square(6,i),true);
                pose_piece(pionsn[i]);
                pose_piece(pionsb[i]);
        }
        // pose des pieces blanches
        for (unsigned char i(0);i<8;i++){       //on part du principe qu'il y a 8 piece spécial blance !
                if(piecesb[i]!=nullptr)
                        pose_piece(piecesb[i]);   
        }
        // puis pose des pièces noires, pions blancs, pions noirs
        for (unsigned char i(0);i<8;i++){
                if(piecesn[i]!=nullptr)
                        pose_piece(piecesn[i]);   
        }

        //valeur inateignable 0,0 
        bak_pion_passant = pion_passant = Square(0,0);
}

/**
 * @brief duplicate a new Echiquier:: Echiquier object
 * 
 * @param obj 
 */
Echiquier::Echiquier(const Echiquier &obj){
        VERBEUX("constructeur copy Echiquier");
        for (size_t y = 0; y < 8; y++){
                for (size_t x = 0; x < 8; x++)
                        echiquier[x][y] = nullptr;
                piecesb[y] = piecesb[15-y] = nullptr;
                piecesn[y] = piecesn[15-y] = nullptr;
                pionsb[y]  = nullptr;
                pionsn[y]  = nullptr;
        }

        for (int i = 0; i < 8; i++)
        {

                if(obj.piecesb[15-i]!=nullptr){
                        piecesb[15-i] = obj.piecesb[15-i]->Clone();
                        pose_piece(piecesb[15-i]);
                }

                if(obj.piecesn[15-i]!=nullptr){
                        piecesn[15-i] = obj.piecesn[15-i]->Clone();
                        pose_piece(piecesn[15-i]);
                }

                if(obj.piecesb[i]!=nullptr){
                        piecesb[i] = obj.piecesb[i]->Clone();
                        pose_piece(piecesb[i]);
                }

                if(obj.piecesn[i]!=nullptr){
                        piecesn[i] = obj.piecesn[i]->Clone();
                        pose_piece(piecesn[i]);
                }

                if (obj.pionsb[i]!=nullptr){
                        pionsb[i] =  (Pion*)obj.pionsb[i]->Clone();
                        // pionsb[i] = new Pion(*obj.pionsb[i]);
                        pose_piece(pionsb[i]);
                }

                if (obj.pionsn[i]!=nullptr){
                        pionsn[i] =  (Pion*)obj.pionsn[i]->Clone();
                        // pionsn[i] = new Pion(*obj.pionsn[i]);
                        pose_piece(pionsn[i]);
                }
        }
        
        //valeur inateignable 0,0 
        bak_pion_passant = pion_passant = Square(0,0);
}

/**
 * @brief Destroy the Echiquier:: Echiquier object
 * 
 */
Echiquier::~Echiquier(){
        VERBEUX("destructeur echiquier");

        for (unsigned char i(0);i<8;i++) {
                if (pionsb[i] != nullptr)
                        delete pionsb[i];
        
                if (pionsn[i] != nullptr)        
                        delete pionsn[i];
        
                if(piecesb[i] != nullptr)
                        delete piecesb[i];
                        
                if(piecesn[i] != nullptr)
                        delete piecesn[i];

                if(piecesb[15-i] != nullptr)
                        delete piecesb[15-i];
                        
                if(piecesn[15-i] != nullptr)
                        delete piecesn[15-i];
        }
}

void Echiquier::pose_piece(Piece * piece,Piece * dst){
        pose_piece(piece,dst->get_pos());
}

void Echiquier::pose_piece(Piece * piece,Square  dst){
        echiquier[dst.ligne][dst.colone]=piece;
}

void Echiquier::pose_piece(Piece * piece){
        pose_piece(piece,piece);
}

void Echiquier::del_board_piece(Piece * old_piece,Piece * address_piece_effacer){

        //supression de la piece dans la main des joueur
        //piece destination existe
        if (old_piece){
                //supression des piece dans les main des joueur

                //génération des board en fonction de la couleur du joueur
                Couleur couleur_joueur=old_piece->get_couleur()==Blanc ? Noir : Blanc;
                Piece ** board_piece = couleur_joueur==Blanc ? piecesn: piecesb;
                Pion  ** board_pion  = couleur_joueur==Blanc ? pionsn : pionsb;

                //choisie le bon tableuax dans lequelle la piece a suprimer appartien
                Piece ** tab_piece = (old_piece->get_type()==pion ? (Piece**)board_pion : board_piece);

                //on recherche la piece a effacer dans le tableaux
                for (size_t i = 0; i < 16; i++)
                {
                        //si une des piece dans la main a la meme position que la piece rechercher
                        if(tab_piece[i]!=nullptr && tab_piece[i]->get_pos() == old_piece->get_pos()){
                                address_piece_effacer = tab_piece[i];
                                tab_piece[i]=nullptr;
                                break;
                        }
                }
        }
}

void Echiquier::del_board_piece(Square pos_piece, Piece * address_piece_effacer){
        del_board_piece(get_piece(pos_piece),address_piece_effacer);
}
void Echiquier::del_board_piece(Square pos_piece){
        del_board_piece(pos_piece, get_piece(pos_piece));
}
void Echiquier::del_board_piece(Piece *  pos_piece){
        del_board_piece(pos_piece, pos_piece);
}


/**
 * @brief 
 * 
 * @param position_src 
 * @param position_dst 
 * @param couleur_joueur 
 * @param print_err indique s'il faut indiquer les erreur de déplacement (la fonction est utiliser par le joueur est par des test automatique donc il faut différencier)
 * @return erreurDeplacement 
 */
erreurDeplacement Echiquier::deplace(Square position_src, Square position_dst,Couleur couleur_joueur,bool print_err){
                //Vérification
        
        //piece origine non vide
        if (est_case_vide(position_src)==true)
            return srcvide;

        //joue une piece que le joueur possède
        if( get_piece(position_src)->get_couleur()!=couleur_joueur)
            return appartenance;

        //on sais que la piece selectioner est valide
        Piece * piece =  get_piece(position_src);
        
        //vérifie avec les règle de déplacent que la piece que le déplacement est possible
        VERBEUX("test déplacement logique");
        erreurDeplacement tmp;
        if( (tmp = pseudocheck(piece,position_dst,print_err)) !=ok)
                return tmp;

        //vérifie qu'il n'y a pas de colision pandant le déplacement de la piece
        DEBUG("test colision piece");
        if (!slidecheck(piece,position_dst))
                return collision;

        bool prise_passant = (piece->get_type()==pion && pion_passant != Square(0,0) && position_dst == pion_passant+AVANCE1BONSENS);
        return move_piece(piece,position_dst,prise_passant);
}


erreurDeplacement Echiquier::deplace(Piece * piece, Square dst,Couleur couleur_joueur,bool print_err){
        if (!piece)
                return srcvide;
        return deplace(piece->get_pos(),dst,couleur_joueur,print_err);
}

erreurDeplacement Echiquier::move_piece(Piece * piece,Square position_dst,bool passant){
        Couleur couleur_joueur = piece->get_couleur();

        Piece * address_pion_passant = nullptr;
        Piece * backup_passant;
        if (passant)
        {
                backup_passant = get_piece(pion_passant);
                vider_case(pion_passant);
                del_board_piece(backup_passant,address_pion_passant);

        }
        

////backup

        //addresse dans la main ou est la piece
        Piece * address_piece_effacer = nullptr;
        //save l'ancienne piece
        Piece * old_piece = get_piece(position_dst);


//fc deplace
        //supression de la piece position sur l'echequier
        vider_case(piece);
        //on place la piece sur lechequier
        pose_piece(piece,position_dst);
        //supression de la piece pour les joueur
        del_board_piece(old_piece,address_piece_effacer);
        //on change les coordoner dans la piece
        piece->deplace(position_dst);

//echeque
        DEBUG("Le rois est en ECHEQUE ?");
        if(chk_echec_roi(couleur_joueur)){
                //on déplace la piece a la position initial
                piece->undo_move();
                //restoration de la piece original
                pose_piece(piece);
                //restoration de la case dst
                pose_piece(old_piece,position_dst);
                //restoration de la piece dans la main joueur
                if(old_piece && address_piece_effacer)
                        address_piece_effacer=old_piece;
                if (passant)
                {
                        pose_piece(backup_passant);
                        address_pion_passant=backup_passant;
                }
                
                return echeque;
        }

        //suprime la piece de la mémoire
        if (passant)
                delete backup_passant;         
        delete old_piece;
        return ok;
}



Piece * Echiquier::get_piece(Square const square)const{
        return echiquier[square.ligne][square.colone];
}

bool Echiquier::est_case_vide(Square const square) const{
        if(get_piece(square) == nullptr){
                return true;
        }
        return false;
}

/**
 * @brief simule le déplacement d'une piece sur le plateaux
 * 
 * @param source 
 * @param position_dst 
 * @param force 
 * @return true 
 * @return false 
 */
bool Echiquier::slidecheck(Piece *source,Square position_dst,bool force){
        //sassure d'avoir une piece déplacable en diagonal avant de continue
        if (!force)
        {
                if (source->get_type() != tour 
                &&  source->get_type() != fou 
                &&  source->get_type() != dame)
                        return true; 
        }

        Square origine = source->get_pos();
        Square decalage= sens_deplacement(origine,position_dst);
        DEBUG("Déplacemnt de: "<< source->typePc_to_string() << "\t" << origine.to_string() << "==>"<< position_dst.to_string() << "\tdécalage: " << decalage.colone<<":"<<decalage.ligne);
        string chaine = origine.to_string();


        do{
                origine+=decalage;
                chaine+=" -> "+origine.to_string();

                if(origine==position_dst){
                        VERBEUX(chaine);
                        VERBEUX("slide OK");
                        return true;
                }
        }while (est_case_vide(origine));

        VERBEUX(chaine);
        VERBEUX("slide COLISION");
        return false;
}


/**
 * @brief vérifie que le déplacement LOGIQUE de la piece selon les règle de celle cis
 * - vérifie prise en passant
 * - set la prise en passant 
 * 
 * @param piece
 * @param position_dst 
 * @param print_err doit t'on afficher les erreur dans la sortie erreur
 * @return erreurDeplacement 
 */
erreurDeplacement Echiquier::pseudocheck(Piece * piece,Square position_dst, bool print_err){
        //si destination est une piece
        if (get_piece(position_dst) != nullptr)
        {
                //destination moi
                if(get_piece(position_dst)->get_couleur()==piece->get_couleur())//test couleur opposer)
                        return TK;
                // test déplacement agressif
                else
                        if(!piece->check_dst(position_dst,true,print_err))
                                return checkgeometric;
        }
        //allor case vide
        else{
                
                //autorise le mouvement diagonal si la prise en passante est valide
                if (
                    pion_passant != Square(0,0) &&                     //vérifie que la piece est initialiser
                    position_dst == (pion_passant+AVANCE1BONSENS))     //fait reculer le pion adverse pour tester la prise en pasant
                {
                        //vérification standar si la piece est prenable
                        if(piece->check_dst(position_dst,true,print_err))
                                return ok;
                        else
                                return prisepasantfail;
                }

                //test deplacement standar
                if(!piece->check_dst(position_dst,false,print_err))
                        return checkgeometric;

                //si la piece est un pion
                if(piece->get_type()==pion){
                        Square devant_pion = piece->get_pos()+AVANCE1BONSENS;
                        Square devant_devant_pion = devant_pion+AVANCE1BONSENS;
                        
                        //déplace de 2 ver l'avant unique
                        if(position_dst == devant_devant_pion){
                                //verifie si le pion rentre en colision pendant son déplacement
                                if(!est_case_vide(devant_pion))
                                                return collision;
                                //le pion avancant de 2 il est candidat pour etre passant
                                pion_passant = position_dst;
                        }
                }
        }
        return ok;
}

/**
 * @brief vérifie la mise en echeque du rois
 * 
 * @param couleur_joueur 
 * @return true 
 * @return false 
 */
bool Echiquier::chk_echec_roi(Couleur couleur_joueur){

        //remplacer par get_main_joueur ?
        Square pos_roi = (couleur_joueur==Blanc ? piecesb[4]->get_pos() : piecesn[4]->get_pos());
        VERBEUX("----chk_echec_roi----");
        VERBEUX("ROI Position:"<< pos_roi.to_string());
        Piece ** board_piece = couleur_joueur==Blanc ? piecesn: piecesb;
        Pion  ** board_pion  = couleur_joueur==Blanc ? pionsn : pionsb;        
        
        for (short i = 0; i < 16; i++)
        {
                
                //piece ataque roi
                if (board_piece[i] != nullptr
                && !pseudocheck(board_piece[i],pos_roi)
                && slidecheck(board_piece[i],pos_roi)){
                        VERBEUX("====ECHEQUE====");
                        return true;
                }
        
                //pion attaque un roi
                if (board_pion[i/2] != nullptr
                && !pseudocheck(board_pion[i/2],pos_roi) 
                && slidecheck(board_pion[i/2],pos_roi)){
                        VERBEUX("====ECHEQUE====");
                        return true;              
                }
        }
        VERBEUX("====Pas ECHEQUE====");
        return false;
}



/**
 * @brief tester si la partie est fini
 * 
 * test tout les mouvement possible d'un joueur
 * 
 * @return true 
 * @return false 
 */
bool Echiquier::isstuck(Couleur couleur_joueur,bool en_echeque){
        Piece ** board_piece = couleur_joueur==Noir ? piecesn: piecesb;
        Piece ** board_pion  = (Piece**)(couleur_joueur==Noir ? pionsn : pionsb);
        //l'idée de cache mis en place aurait pus etre efficace...
#ifndef DEBUG_ECHEQUE
        for (int u = 0; u < 16; u++)
        for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
        {
                if (    (deplace(board_pion[u/2],Square(x,y),couleur_joueur)==ok) //on check 2x les pion pas opti doit refaire une boucle 
                ||      (deplace(board_piece[u],Square(x,y),couleur_joueur)==ok))
                        return true;                                                              
        }
#else
        // swapcolor(couleur_joueur);
        INFO("PARTIE BLOQUER ?");
        INFO("Test deplacement pion");
        for (int u = 0; u < 8; u++){
                Piece* piece = board_pion[u];
                if (!piece)
                        break;
                INFO(piece->to_string());

                for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++){

                if    (deplace(board_pion[u-1],Square(x,y),couleur_joueur)==ok) // <========================= bug tres tres chelou il faut u-1 est rien d'autre ? ? ?? 
                        return true;
                 //on check 2x les pion pas opti doit refaire une boucle 


                
                        // if ((deplace(piece,Square(x,y),couleur_joueur)==ok))
                        // {
                        //         WARNING("NON BLOQUER");
                        //         return true;
                        // }
                }
        }
        INFO("Test deplacement piece");
        for (int u = 0; u < 16; u++){
                Piece* piece = board_piece[u];
                //on skip le test ou la piece n'existe pas 
                //ET quand le rois est en echeque est veux ce déplacer
                if (!piece || (u == 4 && en_echeque))
                        break;
                INFO(piece->to_string());

                for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++){
                        //le déplacemnet du fout a tuer la reine 
                        if (deplace(piece,Square(x,y),couleur_joueur)==ok)
                        {
                                WARNING("NON BLOQUER");
                                return true;
                        }
                }
        }

        
        WARNING("BLOQUER");
#endif
        return false;
}




erreurDeplacement Echiquier::rocker(Couleur couleur_joueur, bool grand){
        struct main_joueur mes_piece = get_main_joueur(couleur_joueur);
        Piece * mon_roi = mes_piece.board_piece[4];
        Piece * ma_tour;
        Square destination_roi;
        Square destination_tour;
        
        //check que les piece n'on jamais bouger
        if (!((Roi*)mon_roi)->isvierge())
                return dejabougerR;
        
        
        if (!grand)
        {
                ma_tour = mes_piece.board_piece[7];

                //check que les case sont prete
                destination_roi = Square(ma_tour->get_pos().ligne,ma_tour->get_pos().colone-1);
                destination_tour= Square(mon_roi->get_pos().ligne,mon_roi->get_pos().colone+1);

        }
        else if (grand)
        {
                ma_tour = mes_piece.board_piece[0];

                //check que les case sont prete
                Square  case_cavalier    = Square(ma_tour->get_pos().ligne,ma_tour->get_pos().colone+1);
                        destination_roi  = Square(ma_tour->get_pos().ligne,ma_tour->get_pos().colone+2);
                        destination_tour = Square(mon_roi->get_pos().ligne,mon_roi->get_pos().colone-1);
                
                //on aurait pus utiliser un slide check mais verifier la préseance de 3 piece est plus légée
                if (!est_case_vide(case_cavalier))
                        return collision;
        }             
        
        if (!est_case_vide(destination_roi) || !est_case_vide(destination_tour))
                return collision;

        if (!((Tour*)ma_tour)->isvierge())
                return dejabougerT;
        
        //delet de l'echiquier
        vider_case(ma_tour);
        vider_case(mon_roi);

        //met a jour les position de la piece
        mon_roi->deplace(destination_roi);
        ma_tour->deplace(destination_tour);

        //pose les piece sur le jeux
        pose_piece(mon_roi);
        pose_piece(ma_tour);
        
        return ok;
}


bool Echiquier::promote(Square piece){
        Piece * mapiece = get_piece(piece);
        Square position = mapiece->get_pos();
        if(mapiece->get_type()!=pion)
                return false;

        struct main_joueur mamain = get_main_joueur(mapiece->get_couleur());
        //convertion de + ou - en +1 ou 0
        char sens = (mamain.sens+1)/2;

        if ( sens*7 != position.ligne)
                return false;
        
        

        //detection l'emplacement du pion dans le board
        size_t i = 0;
        for (; i < 8; i++)
        {
                if( mamain.board_pion[i] != nullptr && mamain.board_pion[i]->get_pos() == mapiece->get_pos())
                        break;
        }

        Piece * newpiece;        

        switch (saisie_promotion())
        {
        case dame:
                newpiece = new Dame(mapiece->get_couleur(),mapiece->get_pos());
                break;
        case tour:
                newpiece = new Tour(mapiece->get_couleur(),mapiece->get_pos());
                break;
        case fou:
                newpiece = new Fou(mapiece->get_couleur(),mapiece->get_pos());
                break;
        case cavalier:
                newpiece = new Cavalier(mapiece->get_couleur(),mapiece->get_pos());
                break;
        default:
                WARNING("erreur switch promotion");
                break;
        }


        //remplacement visuel
        pose_piece(newpiece,mapiece);
        del_board_piece(mapiece);
        delete mapiece;

        //ajout de la nouvelle picece
        for (int i = 0; i<16; i++){
                if(mamain.board_piece[i]==nullptr){
                        mamain.board_piece[i] = newpiece;
                        break;
                }
        }
        // INFO(newpiece->to_string());
        // print_all_piece();

        return true;

}

main_joueur Echiquier::get_main_joueur(Couleur couleur_joueur){
        Piece ** board_piece = couleur_joueur==Noir ? piecesn: piecesb;
        Piece ** board_pion  = (Piece**)(couleur_joueur==Noir ? pionsn : pionsb);
        char sens = (couleur_joueur==Noir ? -1: 1);

        return main_joueur{ board_piece,board_pion,sens };
}



void Echiquier::vider_case(Piece * piece){
        vider_case(piece->get_pos());
}

void Echiquier::vider_case(Square posit){
        echiquier[posit.ligne][posit.colone]=nullptr;
}

void Echiquier::rst_passant(){
        if (pion_passant==bak_pion_passant)
                pion_passant = Square(0,0);
        bak_pion_passant=pion_passant;
}


void Echiquier::print_all_piece(){
        DEBUG("Piece des joueur !");
        INFO("Piece blanche");
        cout << YELLO() << "Piece\t" << CLRCOLOR();
        for (size_t i = 0; i < 16; i++)
        {
                if (piecesb[i] != nullptr)
                        piecesb[i]->affiche();
                cout << "\t";
        }
        cout << endl;
        cout << YELLO() << "Pion\t" << CLRCOLOR();
        for (size_t i = 0; i < 8; i++)
        {
                if (pionsb[i] != nullptr)
                        pionsb[i]->affiche();
                cout << "\t";
        }
        cout << endl;

        INFO("Piece Noir");
        cout << YELLO() << "Piece\t" << CLRCOLOR();
        for (size_t i = 0; i < 16; i++)
        {
                if (piecesn[i] != nullptr)
                        piecesn[i]->affiche();
                cout << "\t";
        }
        cout << endl;
        cout << YELLO() << "Pion\t" << CLRCOLOR();
        for (size_t i = 0; i < 8; i++)
        {
                if (pionsn[i] != nullptr)
                        pionsn[i]->affiche();
                cout << "\t";
        }
        cout << endl;
}

/**
 * @brief affiche le plataux avec les piece est les coup jouer pour le debug
 * 
 * @param obj 2ème plateaux a comarer
 */
void Echiquier::affiche (Echiquier const * obj) const {
        string space5 = string(5,' ');
        cout << endl;
        cout << "     a     b     c     d     e     f     g     h    "<< endl;
        cout << "  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐" << endl;
        for (int i(8-1);i>=0;i--) {
                cout << i+1 << " "; // numérotation ligne dans affichage
                for (int j(0);j<8;j++) {
                        cout << "│" ;
                        if (echiquier[i][j]) { 
                          cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                        //coup 
                        
                        //si 2eme plateaux on compare si la piece a bouger on print le déplacement en jaune
                        if (obj && !(obj->echiquier[i][j] && (obj->echiquier[i][j]->to_string()==echiquier[i][j]->to_string())))
                        {
                                cout << YELLO();
                                echiquier[i][j]-> affiche();
                                cout << CLRCOLOR();
                        }
                        //afichage du plataux standare
                        else
                                echiquier[i][j]-> affiche();

                          cout << "\u0020" << " ";
                        }
                        else 
                                cout << space5;  // 2 ascii spaces
                }
                if(i!=0)
                        cout << "│\n  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤";
                else
                        cout << "│\n  └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘";
                cout << endl;
        }

}

string Echiquier::canonical_position() const {
      string output;
      for (size_t row(1); row<=8; row++){
              for (char col('a');col<='h';col++) {
                      Square square(col+to_string(row)); 
                      if (!est_case_vide(square))
                              // get pieces with theit PGN names, 
                              // true -> with P for pawns, true -> w/b for colors.
                              output += pgn_piece_name(get_piece(square)->to_string(),true,true);
                      output += ",";
              }
      }
      return output;
}

 string Echiquier::pgn_piece_name(string const name, bool view_pawn, bool view_color) const {

    string psymb;
    if      (name=="\u2656") psymb="R";  // Rook W
    else if (name=="\u2658") psymb="N";  // Knight W
    else if (name=="\u2657") psymb="B";  // Bishop W
    else if (name=="\u2655") psymb="Q";  // Queen W
    else if (name=="\u2654") psymb="K";  // King W
    else if (name.rfind("\u2659",0)==0 && view_pawn) psymb= "P"; // Pawn W
    if (psymb.size()>0) { // one of the white piece has been found
            if (view_color)
                return "w"+psymb;
            else
                return psymb;
    } 
    if      (name=="\u265C") psymb= "R";  // Rook B
    else if (name=="\u265E") psymb= "N";  // Knight B
    else if (name=="\u265D") psymb= "B"; // Bishop B
    else if (name=="\u265B")  psymb= "Q"; // Queen B
    else if (name=="\u265A")  psymb= "K"; // King B
    else if (name.rfind("\u265F",0)==0 && view_pawn) psymb= "P"; // Pawn B
    if (psymb.size()>0) { // one of the black piece has been found
            if (view_color)
                return "b"+psymb;
            else
                return psymb;
    } 
    else return "";
}


