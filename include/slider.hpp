#pragma once
#include "piece.hpp"

class Slider : public Piece
{
public:
    Slider() = delete;
    Slider(PieceType piece_type, Team team, Coord position);
    ~Slider() override = default;
    std::set<Coord> getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const override;
protected:
    std::vector<Coord> directions;  
};
