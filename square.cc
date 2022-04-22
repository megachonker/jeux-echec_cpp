#include <regex>
#include <string>
#include <iostream>
#include "square.hh"

#include "macro.hh"

using namespace std;

bool saisie_correcte(string const & cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]",regex_constants::icase);
    return regex_match(cmd,mouvmtpattern);

}

void swapcolor(Couleur & couleur){couleur = (couleur==Blanc ? Noir : Blanc);}


bool saisie_correcte_grandroque(string const & cmd) {
    regex mouvmtpattern("[Oo0]-[Oo0]-[Oo0]");
    return regex_match(cmd,mouvmtpattern);
}

bool saisie_correcte_petitroque(string const & cmd) {
    regex mouvmtpattern("[Oo0]-[Oo0]");
    return regex_match(cmd,mouvmtpattern);
}

//afaire
typePc saisie_promotion() {
    //on aurait pus utiliser un char mais on regle pas les débordement 
    string choix;
    INFO("{Q,R,B,K} pour respectivement promouvoir en Reine, Tour, Fou, Cavalier.");
    do
    {
        choix.clear();    
        cin >> choix;        
        switch (choix.at(0))
        {
        case 'Q':
            return dame;
        case 'R':
            return tour;
        case 'B':
            return fou;
        case 'K':
            return cavalier;
        default:
            WARNING("pas bonne piece choisie");
            break;
        }

    } while (true);
    return pion;
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
    return std::string(1,(char)colone+'A')+":"+std::to_string(ligne+1);
}

bool Square::operator== (Square cmp) const{
    return ((ligne==cmp.ligne)&&(colone==cmp.colone));
}

bool Square::operator!= (Square cmp)const{
    return !(*this==cmp);
}


Square Square::operator+ (Square add){
    return Square(ligne+add.ligne,colone+add.colone);
}

void Square::operator+=(Square cible){
    ligne = this->ligne + cible.ligne;
    colone = this->colone + cible.colone;
    // Square(ligne,colone) = Square(ligne,colone)+cible;
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
    return to_string()+"->"+dst.to_string();
}



////////////////////////////////////////////////
std::string couleur_to_str(Couleur ma_couleur){
    return ma_couleur==Blanc ? "Blanc" : "Noir";
}
