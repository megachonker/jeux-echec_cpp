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
    echeque,
    dejabougerR,
    dejabougerT,
    TK,
    prisepasantfail
};


struct main_joueur
{
        Piece ** board_piece;
        Piece ** board_pion;
        char sens;
};

class Echiquier
{
private:
    Piece * echiquier[8][8];
    //faire des vecteur comme un clochard
    Pion  * pionsb[8];//nombre de Pion par joueur
    Pion  * pionsn[8];
    Piece * piecesb[16];//nombre de Piece par joueur
    Piece * piecesn[16];
    Square pion_passant;
    Square bak_pion_passant;

    erreurDeplacement pseudocheck(Piece * piece,Square position_dst,bool print_err=false);
    bool slidecheck(Piece * source,Square const position_dst,bool force=false);

    erreurDeplacement move_piece(Piece * piece,Square position_dst,bool passant=false);

    //opti ?
    void pose_piece(Piece * piece);
    void pose_piece(Piece * piece,Piece * dst);
    void pose_piece(Piece * piece,Square  dst);
    
    void vider_case(Piece * piece);
    void vider_case(Square piece);

    Piece * get_piece(Square const square)   const; //peut etre priver a la fin ?
    bool  est_case_vide(Square const square) const;

    main_joueur get_main_joueur(Couleur couleur);

    void del_board_piece(Piece * pos_piece);
    void del_board_piece(Square pos_piece);
    void del_board_piece(Piece * piece, Piece * address_piece_effacer);
    void del_board_piece(Square pos_piece, Piece * address_piece_effacer);
public:
    erreurDeplacement rocker(Couleur couleur,bool grand);
    Square get_pos();
    bool isstuck(Couleur couleur_joueur);
    bool chk_echec_roi(Couleur couleur_joueur);
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name,bool view_pawn=false,bool view_color=false) const;
    erreurDeplacement deplace(Piece* piece, Square dst,Couleur couleur_joueur,bool print_err=false);
    erreurDeplacement deplace(Square piece, Square dst,Couleur couleur_joueur,bool print_err=false);
    bool promote(Square piece);
    Echiquier();
    Echiquier(const Echiquier &obj);
    ~Echiquier();
    void affiche (Echiquier const * obj=nullptr) const;
    void print_all_piece();
    void comparer(const Echiquier &obj);
    void rst_passant();
};

