#include <regex>
#include "Echiquier.hh"
// #include <iostream>
using namespace std;

//lower avant

bool saisie_correcte(string const & cmd) {
regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);

}

bool saisie_correcte_petitroque(string const & cmd) {
regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

