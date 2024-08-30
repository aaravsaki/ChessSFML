#pragma once
#include "piece.hpp"

class Pawn : public Piece
{
public:
    Pawn() = default;
    Pawn(PieceType piece_type, Team team, Coord position);
    std::vector<Coord> getMoves(std::vector<std::vector<std::unique_ptr<Piece>>> field) const override;
    ~Pawn() override = default;

};
