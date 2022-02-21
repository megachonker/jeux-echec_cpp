#pragma once
#include <string>
using namespace std;


bool saisie_correcte(string const & cmd);
bool saisie_correcte_petitroque(string const & cmd);

class Square
{
    public:
        short ligne, colone;
        Square(string const & position);
        ~Square();
};

