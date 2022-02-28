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
        short ligne, colone;
        Square(std::string const position);
        Square(int ligne, int colone);
        std::string to_string() const;
        // ~Square();
};

