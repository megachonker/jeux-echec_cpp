// #include <cstdio>
#include <iostream>
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"

using namespace std;

void Echiquier::pose_piece(Piece * piece){
        echiquier[piece->get_pos().ligne][piece->get_pos().colone]=piece;
}


bool Echiquier::deplace(Piece * piece, Square const dst){
        Square old_pos = piece->get_pos();
        if (piece->deplace(dst)==false)
                return false;

        cout << "vrite position" << endl;

        echiquier[old_pos.ligne][old_pos.colone]=nullptr;
        echiquier[dst.ligne][dst.colone]=piece;

        return true;
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
        // piecesb[1] = new Cavalier(Blanc ,Square(0,1));
        // piecesb[2] = new Fou     (Blanc ,Square(0,2));
        // piecesb[3] = new Dame    (Blanc ,Square(0,3));
        // piecesb[4] = new Roi     (Blanc ,Square(0,4));
        // piecesb[5] = new Fou     (Blanc ,Square(0,5));
        // piecesb[6] = new Cavalier(Blanc ,Square(0,6));
        piecesb[7] = new Tour    (Blanc ,Square(0,7));
        piecesn[0] = new Tour    (Noir  ,Square(7,0));
        // piecesn[1] = new Cavalier(Noir  ,Square(7,1));
        // piecesn[2] = new Fou     (Noir  ,Square(7,2));
        // piecesn[3] = new Dame    (Noir  ,Square(7,3));
        // piecesn[4] = new Roi     (Noir  ,Square(7,4));
        // piecesn[5] = new Fou     (Noir  ,Square(7,5));
        // piecesn[6] = new Cavalier(Noir  ,Square(7,6));
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
                if ( pionsb[i] != nullptr)
                        delete pionsb[i];
        
                if ( pionsn[i] != nullptr)        
                        delete pionsn[i];
        
                if(piecesb[i] != nullptr)
                        delete piecesb[i];
                        
                if(piecesn[i] != nullptr)
                        delete piecesn[i];
                
        }
        
        // delete [] pionsb;
        // delete [] pionsn;
}


Piece * Echiquier::get_piece(Square const square)const{
        return echiquier[square.ligne][square.colone];
}

bool Echiquier::est_case_vide(Square const square) const{
        if(get_piece(square) == nullptr)
                return true;
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
