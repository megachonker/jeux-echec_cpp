#pragma once


class Echiquier; // forfward declaration

#include <iostream>
#include "piece.hh"
#include "square.hh"


enum erreurDeplacement{
    ok,
    srcvide,
    appartenance,
    checkgeometric,
    collision,
    echeque
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

    bool pseudocheck(Piece * piece,Square position_dst,bool print_err=false)const;
    bool slidecheck(Piece * source,Square const position_dst);

    void pose_piece(Piece * piece);

    Piece * get_piece(Square const square)   const; //peut etre priver a la fin ?
    bool  est_case_vide(Square const square) const;

public:
    bool isstuck(Couleur couleur_joueur);
    void print_all_piece();
    bool chk_echec_roi(Couleur couleur_joueur);
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name,bool view_pawn=false,bool view_color=false) const;
    void affiche (Echiquier const * obj=nullptr) const;
    Square get_pos();
    erreurDeplacement deplace(Piece* piece, Square dst,Couleur couleur_joueur,bool print_err=false);
    erreurDeplacement deplace(Square piece, Square dst,Couleur couleur_joueur,bool print_err=false);
    Echiquier();
    Echiquier(const Echiquier &obj);
    ~Echiquier();
    void comparer(const Echiquier &obj);
};

