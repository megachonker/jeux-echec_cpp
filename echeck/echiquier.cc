#include <iostream>
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include "jeu.hh" //include mouvement


using namespace std;
#include "macro.hh"



void Echiquier::pose_piece(Piece * piece,Piece * dst){
        pose_piece(piece,dst->get_pos());
}

void Echiquier::pose_piece(Piece * piece,Square  dst){
        echiquier[dst.ligne][dst.colone]=piece;
}

void Echiquier::pose_piece(Piece * piece){
        pose_piece(piece,piece);
}


erreurDeplacement Echiquier::deplace(Piece * piece, Square dst,Couleur couleur_joueur,bool print_err){
        if (!piece)
                return srcvide;        
        return deplace(piece->get_pos(),dst,couleur_joueur,print_err);
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
                for (size_t i = 0; i < 8; i++)
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

erreurDeplacement Echiquier::move_piece(Piece * piece,Square position_dst,bool passant){
        Couleur couleur_joueur = piece->get_couleur();
////backup

        //addresse pour save
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
        VERBEUX("check lecheque est le roi");
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
                return echeque;
        }

        //suprime la piece de la mémoire
        delete old_piece;
        return ok;
}


erreurDeplacement Echiquier::deplace(Square position_src, Square position_dst,Couleur couleur_joueur,bool print_err){

//fc check

        //piece origine non vide
        if (est_case_vide(position_src)==true)
            return srcvide;

        //joue une piece a luit (modifier si troc)
        if( get_piece(position_src)->get_couleur()!=couleur_joueur)
            return appartenance;

        Piece * piece = get_piece(position_src);

        if(!pseudocheck(piece,position_dst,print_err))
                return checkgeometric;

        bool prise_passant = (piece->get_type()==pion && pion_passant != Square(0,0) && position_dst == pion_passant+Square((piece->get_couleur()==Noir ? -1: 1),0));

        if (!slidecheck(piece,position_dst))
                return collision;


        return move_piece(piece,position_dst);

}

