#pragma once
#include <iostream>
using namespace std;

class Echiquier
{
private:
    /* data */
public:
    string Echiquier::canonical_position() const;
    string Echiquier::pgn_piece_name(string const name, bool view_pawn, bool view_color) const;


    Echiquier(/* args */);
    ~Echiquier();
};
