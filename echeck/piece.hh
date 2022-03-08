#pragma once
#include <string>
#include "square.hh"


//15 avrille
class Piece
{
protected:
    std::string nom;
    Couleur couleur;
    Square position; // a metre a jour
public:
    virtual bool deplace(Square dst)=0;
    std::string to_string() const;
    void affiche() const;
    Piece(std::string nom, Couleur couleur, Square position);
    Square get_pos();
    Couleur get_couleur();
    virtual ~Piece(){};
};


class Pion : public Piece
{
    private:
        bool vierge;
        bool deplace(Square dst);
        bool mangerdiag(Square dst);
    public:
        std::string to_string() const;
        Pion(Couleur couleur,Square position,bool vierge); 
};

class Tour : public Piece
{
    private:
        bool deplace(Square dst);
    public:
        Tour(Couleur couleur,Square position);
};

class Fou : public Piece
{
    private:
        bool deplace(Square dst);
    public:
        Fou(Couleur couleur,Square position);
};

//   if      (name=="\u2656") psymb="R";  // Rook W
//   else if (name=="\u2658") psymb="N";  // Knight W
//   else if (name=="\u2657") psymb="B";  // Bishop W
//   else if (name=="\u2655") psymb="Q";  // Queen W
//   else if (name=="\u2654") psymb="K";  // King W


// pion fout cavalier renet toure  rois 
// \u2656
// \u2658
// \u2657
// \u2655
// \u2654