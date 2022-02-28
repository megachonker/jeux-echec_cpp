#pragma once
#include <iostream>
#include "piece.hh"
#include "square.hh"

class Echiquier
{
private:
    Piece * echiquier[8][8];
    // Piece *** echiquier;
public:
    bool  est_case_vide(Square const square) const;
    Piece * get_piece(Square const square)   const;
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name, bool view_pawn, bool view_color) const;


    Echiquier();
    // ~Echiquier();
};
