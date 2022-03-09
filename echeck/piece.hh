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
    virtual bool deplace(Square dst,bool offensif);
    virtual bool check_dst(Square dst) const =0; //virtuel pure
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
        bool mangerdiag(Square dst) const;
    public:
        bool deplace(Square dst,bool offensif) override; 
        bool check_dst(Square dst) const override ;
        std::string to_string() const;
        Pion(Couleur couleur,Square position,bool vierge); 
};

class Tour : public Piece
{
    public:
        bool check_dst(Square dst) const override;
        Tour(Couleur couleur,Square position);
        virtual ~Tour(){}
};

class Fou : public Piece
{
    public:
        bool check_dst(Square dst) const override;
        Fou(Couleur couleur,Square position);
        virtual ~Fou(){}
};

class Cavalier : public Piece
{
    public:
        bool check_dst(Square dst) const override ;
        Cavalier(Couleur couleur,Square position);
        virtual ~Cavalier(){}
};

class Dame : public Piece
{
    public:
        bool check_dst(Square dst) const override;
        Dame(Couleur couleur,Square position);
        virtual ~Dame(){}
};

class Roi : public Piece
{
    public:
        bool check_dst(Square dst) const override;
        Roi(Couleur couleur,Square position);
        virtual ~Roi(){}
};

