#pragma once
#include "piece_constants.hpp"

struct Coord
{
    int x;
    int y;
};

class Piece
{
public:
    Piece(PieceType piece_type, Team team, Coord position);
    virtual ~Piece() = default;
};
