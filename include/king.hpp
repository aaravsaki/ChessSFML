#pragma once
#include "piece.hpp"

class King : public Piece
{
public:
    King() = delete;
    King(PieceType piece_type, Team team, Coord position);
    std::vector<Coord> getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const override;
    ~King() override = default;

};