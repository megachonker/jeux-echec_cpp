// #include <cstdio>
#include <iostream>
#include "echiquier.hh"
#include "square.hh"
#include "piece.hh"
#include "jeu.hh" //include mouvement
using namespace std;

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
void Echiquier::deplace(Piece * piece, Square dst,bool offensif=false){

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


bool Echiquier::check(mouvement move){

    if(!pseudocheck(move)){
        cout << "pseudo check géometrique echouer" << endl;
        return false;
    }
    if (!slidecheck(move.piece,move.position_dst))
    {
        cout << "pseudo check géometrique echouer" << endl;
        return false;
    }
    

    return true;
}



/**
 * @brief verifie les piece ayant des colision
 * 
 *      slidecheque pourait retourner une carte des collision est apres on verrifie si la piece dedant donc on fait le call de la map si elle existe pas !     
 * 
 *      pour plus de lisibilitée j'ai 2 énume qui veule dire les meme chause utile ?
 * @param source 
 * @param direction 
 * @return true 
 * @return false 
 */
bool Echiquier::slidecheck(Piece * source,Square const position_dst){

        //choix bonne piece
        switch (source->get_type())
        {
        case tour:      return  slidecheck(source,position_dst,lignecolone    );
        case fou:       return  slidecheck(source,position_dst,diagonal       );
        case dame:      return  slidecheck(source,position_dst,diagonal       ) 
                        ||      slidecheck(source,position_dst,lignecolone    );
        default: return true;
        }
        return true;
}

/**
 * @brief vérifie si le déplacemetn est possible sans colision
 * 
 * vérifie si la colymap est bonne puis vérifie le masque avec la position de destination si elle n'es pas bonne le regenère 
 * 
 * @param source 
 * @param position_dst 
 * @param look 
 * @return true 
 * @return false 
 */
bool Echiquier::slidecheck(Piece *source,Square position_dst,direction const look){
        if (!source->colisionvalide)
                clear_colimap(source);
                gen_colimap(source,look);
        
        if (source->get_colision(position_dst)){
                cout << "collision avec une piece !" << endl;
                return false;
        }
        
        return true;
}


void Echiquier::clear_colimap(Piece * source){
        for (size_t i = 0; i < 8; i++)
                for (size_t u = 0; u < 8; i++)
                        source->colisionmap_map[i][u]=false;
}


/**
 * @brief génère une carte des colision est raporte s'il y a eux colision
 * 
 * @param source 
 * @param look 
 * @return true 
 * @return false 
 */
void Echiquier::gen_colimap(Piece * source,direction look) {/////////////manque la colimap
        Square decalage = look==lignecolone ? Square(1,0) : Square(1,1);
        Square virtual_case = source->get_pos();

        slide(virtual_case,decalage);
        virtual_case.inv();
        slide(virtual_case,decalage);
        virtual_case.swap();
        slide(virtual_case,decalage);
}


/**
 * @brief va avancer la piece j'usqua une colision
 * 
 * @param origine enplacement pour tester
 * @param decalage direction du déplacement
 * @return true pas de colision
 * @return false il y a eux une colision
 */
void Echiquier::slide(Square origine,Square decalage){//ADD LA PÏCE
        //tan que la position a tester est dans le jeux decheque
        while (true){
                origine+=decalage;
                if (origine.inside())
                        break;
                if (est_case_vide(origine))
                        break;//on pourait set a la pice toucher l'info de l'ataquand  !
                set_colimap(origine);
                // colisionmap_map[]++++++++++++++ faire le masque
        }
}


void Echiquier::set_colimap(Square dst){
        //senser acceder au colimap
        
}

bool Echiquier::pseudocheck(mouvement move)const{
        if (get_piece(move.position_dst) != nullptr)   //test si dest est une piece
        {
                //destination moi
                if(get_piece(move.position_dst)->get_couleur()==move.couleur){//test couleur opposer)
                        cout << "vous avez selectioner une piece d'un autre joueur" << endl;
                        return false;
                }
                // test déplacement agressif
                else
                        if(!move.piece->check_dst(move.position_dst,(move.deplacement_aggressif=true)))
                        return false;
        }
        //case vide
        else
                //test deplacement
                if(!move.piece->check_dst(move.position_dst,false))
                        return false;
        return true;
}