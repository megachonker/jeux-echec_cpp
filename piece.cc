#include "piece.hh"
#include <iostream>
#include <string>
#include "square.hh"

#include "macro.hh"

using namespace std;


/////////////
//  Piece  //
/////////////


Square Piece::get_pos()const{
    return position;
}

Piece::Piece(std::string nom, Couleur couleur,Square position): nom(nom),couleur(couleur),position(position){}

std::string Piece::get_nom(){
    return nom;
}

/**
 * @brief déplace la piece
 * 
 * peut être vue comme un setter de la position de la piece
 * 
 * @param dst   mouvement de déstination
 * @return true déplacement effectuer
 * @return false déplacement non effecif
 */
void Piece::deplace(Square dst){
    old_position = position;
    position=dst;
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

std::string Piece::typePc_to_string(){
    switch (get_type())
    {
    case pion:
        return "Pion";
    case tour:
        return "Tour";
    case fou:
        return "Fou";
    case cavalier:
        return "Cavalier";
    case dame:
        return "Dame";
    case roi:
        return "Roi";
    }
    return "TYPE NOT FOUND";
}

Couleur Piece::get_couleur()const{
    return couleur;
}


void Piece::undo_move(){
    Square tmp   = position;
    position     = old_position;
    old_position = tmp;
}
//////////////
//  PION    //
//////////////

Pion::Pion(Couleur couleur,Square position,bool vierge) 
: Piece(couleur==Blanc ? "\u2659" :"\u265F",couleur,position),vierge(vierge)
{old_vierge=false;}

Piece * Pion::Clone(){
    return new Pion(*this);
}

typePc Pion::get_type() const {return pion;}


/**
 * @brief test les mouvent d'attaque du pion
 * 
 * prend en compte si le pion a déja avancer
 * 
 * @param dst 
 * @return true 
 * @return false 
 */
bool Pion::mangerdiag(Square dst,bool print_err) const{
    //si noir on inverse le sens
    int sens = (couleur==Noir ? -1: 1);
    //portée effectif du coup
    int porter = position.ligne+sens;

    if(dst==Square(porter,position.colone+1)
    || dst==Square(porter,position.colone-1))
        return true;

    if(print_err)
        WARNING("déplacement offensif du pion invalide");
    return false;
}


bool Pion::check_dst(Square dst,bool offensif,bool print_err)const{
    if(offensif)
        return mangerdiag(dst,print_err);

    //si noir on inverse le sens
    int sens = couleur==Noir ? -1 : 1;
    int distance =  (dst.ligne-position.ligne)*sens;//distance parcourue
    if (distance<0)
    {
        if (print_err)
            WARNING("déplacement négatif");
        return false;
    }

    //check si le pion avance
    if (distance <= 0)
    {
        if (print_err)
            WARNING("check_dstment_null");
        return false;
    }

    
    if (position.colone!=dst.colone)
    {
        if (print_err)
            WARNING("le pion ne peut ce déplacer que en avant");
        return false;
    }

    if((vierge==true && distance<=2)||(distance<=1))
        return true;
    
    if (print_err)
        WARNING("déplacement imposible");
    return false;
}

string Pion::to_string() const{    
return  Piece::to_string()+"\n"+
        "vierge     :    "+(vierge==true?"Oui":"Non")+
        "\nold_vierge :    "+(old_vierge==true?"Oui":"Non");
}

/**
 * @brief réécriture du déplacement de piece
 * le pion étant la soeule piece qui possède un déplacement alternative s'il est agressif
 * dans la redéfinition on fait appelle a une fonction alternative mangerdiag
 * @param dst 
 * @return true 
 * @return false 
 */
void Pion::deplace(Square dst){
    Piece::deplace(dst);//verrification clasique
    old_vierge=vierge;
    vierge=false;
}

void Pion::undo_move(){
    Piece::undo_move();
    bool tmp   = vierge;
    vierge = old_vierge;
    old_vierge = tmp;
}

//////////////
//  Tour    //
//////////////

Tour::Tour(Couleur couleur,Square position,bool vierge) : Piece(couleur==Blanc ? "\u2656" :"\u265C",couleur,position),vierge(vierge){old_vierge=false;}

Piece * Tour::Clone(){
    return new Tour(*this);
}

typePc Tour::get_type() const {return tour;}


bool Tour::check_dst(Square dst,bool offensif,bool print_err) const  {
    (void)offensif;
    (void)print_err;

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

void Tour::deplace(Square dst){
    Piece::deplace(dst);//verrification clasique
    old_vierge=vierge;
    vierge=false;
}
bool Tour::isvierge(){
    return vierge;
}

string Tour::to_string() const{    
return  Piece::to_string()+"\n"+
        "vierge     :    "+(vierge==true?"Oui":"Non")+
        "\nold_vierge :    "+(old_vierge==true?"Oui":"Non");
}

void Tour::undo_move(){
    Piece::undo_move();
    bool tmp   = vierge;
    vierge = old_vierge;
    old_vierge = tmp;
}

//////////////
//  Fout    //
//////////////
 
Fou::Fou(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2657" :"\u265D",couleur,position){}

Piece * Fou::Clone(){
    return new Fou(*this);
}


typePc Fou::get_type() const{return fou;}

bool Fou::check_dst(Square dst,bool offensif,bool print_err) const {
    (void)offensif;
    (void)print_err;
    //check ratio de déplacement a 1
    if((abs((dst.colone-position.colone))==abs((dst.ligne-position.ligne)))==1){
        return true;
    }
    return false;
}

//////////////////
//  Cavalier    //
//////////////////
 
Cavalier::Cavalier(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2658" :"\u265E",couleur,position){}

Piece * Cavalier::Clone(){
    return new Cavalier(*this);
}


typePc Cavalier::get_type() const{return cavalier;}

bool Cavalier::check_dst(Square dst,bool offensif,bool print_err) const {
    (void)offensif;
    (void)print_err;
    return
    Square(position.ligne+2,position.colone+1) == dst ||
    Square(position.ligne+2,position.colone-1) == dst ||

    Square(position.ligne-2,position.colone+1) == dst ||
    Square(position.ligne-2,position.colone-1) == dst ||

    Square(position.ligne+1,position.colone+2) == dst ||
    Square(position.ligne-1,position.colone+2) == dst ||

    Square(position.ligne+1,position.colone-2) == dst ||
    Square(position.ligne-1,position.colone-2) == dst ;
    // Square(position.ligne+2,position.colone+1) == Square(abs(dst.ligne),abs(dst.colone));
}

//////////////
//  Dame    //
//////////////
 
Dame::Dame(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2655" :"\u265B",couleur,position){}

Piece * Dame::Clone(){
    return new Dame(*this);
}


typePc Dame::get_type() const{return dame;}

bool Dame::check_dst(Square dst,bool offensif,bool print_err) const {
    (void)offensif;
    (void)print_err;
    Fou F(couleur,position);
    Tour T(couleur,position);

    return  F.check_dst(dst)
        ||  T.check_dst(dst);
}



/////////////
//  Roi    //
/////////////

Roi::Roi(Couleur couleur,Square position,bool vierge) : Piece(couleur==Blanc ? "\u2654" :"\u265A",couleur,position),vierge(vierge){old_vierge=false;}

Piece * Roi::Clone(){
    return new Roi(*this);
}


typePc Roi::get_type() const{return roi;}

bool Roi::check_dst(Square dst,bool offensif,bool print_err) const {
    (void)offensif;
    (void)print_err;
    return (position-dst).around();
}        bool rock(bool grand);

void Roi::deplace(Square dst){
    Piece::deplace(dst);//verrification clasique
    old_vierge=vierge;
    vierge=false;
}

bool Roi::isvierge(){
    return vierge;
}

string Roi::to_string() const{    
return  Piece::to_string()+"\n"+
        "vierge     :    "+(vierge==true?"Oui":"Non")+
        "\nold_vierge :    "+(old_vierge==true?"Oui":"Non");
}

void Roi::undo_move(){
    Piece::undo_move();
    bool tmp   = vierge;
    vierge = old_vierge;
    old_vierge = tmp;
}