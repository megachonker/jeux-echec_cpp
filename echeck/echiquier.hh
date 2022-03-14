#pragma once

class Echiquier; // forfward declaration

#include <iostream>
#include "piece.hh"
#include "square.hh"

enum direction{
        lignecolone,
        diagonal
};

class Echiquier
{
private:
    Piece * echiquier[8][8];
    //faire des vecteur comme un clochard
    Pion  * pionsb[8];//nombre de Pion par joueur
    Pion  * pionsn[8];
    Piece * piecesb[8];//nombre de Piece par joueur
    Piece * piecesn[8];

    bool pseudocheck(Piece * piece,Square position_dst)const;
    //classe ?
    bool slidecheck(Piece * source,Square const position_dst);
    bool slide(Square origine,Square decalage);
    
    bool chk_echec_roi(Square position_dst);


public:
    bool check(Piece * piece,Square position_dst);


    bool  est_case_vide(Square const square) const;
    Piece * get_piece(Square const square)   const; //peut etre priver a la fin ?
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name,bool view_pawn=false,bool view_color=false) const;
    void affiche () const;
    Square get_pos();
    void pose_piece(Piece * piece);
    void deplace(Piece * piece, Square dst,bool offensif=false);
    Echiquier();
    ~Echiquier();
};

