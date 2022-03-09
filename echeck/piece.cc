#include "piece.hh"
#include <iostream>
#include <string>
#include "square.hh"
#include "mad.h"//calcule absolut facilement

using namespace std;

Square Piece::get_pos(){
    return position;
}

Piece::Piece(std::string nom, Couleur couleur,Square position): nom(nom),couleur(couleur),position(position){}

/**
 * @brief déplace la piece
 * 
 *  met a jour ces coordoner si check_dst() est bon
 * 
 * peut être vue comme un setter de la position de la piece
 * 
 * @param dst   mouvement de déstination
 * @return true déplacement effectuer
 * @return false déplacement non effecif
 */
bool Piece::deplace(Square dst){
    //le déplacement est possible ?
    if (check_dst(dst)==true)
    {
        //metre a jour la position
        position=dst;
        return true;
    }
    return false;
}

string Piece::to_string() const{    
return  string("\n")+
        "noms:      "+nom+"\n"+
        "position:  "+ position.to_string()+"\n"+
        "couleur:   "+(couleur==Blanc?"Blanc":"Noir");
}

void Piece::affiche() const{
    cout << nom ;   
}
Couleur Piece::get_couleur(){
    return couleur;
}


//////////////
//  PION    //
//////////////

Pion::Pion(Couleur couleur,Square position,bool vierge) : Piece(couleur==Blanc ? "\u2659" :"\u265F",couleur,position),vierge(vierge)
{cout << to_string()<< endl;}


/**
 * @brief test les mouvent d'attaque du pion
 * 
 * prend en compte si le pion a déja avancer
 * 
 * @param dst 
 * @return true 
 * @return false 
 */
bool Pion::mangerdiag(Square dst) const{
    //a déja bouger ?
    char distance = (vierge==true ? 2 : 1);
    //si noir on inverse le sens
    char sens = (couleur==Noir ? -1: 1);
    //portée effectif du coup
    char porter = dst.colone+(distance*sens);

    if(dst==Square(position.ligne+1,porter)
    || dst==Square(position.ligne-1,porter))
        return true;

    cout << "déplacement offensif du pion invalide" << endl;
    return false;
}

/**
 * @brief vérifie géométriquement la fesabilitée d'un mouvement du pion
 * @param dst 
 * @return true 
 * @return false 
 */
bool Pion::check_dst(Square dst) const {

    int distance =  (dst.ligne-position.ligne)//distance parcourue
                    *(couleur==Noir ? -1 : 1);//si noir on inverse le sens

    //check si le pion avance
    if (distance <= 0)
    {
        cout << "check_dstment_null" << endl;
        return false;
    }

    if((vierge==true && distance<=2)||(distance<=1)||mangerdiag(dst))
        return true;
    
    cout << "déplacement imposible" << endl;
    return false;
}

string Pion::to_string() const{    
return  Piece::to_string()+"\n"+
        "vierge:    "+(vierge==true?"Oui":"Non");
}

/**
 * @brief 
 * @param dst 
 * @return true 
 * @return false 
 */
bool Pion::deplace(Square dst){
    if (!Piece::deplace(dst))
        return false;
    vierge=false;
    return true;
}


//////////////
//  Tour    //
//////////////

Tour::Tour(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2656" :"\u265C",couleur,position){}

bool Tour::check_dst(Square dst) const  {

    //jeu verifie que la src est destination ne sont pas les meme
    if(position.colone == dst.colone){
        return true;
    }
    else if (position.ligne == dst.ligne)
    {
        return true;
    }
    return false;
}

//////////////
//  Fout    //
//////////////
 
Fou::Fou(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2657" :"\u265D",couleur,position){}

bool Fou::check_dst(Square dst) const {
    //check ratio de déplacement a 1
    cout << "COLONE " << dst.colone-position.colone << "LIGNE" <<  dst.ligne-position.ligne << endl;
    if((abs((dst.colone-position.colone))/abs((dst.ligne-position.ligne)))==1){
        return true;
    }
    return false;
}

//////////////////
//  Cavalier    //
//////////////////
 
Cavalier::Cavalier(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2658" :"\u265E",couleur,position){}

bool Cavalier::check_dst(Square dst) const {
    return
    Square(position.ligne+2,position.colone+1) == dst ||
    Square(position.ligne+2,position.colone-1) == dst ||
    Square(position.ligne-2,position.colone+1) == dst ||
    Square(position.ligne-2,position.colone-1) == dst ||
    Square(position.colone+2,position.ligne+1) == dst ||
    Square(position.colone+2,position.ligne-1) == dst ||
    Square(position.colone-2,position.ligne+1) == dst ||
    Square(position.colone-2,position.ligne-1) == dst;
}

//////////////
//  Dame    //
//////////////
 
Dame::Dame(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2655" :"\u265B",couleur,position){}

bool Dame::check_dst(Square dst) const {
    Fou F(couleur,position);
    Tour T(couleur,position);

    return  F.check_dst(dst)
        ||  T.check_dst(dst);
}

/////////////
//  Roi    //
/////////////

Roi::Roi(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2654" :"\u265A",couleur,position){}

bool Roi::check_dst(Square dst) const {
    return
        Square(position.ligne+1,position.colone+1) == dst ||
        Square(position.ligne+1,position.colone-1) == dst ||
        Square(position.ligne-1,position.colone+1) == dst ||
        Square(position.ligne-1,position.colone-1) == dst;
}