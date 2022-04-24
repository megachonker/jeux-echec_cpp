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
    Square old_position;
public:
    std::string get_nom();
    virtual void undo_move();
    std::string typePc_to_string();
    virtual typePc get_type() const =0;//peut etre enlever
    virtual void deplace(Square dst);
    virtual bool check_dst(Square dst,bool aggresssion=false,bool print_err=false) const =0;//metre un false est chanbger
    virtual std::string to_string() const;
    void affiche() const;
    Piece(std::string nom, Couleur couleur, Square position);
    Square get_pos()const;
    Couleur get_couleur()const;
    virtual Piece * Clone()=0;
    virtual ~Piece(){};
};


class Pion : public Piece
{
    private:
        bool vierge;
        bool old_vierge;
        bool mangerdiag(Square dst,bool print_err) const;
    public:
        void undo_move() override;
        virtual typePc get_type() const override;
        void deplace(Square dst) override; 
        bool check_dst(Square dst,bool aggresssion=false,bool print_err=false) const override ;
        std::string to_string() const override;
        Pion(Couleur couleur,Square position,bool vierge);
        Piece * Clone() override;
        virtual ~Pion(){}
};

class Tour : public Piece
{
    private:
        bool vierge;
        bool old_vierge;
    public:
        void undo_move() override;
        std::string to_string() const override;
        bool isvierge();
        void deplace(Square dst) override; 
        virtual typePc get_type() const override;
        bool check_dst(Square dst,bool offensif=false,bool print_err=false) const override;
        Tour(Couleur couleur,Square position,bool vierge=true);
        Piece * Clone() override;
        virtual ~Tour(){}
};

class Fou : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst,bool offensif=false,bool print_err=false) const override;
        Fou(Couleur couleur,Square position);
        Piece * Clone() override;
        virtual ~Fou(){}
};

class Cavalier : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst,bool offensif=false,bool print_err=false) const override ;
        Cavalier(Couleur couleur,Square position);
        Piece * Clone() override;
        virtual ~Cavalier(){}
};

class Dame : public Piece
{
    public:
        virtual typePc get_type() const override;
        bool check_dst(Square dst,bool offensif=false,bool print_err=false) const override;
        Dame(Couleur couleur,Square position);
        Piece * Clone() override;
        virtual ~Dame(){}
};

class Roi : public Piece
{
    private:
        bool vierge;
        bool old_vierge;
    public:
        void undo_move() override;
        std::string to_string() const override;
        bool isvierge();
        void deplace(Square dst) override; 
        virtual typePc get_type() const override;
        bool check_dst(Square dst,bool offensif=false,bool print_err=false) const override;
        Roi(Couleur couleur,Square position,bool vierge=true);
        Piece * Clone() override;
        virtual ~Roi(){}
};

