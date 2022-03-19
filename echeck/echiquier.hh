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

    bool check(Square position_src,Square position_dst,Couleur couleur_joueur);
    bool pseudocheck(Piece * piece,Square position_dst,bool print_err=false)const;
    bool slidecheck(Piece * source,Square const position_dst);
    bool slide(Square origine,Square decalage);

    void pose_piece(Piece * piece);
    bool chk_echec_roi(Piece ** board_piece,Pion ** board_pion,Square pos_roi);

    Piece * get_piece(Square const square)   const; //peut etre priver a la fin ?
    bool  est_case_vide(Square const square) const;

public:
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name,bool view_pawn=false,bool view_color=false) const;
    void affiche () const;
    Square get_pos();
    bool deplace(Square piece, Square dst,Couleur couleur_joueur);
    Echiquier();
    ~Echiquier();
};

