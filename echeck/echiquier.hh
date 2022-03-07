#pragma once
#include <iostream>
#include "piece.hh"
#include "square.hh"

class Echiquier
{
private:
    Piece * echiquier[8][8];
    //faire des vecteur comme un clochard
    Pion  * pionsb[8];//nombre de Pion par joueur
    Pion  * pionsn[8];
    Piece * piecesb[8];//nombre de Piece par joueur
    Piece * piecesn[8];
public:
    bool  est_case_vide(Square const square) const;
    Piece * get_piece(Square const square)   const;
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name, bool view_pawn, bool view_color) const;
    void affiche () const;
    Square get_pos();
    void pose_piece(Piece * piece);
    bool deplace(Piece * piece, Square const dst);
    Echiquier();
    // ~Echiquier();
};
