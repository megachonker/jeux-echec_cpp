#pragma once
#include <string>
#include "square.hh"

enum typePc{
    piece,
    pion,
    tour,
    fou,
    cavalier,
    dame,
    roi
};

//15 avrille
class Piece
{
protected:
    bool colisionvalide;//utile ?
    bool colisionmap_map[8][8];//a déclarer que dans eles bonne classe

    std::string nom;
    Couleur couleur;
    Square position; // a metre a jour
public:
    virtual bool get_colision(Square test) const; //doit etre utiliser que par les bonne piece
    virtual typePc Piece::get_type() const =0;
    virtual void deplace(Square dst);
    virtual bool check_dst(Square dst) const =0;
    virtual bool check_dst(Square dst,bool offensif) const;
    std::string to_string() const;
    void affiche() const;
    Piece(std::string nom, Couleur couleur, Square position);
    Square get_pos()const;
    Couleur get_couleur()const;
    virtual ~Piece(){};
};


class Pion : public Piece
{
    private:
        bool vierge;
        bool mangerdiag(Square dst) const;
    public:
        virtual typePc get_type() const override;
        void deplace(Square dst) override; 
        bool check_dst(Square dst) const override ;
        bool check_dst(Square dst,bool aggresssion) const override ;
        std::string to_string() const;
        Pion(Couleur couleur,Square position,bool vierge); 
};

class Tour : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst) const override;
        Tour(Couleur couleur,Square position);
        virtual ~Tour(){}
};

class Fou : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst) const override;
        Fou(Couleur couleur,Square position);
        virtual ~Fou(){}
};

class Cavalier : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst) const override ;
        Cavalier(Couleur couleur,Square position);
        virtual ~Cavalier(){}
};

class Dame : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst) const override;
        Dame(Couleur couleur,Square position);
        virtual ~Dame(){}
};

class Roi : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst) const override;
        Roi(Couleur couleur,Square position);
        virtual ~Roi(){}
};

