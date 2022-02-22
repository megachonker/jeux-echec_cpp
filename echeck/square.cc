#include <regex>
#include <string>
#include <iostream>
#include "square.hh"
using namespace std;

bool saisie_correcte(string const & cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);

}

bool saisie_correcte_petitroque(string const & cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}
                        //& ?
Square::Square(string const position)
{
    //a déplacer dans le ':' si ça marche
    ligne  = (char)position[1]-'0';
    colone = (char)position[0]-'a';
    cout << "colone " << colone << " ,ligne " << ligne << endl;
}

// Square::~Square()
// {
// }
