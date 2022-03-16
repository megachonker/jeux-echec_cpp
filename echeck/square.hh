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
    private:
        void inv ();
        void swap();
        bool inside();
    public:
        short ligne, colone;//checker si priver bon

        Square(std::string const position);
        Square(int ligne=0, int colone=0);
        std::string to_string() const;
        bool operator== (Square cmp)const;
        Square operator+ (Square add);
        void operator+=(Square cible);
        std::string print_deplace(Square dst); //,Square src   =   BVITCH =Square(colone,ligne)

        // ~Square();
};

Square sens_deplacement(Square cible,Square destination);

///////////////////
std::string couleur_to_str(Couleur ma_couleur);