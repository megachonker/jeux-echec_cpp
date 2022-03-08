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
    ligne  = (char)position[1]-'1';
    colone = (char)position[0]-'a';
}

Square::Square(int ligne, int colone) : ligne(ligne),colone(colone)
{
    
}

std::string Square::to_string() const{
    return "colone: "+std::to_string(colone)+" Ligne: "+std::to_string(ligne);
}

bool Square::operator== (Square cmp) const{
    return (ligne==cmp.ligne)&&(colone==cmp.ligne);
}


////////////////////////////////////////////////
std::string couleur_to_str(Couleur ma_couleur){
    return ma_couleur==Blanc ? "Blanc" : "Noir";
}