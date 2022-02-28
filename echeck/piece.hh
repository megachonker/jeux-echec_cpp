#pragma once
#include <string>

class Piece
{
private:
    std::string test;

    //uid
    //nom \u2656 affichera ♖
    //couleur
    //position

public:
    std::string to_string() const;
    Piece(/* args */);
    ~Piece();
};


