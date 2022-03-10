#pragma once
#include <iostream>
#include "piece.hh"
#include "square.hh"
#include "jeu.hh"//pour mouvement

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
    bool check(struct mouvement move)const;
    bool pseudocheck(struct mouvement move)const;
    bool slidecheck(Piece &source,direction direction)const;
    bool slidecheck(Piece &source);
    bool gen_colimap(Piece &source);



    bool  est_case_vide(Square const square) const;
    Piece * get_piece(Square const square)   const; //peut etre priver a la fin ?
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name,bool view_pawn=false,bool view_color=false) const;
    void affiche () const;
    Square get_pos();
    void pose_piece(Piece * piece);
    void deplace(Piece * piece, Square const dst,bool offensif);
    Echiquier();
    ~Echiquier();
};


enum direction{
        lignecolone,
        diagonal
};