Echiquier::Echiquier () 
{
        for (size_t y = 0; y < 8; y++){
                for (size_t x = 0; x < 8; x++)
                        echiquier[x][y] = nullptr;
                piecesb[y] = nullptr;
                piecesn[y] = nullptr;
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
        }
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

                        if (obj && !(obj->echiquier[i][j] && (obj->echiquier[i][j]->to_string()==echiquier[i][j]->to_string())))
                        {
                                cout << YELLO();
                                echiquier[i][j]-> affiche();
                                cout << CLRCOLOR();
                        }
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

bool Echiquier::chk_echec_roi(Couleur couleur_joueur){
        Square pos_roi = (couleur_joueur==Blanc ? piecesb[4]->get_pos() : piecesn[4]->get_pos());
        Piece ** board_piece = couleur_joueur==Blanc ? piecesn: piecesb;
        Pion  ** board_pion  = couleur_joueur==Blanc ? pionsn : pionsb;        
        for (short i = 0; i < 8; i++)
        {
                
                //piece ataque roi
                if (board_piece[i] != nullptr
                && pseudocheck(board_piece[i],pos_roi)
                && slidecheck(board_piece[i],pos_roi))
                        return true;
        
                //pion attaque un roi
                if (board_pion[i] != nullptr
                && pseudocheck(board_pion[i],pos_roi) 
                && slidecheck(board_pion[i],pos_roi))
                        return true;
        }
        return false;
}

bool Echiquier::slidecheck(Piece *source,Square position_dst,bool force){

        if (!force)
        {
                if (source->get_type() != tour 
                &&  source->get_type() != fou 
                &&  source->get_type() != dame)
                        return true; 
        }

        Square origine = source->get_pos();
        Square decalage= sens_deplacement(origine,position_dst);
        DEBUG("Déplacemnt de: "<< source->typePc_to_string() << "\t" << origine.to_string() << "==>"<< position_dst.to_string() << "\tdécalage: " << decalage.to_string());
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

bool Echiquier::pseudocheck(Piece * piece,Square position_dst, bool print_err){
        if (get_piece(position_dst) != nullptr)   //test si dest est une piece
        {
                //destination moi
                if(get_piece(position_dst)->get_couleur()==piece->get_couleur()){//test couleur opposer)
                        if(print_err)
                                WARNING("vous pouvez pas manger vos propre piece");
                        return false;
                }
                // test déplacement agressif
                else
                        if(!piece->check_dst(position_dst,true,print_err))
                                return false;
        }
        //case vide
        else{
                // //autorise le mouvement diagonal si la prise en passante est valide
                if (pion_passant != Square(0,0) && position_dst == pion_passant+Square((piece->get_couleur()==Noir ? -1: 1),0))
                        return piece->check_dst(position_dst,true,print_err);
                

                //test deplacement standar
                if(!piece->check_dst(position_dst,false,print_err))
                        return false;

                //si la piece est un pion
                if(piece->get_type()==pion){
                        Square devant_pion = piece->get_pos()+Square((piece->get_couleur()==Noir ? -1: 1),0);
                        Square devant_devant_pion = devant_pion+Square((piece->get_couleur()==Noir ? -1: 1),0);
                        
                        //déplace de 2 ver l'avant
                        if(position_dst == devant_devant_pion){
                                //verifie si le pion rentre en colision pendant son déplacement
                                if(!est_case_vide(devant_pion))
                                                return false;
                                //le pion avancant de 2 il est candidat pour etre passant 
                                pion_passant = position_dst;
                        }
                }
        }
        return true;
}


void Echiquier::print_all_piece(){
        DEBUG("Piece des joueur !");
        INFO("Piece blanche");
        cout << YELLO() << "Piece\t" << CLRCOLOR();
        for (size_t i = 0; i < 8; i++)
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
        for (size_t i = 0; i < 8; i++)
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
 * @brief tester si la partie est fini
 * 
 * test tout les mouvement possible d'un joueur
 * 
 * @return true 
 * @return false 
 */
bool Echiquier::isstuck(Couleur couleur_joueur){
        Piece ** board_piece = couleur_joueur==Noir ? piecesn: piecesb;
        Piece ** board_pion  = (Piece**)(couleur_joueur==Noir ? pionsn : pionsb);
        //l'idée de cache mis en place aurait pus etre efficace...
        for (int u = 0; u < 8; u++)
        for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
        {
                if (    (deplace(board_pion[u],Square(x,y),couleur_joueur)==ok)
                ||      (deplace(board_piece[u],Square(x,y),couleur_joueur)==ok))
                        return true;                                                              
        }

        return false;
}

Echiquier::Echiquier(const Echiquier &obj){
        VERBEUX("constructeur copy Echiquier");
        for (size_t y = 0; y < 8; y++){
                for (size_t x = 0; x < 8; x++)
                        echiquier[x][y] = nullptr;
                piecesb[y] = nullptr;
                piecesn[y] = nullptr;
                pionsb[y]  = nullptr;
                pionsn[y]  = nullptr;
        }

        for (int i = 0; i < 8; i++)
        {
                if(obj.piecesb[i]!=nullptr){
                        piecesb[i] = obj.piecesb[i]->Clone();
                        pose_piece(piecesb[i]);
                }

                if(obj.piecesn[i]!=nullptr){
                        piecesn[i] = obj.piecesn[i]->Clone();
                        pose_piece(piecesn[i]);
                }

                if (obj.pionsb[i]!=nullptr){
                        pionsb[i] = new Pion(*obj.pionsb[i]);
                        pose_piece(pionsb[i]);
                }

                if (obj.pionsn[i]!=nullptr){
                        pionsn[i] = new Pion(*obj.pionsn[i]);
                        pose_piece(pionsn[i]);
                }
        }      
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