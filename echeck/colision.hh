#include "square.hh"
#include "piece.hh"
#
enum direction{
        lignecolone,
        diagonal
};

class Colision
{
private:
    bool slidecheck(Piece * source,Square const position_dst, direction const direction);
    void slide(Square origine,Square decalage);
    void gen_colimap(Piece * source,direction look);
public:
    bool slidecheck(Piece * source,Square const position_dst);
    Colision(/* args */);
    ~Colision();
};
