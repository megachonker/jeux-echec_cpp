#pragma once
#include <iostream>
#include "piece.hh"
#include "square.hh"
using namespace std;

class Echiquier
{
private:
    Piece * echiquier[8][8];
    // Piece *** echiquier;
public:
    bool  est_case_vide(Square const square) const;
    Piece * get_piece(Square const square)   const;
    string canonical_position() const;
    string pgn_piece_name(string const name, bool view_pawn, bool view_color) const;


    Echiquier();
    ~Echiquier();
};
