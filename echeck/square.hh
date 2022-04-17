#pragma once
#include <string>

enum Couleur{
    Blanc=-1,
    Noir=1
};

enum typePc{
    pion,
    tour,
    fou,
    cavalier,
    dame,
    roi
};


void swapcolor(Couleur & couleur);


bool saisie_correcte(std::string const & cmd);
bool saisie_correcte_petitroque(std::string const & cmd);
bool saisie_correcte_grandroque(std::string const & cmd);
typePc saisie_promotion();

class Square
{
    private:
        void inv ();
        void swap();
        bool inside();
    public:
        bool around(int size=1);
        short ligne, colone;//checker si priver bon

        Square(std::string const position);
        Square(int ligne=0, int colone=0);
        std::string to_string() const;
        bool operator== (Square cmp)const;
        bool operator!= (Square cmp)const;
        Square operator+ (Square add);
        void operator+=(Square cible);
        Square operator-(Square cible)const;
        std::string print_deplace(Square dst); //,Square src   =   BVITCH =Square(colone,ligne)

        // ~Square();
};

Square sens_deplacement(Square cible,Square destination);

///////////////////
std::string couleur_to_str(Couleur ma_couleur);

Couleur operator!(Couleur couleur);
