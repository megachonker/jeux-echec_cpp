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

    std::string nom;
    Couleur couleur;
    Square position; // a metre a jour
public:
    virtual typePc get_type() const =0;//peut etre enlever
    virtual void deplace(Square dst);
    virtual bool check_dst(Square dst) const =0;
    virtual bool check_dst(Square dst,bool offensif) const;//metre un false est chanbger
    virtual std::string to_string() const;
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
        std::string to_string() const override;
        Pion(Couleur couleur,Square position,bool vierge);
        virtual ~Pion(){}
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

