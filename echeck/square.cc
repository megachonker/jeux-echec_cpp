#include <regex>
#include <string>
#include <iostream>
#include "square.hh"

#include "macro.hh"

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
{}

std::string Square::to_string() const{
    return std::to_string(colone)+":"+std::to_string(ligne);
}

bool Square::operator== (Square cmp) const{
    return ((ligne==cmp.ligne)&&(colone==cmp.colone));
}

Square Square::operator+ (Square add){
    return Square(ligne+add.ligne,colone+add.colone);
}

void Square::operator+=(Square cible){
    ligne = this->ligne + cible.ligne;
    colone = this->colone + cible.colone;
    // Square(ligne,colone) = Square(ligne,colone)+cible;
}

void Square::inv (){
    ligne*=-1;
}
void Square::swap(){
    int tmp = ligne;
    ligne = colone;
    colone = ligne;
}

bool Square::inside(){
    return (colone<8)&&(ligne<8);
}


/**
 * @brief determine dans quelle sens la piece bouge
 * 
 * @param source 
 * @param destination 
 * @return Square 
 */
Square sens_deplacement(Square source,Square destination){
        Square decalage;
        decalage.colone=source.colone<destination.colone ? 1 : -1;
        decalage.ligne=source.ligne<destination.ligne ? 1 : -1;

        if (source.colone==destination.colone)
            decalage.colone=0;
        if (source.ligne==destination.ligne)
            decalage.ligne=0;

        return decalage;
}

bool Square::around(int size){
    return abs(ligne)<=size && abs(colone)<=size;
}

Square Square::operator-(Square cible) const {
    return Square(ligne-cible.ligne,colone-cible.colone);
}

std::string Square::print_deplace(Square dst){
    return std::to_string(colone+1)+":"+std::to_string(ligne+1)+"->"+std::to_string(dst.colone+1)+":"+std::to_string(dst.ligne+1);
}



////////////////////////////////////////////////
std::string couleur_to_str(Couleur ma_couleur){
    return ma_couleur==Blanc ? "Blanc" : "Noir";
}
