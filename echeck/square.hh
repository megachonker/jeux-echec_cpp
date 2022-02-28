#pragma once
#include <string>

bool saisie_correcte(std::string const & cmd);
bool saisie_correcte_petitroque(std::string const & cmd);

class Square
{
    public:
        short ligne, colone;
        Square(std::string const position);
        // ~Square();
};

