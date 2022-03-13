#pragma once
#include <string>

enum Couleur{
    Blanc,
    Noir
};

bool saisie_correcte(std::string const & cmd);
bool saisie_correcte_petitroque(std::string const & cmd);

class Square
{
    public:
        short ligne, colone;//checker si priver bon
        Square(std::string const position);
        Square(int ligne, int colone);
        std::string to_string() const;
        bool operator== (Square cmp)const;
        // void operator= (Square cmp);
        Square operator+ (Square add);
        void operator+=(Square cible);
        void inv ();
        void swap();
        bool inside();
        // ~Square();
};

///////////////////
std::string couleur_to_str(Couleur ma_couleur);