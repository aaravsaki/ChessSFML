#pragma once
#include "piece.hpp"

class Slider : public Piece
{
public:
    Slider() = delete;
    Slider(PieceType piece_type, Team team, Coord position);
    std::vector<Coord> getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const override;
    ~Slider() override = default;
private:
    std::vector<Coord> directions;

};
