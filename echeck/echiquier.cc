#include <iostream>
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include "jeu.hh" //include mouvement



using namespace std;




#include "macro.hh"



void Echiquier::pose_piece(Piece * piece){
        echiquier[piece->get_pos().ligne][piece->get_pos().colone]=piece;
}


/**
 * @brief déplace la piece 
 *      effectue les verification necessaire
 * attention les piece ne sont pas désaouler
 * @param piece 
 * @param dst 
 * @return true 
 * @return false 
 */
void Echiquier::deplace(Piece * piece, Square dst,bool offensif){

        //save encienne position
        Square old_pos = piece->get_pos();

        //on change ça position
        piece->deplace(dst);

        //supression de la piece position sur l'echequier
        echiquier[old_pos.ligne][old_pos.colone]=nullptr;
        //on place la piece sur lechequier
        echiquier[dst.ligne][dst.colone]=piece;


        if (offensif){
                //supression des piece dans les main des joueur
                for (size_t i = 0; i < 8; i++)
                {
                        if(piecesb[i]!=nullptr && piecesb[i]->get_pos()==old_pos)
                                piecesb[i]=nullptr;
                        if(piecesn[i]!=nullptr && piecesn[i]->get_pos()==old_pos)
                                piecesn[i]=nullptr;
                }
        }        

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
}


Echiquier::~Echiquier(){
        cout << "destructeur echiquier" << endl;

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


void Echiquier::affiche () const {

        string space5 = string(5,' ');
        cout << endl;
        cout << "     a     b     c     d     e     f     g     h    "<< endl;
        cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        for (int i(8-1);i>=0;i--) {
                cout << i+1 << " "; // numérotation ligne dans affichage
                for (int j(0);j<8;j++) {
                        cout << "|" ;
                        if (echiquier[i][j]) { 
                          cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                          echiquier[i][j]-> affiche();
                          cout << "\u0020" << " ";
                        }
                        else 
                                cout << space5;  // 2 ascii spaces
                }
                cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
                cout << endl;
        }
}

bool Echiquier::chk_echec_roi(Couleur couleur_joueur){
        Piece ** board_piece = couleur_joueur==Blanc ? piecesn: piecesb;
        Pion  ** board_pion  = couleur_joueur==Blanc ? pionsn : pionsb;
        Square pos_roi = (couleur_joueur==Blanc ? piecesb[4]: piecesn[4])->get_pos();
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

bool Echiquier::check(Piece * piece,Square position_dst){

        if(!pseudocheck(piece,position_dst)){
                cout << "pseudo check géometrique echouer" << endl;
                return false;
        }
        if (!slidecheck(piece,position_dst)){
                WARNING("les piece entre en colision");
                return false;
        }
        
        // check lecheque est le roi
        if(chk_echec_roi(piece->get_couleur())){
                cout << "mise en echeque" << endl;
                return false;
        }
                
        return true;
}


bool Echiquier::slidecheck(Piece *source,Square position_dst){
        
        if (source->get_type() != tour 
        &&  source->get_type() != fou 
        &&  source->get_type() != dame)
                return true;        
        
        Square origine = source->get_pos();
        Square decalage= sens_deplacement(origine,position_dst);

        DEBUG("origine avant: " << origine.to_string() << "décalage: " << decalage.to_string())

        origine+=decalage;
        while (est_case_vide(origine)){
                DEBUG("origine: " << origine.to_string() << "\tdestination: " << position_dst.to_string());
                if(origine==position_dst){
                        VERBEUX("slide ok")
                        return true;
                }
                origine+=decalage;
        }
        
        return false;
}

bool Echiquier::pseudocheck(Piece * piece,Square position_dst)const{
        if (get_piece(position_dst) != nullptr)   //test si dest est une piece
        {
                //destination moi
                if(get_piece(position_dst)->get_couleur()!=piece->get_couleur()){//test couleur opposer)
                        cout << "vous pouvez pas manger vos propre piece" << endl;
                        return false;
                }
                // test déplacement agressif
                else
                        if(!piece->check_dst(position_dst,true))
                                return false;
        }
        //case vide
        else
                //test deplacement
                if(!piece->check_dst(position_dst,false))
                        return false;
        return true;
}