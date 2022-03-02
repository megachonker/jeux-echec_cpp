#pragma once
#include <string>
#include "square.hh"


//15 avrille
class Piece
{
protected:
    short uid;//numeroter de 0 a 32
    std::string nom;
    Couleur couleur;
    Square position; // a metre a jour
    // virtual void deplace(Square dst)=0; //fonction abstraite pure <== peut pas
    virtual void deplace(Square dst); //fonction abstraite pure
public:
    std::string to_string() const;
    void affiche() const;
    Piece(std::string nom, Couleur couleur, Square position);
    Square get_pos();
    // ~Piece();
};

// get_pos

class Pion : public Piece
{
    private:
        void deplace(Square dst);
    public:
        Pion(Couleur couleur,Square position);
};
// class Toure : public Piece
// {}

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