#pragma once
#include <string>
using namespace std;

class Piece
{
private:
    string test;

    //uid
    //nom \u2656 affichera ♖
    //couleur
    //position

public:
    string to_string() const;
    Piece(/* args */);
    ~Piece();
};

Piece::Piece(/* args */)
{
}

Piece::~Piece()
{
}
